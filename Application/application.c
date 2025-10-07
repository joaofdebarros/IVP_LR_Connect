/*
 * application.c
 *
 *  Created on: 26 de set. de 2025
 *      Author: joao.victor
 */
#include "application.h"

application_t application;
packet_void_t sendRadio;

extern EmberEventControl *timeout_control;
extern EmberEventControl *radio_control;
extern EmberEventControl *motionDetected_control;
extern EmberEventControl *TimeoutAck_control;
extern EmberEventControl *report_control;

sl_sleeptimer_timer_handle_t periodic_timer;
uint8_t blink_count = 0;
uint8_t blink_target = 0;
uint8_t led_target;
extern tx_power;

EmberStatus radio_send_packet(packet_void_t *pck){
  uint8_t buffer_send[8];
  EmberStatus status;

  buffer_send[0] = pck->cmd;
  for(uint8_t i = 0; i < (pck->len-1); i++){
      buffer_send[i+1] = pck->data[i];
  }
  status = radioMessageSend(0,pck->len,buffer_send);

  return status;
}

void led_blink(uint8_t led, uint8_t blinks, uint8_t speed){
  led_target = led;
  blink_target = blinks;

  sl_sleeptimer_start_periodic_timer_ms(&periodic_timer,speed,led_handler, NULL,0,SL_SLEEPTIMER_NO_HIGH_PRECISION_HF_CLOCKS_REQUIRED_FLAG);
}

void led_handler(sl_sleeptimer_timer_handle_t *handle, void *data){

  (void)&handle;
  (void)&data;

  switch (led_target) {
    case VERMELHO:

      if(blink_count < (blink_target * 2)){
          blink_count++;
          hGpio_ledToggle(&sl_led_led_vermelho, application.IVP.SensorStatus.Status.led_enabled);
      }else{
          blink_count = 0;
          hGpio_ledTurnOff(&sl_led_led_vermelho, application.IVP.SensorStatus.Status.led_enabled);
          sl_sleeptimer_stop_timer(&periodic_timer);
      }
      break;
    case VERDE:

      if(blink_count < (blink_target * 2)){
          blink_count++;
          hGpio_ledToggle(&sl_led_led_verde, application.IVP.SensorStatus.Status.led_enabled);
      }else{
          blink_count = 0;
          hGpio_ledTurnOff(&sl_led_led_verde, application.IVP.SensorStatus.Status.led_enabled);
          sl_sleeptimer_stop_timer(&periodic_timer);
      }
      break;
    case AZUL:

      if(blink_count < (blink_target * 2)){
          blink_count++;
          hGpio_ledToggle(&sl_led_led_azul, application.IVP.SensorStatus.Status.led_enabled);
      }else{
          blink_count = 0;
          hGpio_ledTurnOff(&sl_led_led_azul, application.IVP.SensorStatus.Status.led_enabled);
          sl_sleeptimer_stop_timer(&periodic_timer);
      }
      break;
    default:
      break;
  }

}

void radio_handler(void){
  packet_void_t *receive;

  receive = &application.radio.Packet;

  switch(receive->cmd){
    case STATUS_CENTRAL:
      application.Status_Central = receive->data[0];
      application.radio.LastCMD = receive->cmd;
      if(application.Status_Central == ARMED){

          pydInit(application.IVP.pydConf.sPYDType.thresholdVal);
          application.Status_Operation = OPERATION_MODE;

          led_blink(VERMELHO, 2, MED_SPEED_BLINK);

          emberEventControlSetActive(*report_control);
      }
      else if(application.Status_Central == DISARMED){
          TurnPIROff(application.IVP.SensorStatus.Status.energy_mode);
          emberEventControlSetInactive(*timeout_control);

          led_blink(VERMELHO, 3, MED_SPEED_BLINK);

          emberEventControlSetActive(*report_control);
      }

      break;
    case SETUP_IVP:
      application.radio.LastCMD = receive->cmd;
      application.IVP.pydConf.sPYDType.operationConf.sOpMode.reserved = 2;                 // reserved
      application.IVP.pydConf.sPYDType.operationConf.sOpMode.reserved1 = 0;                // reserved
      application.IVP.pydConf.sPYDType.operationConf.sOpMode.opMode = PYD_MODE_WAKE_UP;    // wake mode
      application.IVP.pydConf.sPYDType.operationConf.sOpMode.signalSource = 1;             //
      application.IVP.pydConf.sPYDType.alarm.sAlarmConf.blindTime = 0;                     // 0.5seg + val*0.5s
      application.IVP.pydConf.sPYDType.alarm.sAlarmConf.pulseCtr = 1;                      // 1 + val
      application.IVP.pydConf.sPYDType.alarm.sAlarmConf.wdwTime = 3;                       // 2s + val*2s
      application.IVP.pydConf.sPYDType.thresholdVal = receive->data[0];                         // will be configured later

      application.IVP.SensorStatus.Status.energy_mode = receive->data[1];

      if(application.IVP.SensorStatus.Status.energy_mode == UECONOMIC){
          application.IVP.SensorStatus.Status.led_enabled = false;
      }else{
          application.IVP.SensorStatus.Status.led_enabled = receive->data[2];
      }

      tx_power = receive->data[3];
      set_tx(tx_power);

      led_blink(VERMELHO, 2, FAST_SPEED_BLINK);

      motionCounterTimer = MOTION_COUNTER_5S;

      hGpio_changeToOutput(DIRECT_LINK_PORT,DIRECT_LINK_PIN);
      hGpio_write(DIRECT_LINK_PORT,DIRECT_LINK_PIN,hGPIO_PIN_HIGH);

      pydConfig(application.IVP.pydConf.pydRegisters);

//      emberEventControlSetDelayMS(*timeout_control,2000);
      emberEventControlSetActive(*report_control);
      break;

    default:
      break;
  }
  emberEventControlSetInactive(*radio_control);
}

void timeout_handler(void)
{
  motionCounterTimer = 0;
  hGpio_ledTurnOff(&sl_led_led_vermelho, application.IVP.SensorStatus.Status.led_enabled);
  pydAckTrigger();
  hGpio_enableInterrupt(DIRECT_LINK_PORT, DIRECT_LINK_PIN);


  emberEventControlSetInactive(*timeout_control);
}

void motionDetected_handler(void){
  volatile SensorStatus_t SensorStatus;

  hGpio_disableInterrupt(DIRECT_LINK_PORT,DIRECT_LINK_PIN);

  SensorStatus.Status.operation = application.Status_Operation;
  SensorStatus.Status.statusCentral = application.Status_Central;

  sendRadio.cmd = MOTION_DETECTED;
  sendRadio.len = 4;


  sendRadio.data[0] = SensorStatus.Statusbyte;
  sendRadio.data[1] = battery.VBAT >> 8;
  sendRadio.data[2] = battery.VBAT;

  application.radio.LastCMD = sendRadio.cmd;
  radio_send_packet(&sendRadio);
  emberEventControlSetDelayMS(*TimeoutAck_control,500); //Timeout que indica que não houve resposta
  battery.VBAT = calculateVdd();

  hGpio_ledTurnOn(&sl_led_led_vermelho, application.IVP.SensorStatus.Status.led_enabled);
  motionCounterTimer = MOTION_COUNTER_2S;
  emberEventControlSetDelayMS(*timeout_control,2000); //Interrupção desativada e sem detecção por 2 segundos
  emberEventControlSetInactive(*motionDetected_control); //Desativa o motionDetected_control até a próxima detecção
}

void TimeoutAck_handler(void){
  radio_send_packet(&sendRadio);
  battery.VBAT = calculateVdd();
  emberEventControlSetInactive(*TimeoutAck_control);
}

void TurnPIROff(Energy_Mode_t energy_mode){
  switch (energy_mode) {
    case CONTINUOUS:
      hGpio_ledTurnOff(&sl_led_led_vermelho, application.IVP.SensorStatus.Status.led_enabled);
      hGpio_enableInterrupt(DIRECT_LINK_PORT,DIRECT_LINK_PIN);
      break;
    case ECONOMIC:
      hGpio_ledTurnOff(&sl_led_led_vermelho, application.IVP.SensorStatus.Status.led_enabled);
      hGpio_disableInterrupt(DIRECT_LINK_PORT,DIRECT_LINK_PIN);
      break;
    case UECONOMIC:
      hGpio_ledTurnOff(&sl_led_led_vermelho, application.IVP.SensorStatus.Status.led_enabled);
      hGpio_disableInterrupt(DIRECT_LINK_PORT,DIRECT_LINK_PIN);
      break;
    default:
      break;
  }

}
