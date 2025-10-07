/*
 * callbacks.c
 *
 *  Created on: 18 de july de 2024
 *      Author: diego.marinho
 */


#include "callbacks.h"

extern bool StatusTrigger;

packet_void_t Packet;
extern application_t application;
extern EmberEventControl *radio_control;
extern EmberEventControl *motionDetected_control;

/*
 * Globas and Externs
 */

void hTimer_Callback(uint32_t index){
  if(motionCounterTimer)
  {
     if(--motionCounterTimer == 0)
     {
         hTimer_Stop(TIMER0);

        if(hGpio_read(AF_PORT, AF_PIN))
        {
           hGpio_write(RL_PORT, RL_PIN, hGPIO_PIN_HIGH);
        }
        else
        {
            hGpio_write(RL_PORT, RL_PIN, hGPIO_PIN_LOW);
        }
        hGpio_ledTurnOff(&sl_led_led_vermelho, application.IVP.SensorStatus.Status.led_enabled);
        //StatusSleep = false;
        StatusTrigger = true;


     }
  }
}


void hGpio_Callback(uint32_t pin){
  if(pin == DIRECT_LINK_PIN && !motionCounterTimer){
      //StatusSleep = true;
      hGpio_disableInterrupt(DIRECT_LINK_PORT,DIRECT_LINK_PIN);
      //motionDetected();
      emberEventControlSetActive(*motionDetected_control);
  }
}

void callback_Radio_Receive(uint8_t *data, uint8_t len){
  packet_data_demount(data,len,&application.radio.Packet);
  emberEventControlSetActive(*radio_control);
}






