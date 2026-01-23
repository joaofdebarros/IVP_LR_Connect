/***************************************************************************//**
 * @file
 * @brief app_process.c
 *******************************************************************************
 * # License
 * <b>Copyright 2018 Silicon Laboratories Inc. www.silabs.com</b>
 *******************************************************************************
 *
 * SPDX-License-Identifier: Zlib
 *
 * The licensor of this software is Silicon Laboratories Inc.
 *
 * This software is provided 'as-is', without any express or implied
 * warranty. In no event will the authors be held liable for any damages
 * arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software. If you use this software
 *    in a product, an acknowledgment in the product documentation would be
 *    appreciated but is not required.
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 * 3. This notice may not be removed or altered from any source distribution.
 *
 ******************************************************************************/

// -----------------------------------------------------------------------------
//                                   Includes
// -----------------------------------------------------------------------------
#include PLATFORM_HEADER
#include "sl_component_catalog.h"
#include "stack/include/ember.h"
#include "em_chip.h"
#include "app_log.h"
#include "poll.h"
#include "sl_app_common.h"
#include "sl_simple_button_instances.h"
#include "app_process.h"
#include "app_framework_common.h"
#if defined(SL_CATALOG_LED0_PRESENT)
#include "sl_simple_led_instances.h"
#endif
#if defined(SL_CATALOG_KERNEL_PRESENT)
#include "sl_power_manager.h"
#endif
#include "API/packet/pckDataStructure.h"
#include "Application/application.h"
#include "API/battery/battery.h"
#include "API/hNetwork.h"

#include "gpiointerrupt.h"

#include "hplatform/hDriver/hGpio.h"
#include "API/pyd/pyd.h"
#include "poll.h"
#include "hplatform/hDriver/hADC.h"
#include "API/memory/memory.h"
// -----------------------------------------------------------------------------
//                              Macros and Typedefs
// -----------------------------------------------------------------------------
#define MAX_TX_FAILURES     (10U)
#define ALPHA 0.1f
// -----------------------------------------------------------------------------
//                          Static Function Declarations
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
//                                Global Variables
// -----------------------------------------------------------------------------
/// Global flag set by a button push to allow or disallow entering to sleep
bool enable_sleep = false;
/// report timing event control
EmberEventControl *report_control;
EmberEventControl *radio_control;
EmberEventControl *motionDetected_control;
EmberEventControl *timeout_control;
EmberEventControl *TimeoutAck_control;
EmberEventControl *Init_control;

/// report timing period
uint16_t sensor_report_period_ms =  (1 * MILLISECOND_TICKS_PER_SECOND);
/// TX options set up for the network
EmberMessageOptions tx_options = EMBER_OPTIONS_ACK_REQUESTED | EMBER_OPTIONS_SECURITY_ENABLED;

extern application_t application;
extern packet_void_t sendRadio;
extern send_queue_t radioQueue[MAX_QUEUE_PACKETS];

Status_Operation_t last_status = WAIT_REGISTRATION;

uint32_t press_start_time = 0;
extern bool button_is_pressed = false;

bool joined = false;
bool initialized = false;
uint8_t tx_power = 0;
// -----------------------------------------------------------------------------
//                                Static Variables
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
//                          Public Function Definitions
// -----------------------------------------------------------------------------

static void gpioSetup(void){
  GPIO_PinModeSet(SER_IN_PORT, SER_IN_PIN, gpioModePushPull, 0);
  GPIO_PinModeSet(SENSE_LOW_PORT, SENSE_LOW_PIN, gpioModePushPull, 1);
  // Configure Button PB0 as input and enable interrupt
  //GPIO_PinModeSet(DIRECT_LINK_PORT, DIRECT_LINK_PIN, gpioModeInputPull, 1);
  GPIO_PinModeSet(DIRECT_LINK_PORT, DIRECT_LINK_PIN, gpioModeInput, 0);
  GPIO_ExtIntConfig(DIRECT_LINK_PORT,
                    DIRECT_LINK_PIN,
                    DIRECT_LINK_PIN,
                    true,
                    false,
                    true);

  GPIOINT_CallbackRegister((uint8_t)DIRECT_LINK_PIN,(GPIOINT_IrqCallbackPtr_t)CallbackGPIO);

  // Enable EVEN interrupt to catch button press that changes slew rate
  NVIC_ClearPendingIRQ(GPIO_EVEN_IRQn);
  NVIC_EnableIRQ(GPIO_EVEN_IRQn);
}

static void timerSetup(void){
  USTIMER_Init();
}

void CallbackGPIO(uint8_t interrupt_no){
      GPIO_EXTI_Callback(interrupt_no);
}

void app_init(){
  emberAfAllocateEvent(&report_control, &report_handler);
  emberAfAllocateEvent(&radio_control, &radio_handler);
  emberAfAllocateEvent(&motionDetected_control, &motionDetected_handler);
  emberAfAllocateEvent(&timeout_control, &timeout_handler);
  emberAfAllocateEvent(&TimeoutAck_control, &TimeoutAck_handler);
  emberAfAllocateEvent(&Init_control, &Init_handler);

  emberEventControlSetDelayMS(*Init_control, 100);
}

void Init_handler(){
  emberAfPluginPollEnableShortPolling(true);

  application.IVP.pydConf.sPYDType.thresholdVal = 120;
  application.IVP.SensorStatus.Status.led_enabled = 1;
  application.IVP.SensorStatus.Status.energy_mode = CONTINUOUS;
  tx_power = 150;
  application.Status_Operation = OPERATION_MODE;
  //  application.Status_Central = ARMED;

  memory_read(STATUSBYTE_MEMORY_KEY, &application.IVP.SensorStatus.Statusbyte);
  memory_read(SENSIBILITY_MEMORY_KEY, &application.IVP.pydConf.sPYDType.thresholdVal);
  memory_read(TXPOWER_MEMORY_KEY, &tx_power);
  memory_read(STATUSOP_MEMORY_KEY, &application.Status_Operation);
  memory_read(STATUSCENTRAL_MEMORY_KEY, &application.Status_Central);
  memory_read(ID_PARTITION_MEMORY_KEY, &application.IVP.ID_partition);
  memory_read(BATTERY_MEMORY_KEY, &battery.VBAT);

  // FORCANDO ARMADO E CONTINUO SEMPRE PARA TESTE
  //  application.IVP.SensorStatus.Status.energy_mode = CONTINUOUS;
  application.Status_Operation = BOOT;
  //  application.Status_Central = ARMED;

  app_button_press_enable();

  sl_mx25_flash_shutdown();

  gpioSetup();
  timerSetup();
  set_tx(tx_power);
  iadcInit();

  if(application.Status_Operation == OPERATION_MODE){
      application.Status_Operation = BOOT;
  }

  initialized = true;

  emberEventControlSetInactive(*Init_control);
  emberEventControlSetDelayMS(*report_control, 500);
}

void app_button_press_cb(uint8_t button, uint8_t duration)
{
  if(duration < 3){
      if(application.Status_Operation == WAIT_REGISTRATION){
          join_sleepy(0);
          sl_led_turn_on(&sl_led_led_vermelho);
      }else if(application.Status_Operation == OPERATION_MODE){
          led_blink(VERMELHO, 2, MED_SPEED_BLINK);
      }
  }else{
//      hGpio_disableInterrupt(DIRECT_LINK_PORT,DIRECT_LINK_PIN);
      emberEventControlSetInactive(*timeout_control);

      reset_parameters();
      leave();
  }
}


void reset_parameters(){
  memory_erase(STATUSBYTE_MEMORY_KEY);
  memory_erase(SENSIBILITY_MEMORY_KEY);
  memory_erase(TXPOWER_MEMORY_KEY);
  memory_erase(STATUSOP_MEMORY_KEY);
  memory_erase(STATUSCENTRAL_MEMORY_KEY);
  memory_erase(ID_PARTITION_MEMORY_KEY);

  application.IVP.pydConf.sPYDType.thresholdVal = 120;
  application.IVP.SensorStatus.Status.led_enabled = 1;
  application.IVP.SensorStatus.Status.energy_mode = CONTINUOUS;
  pydInit(application.IVP.pydConf.sPYDType.thresholdVal);
  tx_power = 150;
  set_tx(tx_power);
  application.Status_Operation = WAIT_REGISTRATION;
  application.Status_Central = DISARMED;

  memory_write(STATUSOP_MEMORY_KEY, &application.Status_Operation, sizeof(application.Status_Operation));
  memory_write(STATUSCENTRAL_MEMORY_KEY, &application.Status_Central, sizeof(application.Status_Central));
  memory_write(STATUSBYTE_MEMORY_KEY, &application.IVP.SensorStatus.Statusbyte, sizeof(application.IVP.SensorStatus.Statusbyte));
  memory_write(TXPOWER_MEMORY_KEY, &tx_power, sizeof(tx_power));
  memory_write(SENSIBILITY_MEMORY_KEY, &application.IVP.pydConf.sPYDType.thresholdVal, sizeof(application.IVP.pydConf.sPYDType.thresholdVal));
}

void battery_read(){
  uint16_t reading = 0;

  reading = calculateVdd();

  if(reading != 0){
      if(battery.VBAT == 0){
          battery.VBAT = reading;
      }else{
          battery.VBAT = ALPHA * reading + (1.0f - ALPHA) * battery.VBAT;
      }
  }

  memory_write(BATTERY_MEMORY_KEY, &battery.VBAT, sizeof(battery.VBAT));
}

/**************************************************************************//**
 * Here we print out the first two bytes reported by the sinks as a little
 * endian 16-bits decimal.
 *****************************************************************************/
void report_handler(void)
{
  volatile Register_Sensor_t Register_Sensor;

  battery_read();

   switch (application.Status_Operation) {
     case WAIT_REGISTRATION:
       Register_Sensor.Status.Type = MOTION_DETECT;
       Register_Sensor.Status.range = LONG_RANGE;

       sendRadio.cmd = IVP_REGISTRATION;
       sendRadio.len = 2;
       sendRadio.data[0] = Register_Sensor.Registerbyte;

       application.radio.LastCMD = sendRadio.cmd;

       break;

     case OPERATION_MODE:
       volatile SensorStatus_t SensorStatus;

       SensorStatus.Status.operation = application.Status_Operation;
       SensorStatus.Status.statusCentral = application.Status_Central;
       SensorStatus.Status.energy_mode = application.IVP.SensorStatus.Status.energy_mode;
       SensorStatus.Status.led_enabled = application.IVP.SensorStatus.Status.led_enabled;

       if(application.radio.LastCMD == SENSOR_PARTITION){
           sendRadio.cmd = SENSOR_PARTITION;
           sendRadio.len = 4;
           sendRadio.data[0] = application.radio.error;
           sendRadio.data[1] = battery.VBAT;                                     // Nivel de bateria
           sendRadio.data[2] = battery.VBAT >> 8;                                //
       }

       if(application.radio.LastCMD == STATUS_CENTRAL){
           sendRadio.cmd = STATUS_CENTRAL;
           sendRadio.len = 4;
           sendRadio.data[0] = 0;                                                // NULL
           sendRadio.data[1] = battery.VBAT;                                     // Nivel de bateria
           sendRadio.data[2] = battery.VBAT >> 8;                                //
       }

       if(application.radio.LastCMD == SETUP_IVP){
           sendRadio.cmd = SETUP_IVP;
           sendRadio.len = 6;
           sendRadio.data[0] = SensorStatus.Statusbyte;                          // Estado de Operação
           sendRadio.data[1] = battery.VBAT;                                     // Nivel de bateria
           sendRadio.data[2] = battery.VBAT >> 8;                                //
           sendRadio.data[3] = application.IVP.pydConf.sPYDType.thresholdVal;    // Sensibilidade sensor
           sendRadio.data[4] = tx_power;                                         // Potencia de transmissao
       }

       break;
     case BOOT:
       if(joined){
           application.Status_Operation = OPERATION_MODE;
       }else{
           application.Status_Operation = WAIT_REGISTRATION;
       }

       if(application.Status_Central == ARMED){
           pydConfig(application.IVP.pydConf.pydRegisters);
           pydInit(application.IVP.pydConf.sPYDType.thresholdVal);
       }

       if(application.Status_Central == DISARMED){
           if(application.IVP.SensorStatus.Status.energy_mode != CONTINUOUS){
               TurnPIROff(application.IVP.SensorStatus.Status.energy_mode);
           }else{
               //Caso seja modo contínuo, ligar o PIR
               pydConfig(application.IVP.pydConf.pydRegisters);
               pydInit(application.IVP.pydConf.sPYDType.thresholdVal);
           }
       }


       break;
     default:
       break;
   }

   radio_send_packet(&sendRadio, false);
   emberEventControlSetDelayMS(*TimeoutAck_control,500);
   battery_read();

   emberEventControlSetInactive(*report_control);
}

/**************************************************************************//**
 * Entering sleep is approved or denied in this callback, depending on user
 * demand.
 *****************************************************************************/
bool emberAfCommonOkToEnterLowPowerCallback(bool enter_em2, uint32_t duration_ms)
{
  (void) enter_em2;
  (void) duration_ms;
  return enable_sleep;
}

/**************************************************************************//**
 * This function is called when a message is received.
 *****************************************************************************/
void emberAfIncomingMessageCallback(EmberIncomingMessage *message)
{
  privcallback_Radio_Receive(message->payload,message->length);
}

/**************************************************************************//**
 * This function is called to indicate whether an outgoing message was
 * successfully transmitted or to indicate the reason of failure.
 *****************************************************************************/
void emberAfMessageSentCallback(EmberStatus status,
                                EmberOutgoingMessage *message)
{
  if(message->payload[0] == IVP_REGISTRATION && application.Status_Operation == WAIT_REGISTRATION && status == EMBER_SUCCESS){
        //Estado inicial do sensor apos cadastro
        TurnPIROff(application.IVP.SensorStatus.Status.energy_mode);
        application.Status_Operation = OPERATION_MODE;
        application.Status_Central = ARMED;
        application.IVP.SensorStatus.Status.energy_mode = CONTINUOUS;

        memory_write(STATUSOP_MEMORY_KEY, &application.Status_Operation, sizeof(application.Status_Operation));
        memory_write(STATUSCENTRAL_MEMORY_KEY, &application.Status_Central, sizeof(application.Status_Central));
        memory_write(STATUSBYTE_MEMORY_KEY, &application.IVP.SensorStatus.Statusbyte, sizeof(application.IVP.SensorStatus.Statusbyte));
    }

  for(int i = 0; i < MAX_QUEUE_PACKETS; i++){
          if(message->payload[0] == radioQueue[i].packet.cmd){
              if(status == EMBER_SUCCESS){
                  radioQueue[i].slot_used = false;
                  radioQueue[i].attempts = 0;
              }else{
                  if(radioQueue[i].attempts == MAX_QUEUE_PACKET_ATTEMPTS){
                      radioQueue[i].slot_used = false;
                      radioQueue[i].attempts = 0;
                  }else{
                      radioQueue[i].slot_used = true;
                      radioQueue[i].attempts++;
                      radio_send_packet(&radioQueue[i].packet, true);
                  }
              }
          }
    }

    if(application.radio.LastCMD == message->payload[0]){
        emberEventControlSetInactive(*TimeoutAck_control);
    }
}

/**************************************************************************//**
 * This function is called when the stack status changes.
 *****************************************************************************/
void emberAfStackStatusCallback(EmberStatus status)
{
  switch (status) {
      case EMBER_NETWORK_UP:
        joined = true;
        led_blink(VERMELHO, 2, MED_SPEED_BLINK);
        enable_sleep = true;
        if(application.Status_Operation == WAIT_REGISTRATION && initialized){
            emberEventControlSetDelayMS(*report_control, 10);
        }

        break;
      case EMBER_NETWORK_DOWN:
        joined = false;
        enable_sleep = false;
        led_blink(VERMELHO, 5, FAST_SPEED_BLINK);
        break;
      case EMBER_JOIN_SCAN_FAILED:
        led_blink(VERMELHO, 2, SLOW_SPEED_BLINK);
        break;
      case EMBER_JOIN_DENIED:
        led_blink(VERMELHO, 2, SLOW_SPEED_BLINK);
        break;
      case EMBER_JOIN_TIMEOUT:
        led_blink(VERMELHO, 2, SLOW_SPEED_BLINK);
        break;
      default:
        led_blink(VERMELHO, 2, SLOW_SPEED_BLINK);
        break;
    }
}

/**************************************************************************//**
 * This callback is called in each iteration of the main application loop and
 * can be used to perform periodic functions.
 *****************************************************************************/
void emberAfTickCallback(void)
{
  uint32_t current_time = sl_sleeptimer_get_tick_count();

  if(button_is_pressed){
      if((current_time - press_start_time) > 100000){
          sl_led_turn_on(&sl_led_led_vermelho);
      }
  }
#if defined(SL_CATALOG_LED0_PRESENT)
  if (emberStackIsUp()) {
    sl_led_turn_on(&sl_led_led0);
  } else {
    sl_led_turn_off(&sl_led_led0);
  }
#endif
}

/**************************************************************************//**
 * This function is called when a frequency hopping client completed the start
 * procedure.
 *****************************************************************************/
void emberAfFrequencyHoppingStartClientCompleteCallback(EmberStatus status)
{
  if (status != EMBER_SUCCESS) {
//    app_log_error("FH Client sync failed, status=0x%02X\n", status);
  } else {
//    app_log_info("FH Client Sync Success\n");
  }
}

/**************************************************************************//**
 * This function is called when a requested energy scan is complete.
 *****************************************************************************/
//void emberAfEnergyScanCompleteCallback(int8_t mean,
//                                       int8_t min,
//                                       int8_t max,
//                                       uint16_t variance)
//{
//  app_log_info("Energy scan complete, mean=%d min=%d max=%d var=%d\n",
//               mean, min, max, variance);
//}

#if defined(EMBER_AF_PLUGIN_MICRIUM_RTOS) && defined(EMBER_AF_PLUGIN_MICRIUM_RTOS_APP_TASK1)

/**************************************************************************//**
 * This function is called from the Micrium RTOS plugin before the
 * Application (1) task is created.
 *****************************************************************************/
void emberAfPluginMicriumRtosAppTask1InitCallback(void)
{
//  app_log_info("app task init\n");
}

#include <kernel/include/os.h>
#define TICK_INTERVAL_MS 1000

/**************************************************************************//**
 * This function implements the Application (1) task main loop.
 *****************************************************************************/
void emberAfPluginMicriumRtosAppTask1MainLoopCallback(void *p_arg)
{
  RTOS_ERR err;
  OS_TICK yield_time_ticks = (OSCfg_TickRate_Hz * TICK_INTERVAL_MS) / 1000;

  while (true) {
//    app_log_info("app task tick\n");

    OSTimeDly(yield_time_ticks, OS_OPT_TIME_DLY, &err);
  }
}

#endif // EMBER_AF_PLUGIN_MICRIUM_RTOS && EMBER_AF_PLUGIN_MICRIUM_RTOS_APP_TASK1
