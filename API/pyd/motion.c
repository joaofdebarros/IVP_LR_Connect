/*
 * motion.c
 *
 *  Created on: 17 de mai de 2021
 *      Author: fausto.fujikawa
 */
//-----------------------------------------------------------------------------
// Includes
//-----------------------------------------------------------------------------
#include "motion.h"

//-----------------------------------------------------------------------------
// Variables
//-----------------------------------------------------------------------------
volatile uint8_t lastSensitivityMatched;
volatile uint16_t motionCounterTimer;

extern EmberEventControl *timeout_control;

//-----------------------------------------------------------------------------
// Functions
//-----------------------------------------------------------------------------
void motionCheckSensitivy(void)
{
  pydConf.sPYDType.thresholdVal = PYD_SEN_HIGH;
//   if(!hGpio_read(SENSE_LOW_PORT,SENSE_LOW_PIN))
//   {
//      pydConf.sPYDType.thresholdVal = PYD_SEN_LOW;
//   }
//   else if(!hGpio_read(SENSE_HIGH_PORT,SENSE_HIGH_PIN))
//   {
//      pydConf.sPYDType.thresholdVal = PYD_SEN_HIGH;
//   }
//   else
//   {
//      pydConf.sPYDType.thresholdVal = PYD_SEN_MED;
//   }
}

void motionDetected(void)
{
//  hGpio_ledTurnOff(&sl_led_led_vermelho, application.LED_enabled);

   motionCounterTimer = MOTION_COUNTER_2S;
   //hTimer_Start(TIMER0);
   emberEventControlSetDelayMS(*timeout_control,2000);


   if(hGpio_read(AF_PORT,AF_PIN))                      // trigger
   {
       hGpio_write(RL_PORT, RL_PIN, hGPIO_PIN_LOW);
   }
   else
   {
       hGpio_write(RL_PORT, RL_PIN, hGPIO_PIN_HIGH);
   }
}
