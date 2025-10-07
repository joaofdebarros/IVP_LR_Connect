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
// -----------------------------------------------------------------------------
//                              Macros and Typedefs
// -----------------------------------------------------------------------------
#define MAX_TX_FAILURES     (10U)
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

/// report timing period
uint16_t sensor_report_period_ms =  (1 * MILLISECOND_TICKS_PER_SECOND);
/// TX options set up for the network
EmberMessageOptions tx_options = EMBER_OPTIONS_ACK_REQUESTED | EMBER_OPTIONS_SECURITY_ENABLED;

extern application_t application;
extern packet_void_t sendRadio;

Status_Operation_t last_status = WAIT_REGISTRATION;

extern sl_sleeptimer_timer_handle_t periodic_timer;
extern uint8_t blink_target;
extern uint8_t led_target;
uint32_t press_start_time = 0;
bool button_is_pressed = false;

extern tx_power;
// -----------------------------------------------------------------------------
//                                Static Variables
// -----------------------------------------------------------------------------
/// Destination of the currently processed sink node
static EmberNodeId sink_node_id = EMBER_COORDINATOR_ADDRESS;

// -----------------------------------------------------------------------------
//                          Public Function Definitions
// -----------------------------------------------------------------------------
void sl_button_on_change(const sl_button_t *handle){

  if (sl_button_get_state(handle) == SL_SIMPLE_BUTTON_RELEASED) {
     if(&sl_button_btn0 == handle){
         press_start_time = sl_sleeptimer_get_tick_count();
         button_is_pressed = true;
     }
  }

  if(sl_button_get_state(handle) == SL_SIMPLE_BUTTON_PRESSED){
      uint32_t current_time = sl_sleeptimer_get_tick_count();
      button_is_pressed = false;
      if((current_time - press_start_time) > 100000){
          hGpio_disableInterrupt(DIRECT_LINK_PORT,DIRECT_LINK_PIN);
          emberEventControlSetInactive(*timeout_control);
          application.Status_Operation = WAIT_REGISTRATION;
          leave();
          emberResetNetworkState();
      }else if((current_time - press_start_time) < 50000){
          join_sleepy(0);

      }
  }
}

/**************************************************************************//**
 * Here we print out the first two bytes reported by the sinks as a little
 * endian 16-bits decimal.
 *****************************************************************************/
void report_handler(void)
{
  volatile Register_Sensor_t Register_Sensor;
   uint16_t Vbat = calculateVdd();

   switch (application.Status_Operation) {
     case WAIT_REGISTRATION:
       Register_Sensor.Status.Type = MOTION_DETECT;
       Register_Sensor.Status.range = LONG_RANGE;

       sendRadio.cmd = REGISTRATION;
       sendRadio.len = 2;
       sendRadio.data[0] = Register_Sensor.Registerbyte;

       application.radio.LastCMD = sendRadio.cmd;
       break;

     case OPERATION_MODE:

       if(application.radio.LastCMD == STATUS_CENTRAL){
           sendRadio.cmd = STATUS_CENTRAL;
       }

       if(application.radio.LastCMD == SETUP_IVP){
           sendRadio.cmd = SETUP_IVP;
       }

       volatile SensorStatus_t SensorStatus;

       SensorStatus.Status.operation = application.Status_Operation;
       SensorStatus.Status.statusCentral = application.Status_Central;
       SensorStatus.Status.energy_mode = application.IVP.SensorStatus.Status.energy_mode;
       SensorStatus.Status.led_enabled = application.IVP.SensorStatus.Status.led_enabled;

       sendRadio.len = 6;
       sendRadio.data[0] = SensorStatus.Statusbyte;                          //Estado de Operação
       sendRadio.data[1] = battery.VBAT >> 8;                                //
       sendRadio.data[2] = battery.VBAT;                                     //
       sendRadio.data[3] = application.IVP.pydConf.sPYDType.thresholdVal;    //
       sendRadio.data[4] = tx_power;

       break;
     default:
       break;
   }

   radio_send_packet(&sendRadio);
   emberEventControlSetDelayMS(*TimeoutAck_control,500);
   battery.VBAT = calculateVdd();


   enable_sleep = !enable_sleep;

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
  if(message->payload[0] == REGISTRATION && application.Status_Operation == WAIT_REGISTRATION){
        //sensor cadastrado
        application.IVP.SensorStatus.Status.energy_mode = ECONOMIC;
        TurnPIROff(application.IVP.SensorStatus.Status.energy_mode);
        application.Status_Operation = OPERATION_MODE;
        application.Status_Central = DISARMED;
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
        // Schedule start of periodic sensor reporting to the Sink
        led_blink(VERMELHO, 5, MED_SPEED_BLINK);
//        pydInit(application.IVP.pydConf.sPYDType.thresholdVal); //INICIA O PIR
        emberEventControlSetDelayMS(*report_control, sensor_report_period_ms);
        break;
      case EMBER_NETWORK_DOWN:
        led_blink(VERMELHO, 10, FAST_SPEED_BLINK);
//        app_log_info("Network down\n");
        break;
      case EMBER_JOIN_SCAN_FAILED:
//        app_log_error("Scanning during join failed\n");
        break;
      case EMBER_JOIN_DENIED:
//        app_log_error("Joining to the network rejected!\n");
        break;
      case EMBER_JOIN_TIMEOUT:
//        app_log_info("Join process timed out!\n");
        break;
      default:
        led_blink(VERMELHO, 2, SLOW_SPEED_BLINK);
//        app_log_info("Stack status: 0x%02X\n", status);
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
void emberAfEnergyScanCompleteCallback(int8_t mean,
                                       int8_t min,
                                       int8_t max,
                                       uint16_t variance)
{
//  app_log_info("Energy scan complete, mean=%d min=%d max=%d var=%d\n",
//               mean, min, max, variance);
}

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
