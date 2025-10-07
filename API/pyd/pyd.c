/*
 * pyd.c
 *
 *  Created on: 17 de mai de 2021
 *      Author: fausto.fujikawa
 */
#include "pyd.h"

//-----------------------------------------------------------------------------
// Variables
//-----------------------------------------------------------------------------
uPYDType pydConf;
uint16_t pirValue;      // remover
uint32_t pirConfig;     // remover

extern EmberEventControl *timeout_control;

//-----------------------------------------------------------------------------
// Functions
//-----------------------------------------------------------------------------
void pydInit(uint8_t sensibilidade)
{
   pydConf.sPYDType.operationConf.sOpMode.reserved = 2;                 // reserved
   pydConf.sPYDType.operationConf.sOpMode.reserved1 = 0;                // reserved
   pydConf.sPYDType.operationConf.sOpMode.opMode = PYD_MODE_WAKE_UP;    // wake mode
   pydConf.sPYDType.operationConf.sOpMode.signalSource = 1;             //
   pydConf.sPYDType.alarm.sAlarmConf.blindTime = 0;                     // 0.5seg + val*0.5s
   pydConf.sPYDType.alarm.sAlarmConf.pulseCtr = 1;                      // 1 + val
   pydConf.sPYDType.alarm.sAlarmConf.wdwTime = 3;                       // 2s + val*2s
   pydConf.sPYDType.thresholdVal = sensibilidade;                       // will be configured later

//   motionCheckSensitivy();
   motionCounterTimer = MOTION_COUNTER_5S;
   hGpio_changeToOutput(DIRECT_LINK_PORT,DIRECT_LINK_PIN);
   hGpio_write(DIRECT_LINK_PORT,DIRECT_LINK_PIN,hGPIO_PIN_HIGH);
   pydConfig(pydConf.pydRegisters);
   emberEventControlSetDelayMS(*timeout_control,5000);
}

void pydConfig(uint32_t config)
{
   uint8_t i;
   unsigned char nextbit;
   volatile uint32_t regMask = 0x1000000;
   uint32_t outData;

   outData = config >> 7;
   //pydConf.pydRegisters = 0xA0F30;
   config = config >> 7;

   hGpio_write(SER_IN_PORT,SER_IN_PIN,hGPIO_PIN_LOW);

   for(i = 0; i < 25; i++)
   {
       nextbit = (config&regMask)!=0; //Set bit value to LSB register value
       regMask >>= 1;
       hGpio_write(SER_IN_PORT,SER_IN_PIN,hGPIO_PIN_LOW);
       __NOP();

       hGpio_write(SER_IN_PORT,SER_IN_PIN,hGPIO_PIN_HIGH);
       __NOP();

      if(nextbit)
      {
          hGpio_write(SER_IN_PORT,SER_IN_PIN,hGPIO_PIN_HIGH);
      }
      else
      {
          hGpio_write(SER_IN_PORT,SER_IN_PIN,hGPIO_PIN_LOW);
      }
      //regMask >>= 1;

      hTimer_udelay(100);
   }
   hGpio_write(SER_IN_PORT,SER_IN_PIN,hGPIO_PIN_LOW);
   hTimer_udelay(600);
}

void pydRead(void)
{
   uint8_t i;
   uint16_t intBitMask;
   uint32_t longBitMask;

   hGpio_disableInterrupt(DIRECT_LINK_PORT,DIRECT_LINK_PIN);

   //hGpio_changeToOutput(DIRECT_LINK_PORT,DIRECT_LINK_PIN);

   //hGpio_write(DIRECT_LINK_PORT,DIRECT_LINK_PIN,hGPIO_PIN_HIGH);
   //hGpio_changeToOutput(DIRECT_LINK_PORT,DIRECT_LINK_PIN);
   //hTimer_udelay(120);

   intBitMask = 0x4000;
   pirValue = 0;
   for(i = 0; i < 15; i++)
     {
       hGpio_changeToOutput(DIRECT_LINK_PORT,DIRECT_LINK_PIN);
       hGpio_write(DIRECT_LINK_PORT,DIRECT_LINK_PIN,hGPIO_PIN_LOW);
       //hGpio_changeToOutput(DIRECT_LINK_PORT,DIRECT_LINK_PIN);
       __NOP();
       hTimer_udelay(1);

       hGpio_write(DIRECT_LINK_PORT,DIRECT_LINK_PIN,hGPIO_PIN_HIGH);
       __NOP();
       hTimer_udelay(1);

       hGpio_changeToInput(DIRECT_LINK_PORT, DIRECT_LINK_PIN, 0);
       //hGpio_write(DIRECT_LINK_PORT,DIRECT_LINK_PIN,hGPIO_PIN_HIGH);
       hTimer_udelay(10);

       if(hGpio_read(DIRECT_LINK_PORT, DIRECT_LINK_PIN))
         {
           pirValue |= intBitMask;
         }
       intBitMask >>= 1;
     }
   pirValue &= 0x3FFF;

   longBitMask = 0x1000000;
   pirConfig = 0;
   for(i = 0; i < 25; i++)
     {
       hGpio_changeToOutput(DIRECT_LINK_PORT,DIRECT_LINK_PIN);
       hGpio_write(DIRECT_LINK_PORT,DIRECT_LINK_PIN,hGPIO_PIN_LOW);
       //hGpio_changeToOutput(DIRECT_LINK_PORT,DIRECT_LINK_PIN);
       __NOP();
       hTimer_udelay(1);

       hGpio_write(DIRECT_LINK_PORT,DIRECT_LINK_PIN,hGPIO_PIN_HIGH);
       __NOP();
       hTimer_udelay(1);

       hGpio_changeToInput(DIRECT_LINK_PORT, DIRECT_LINK_PIN, 0);
       //hGpio_write(DIRECT_LINK_PORT,DIRECT_LINK_PIN,hGPIO_PIN_HIGH);
       hTimer_udelay(10);

       if(hGpio_read(DIRECT_LINK_PORT, DIRECT_LINK_PIN))
         {
           pirConfig |= longBitMask;
         }
       longBitMask >>= 1;
     }
   hGpio_changeToOutput(DIRECT_LINK_PORT,DIRECT_LINK_PIN);
   hGpio_write(DIRECT_LINK_PORT,DIRECT_LINK_PIN,hGPIO_PIN_LOW);
   //hGpio_changeToOutput(DIRECT_LINK_PORT,DIRECT_LINK_PIN);
   hTimer_udelay(1);
   hGpio_changeToInput(DIRECT_LINK_PORT, DIRECT_LINK_PIN, 0);
   //hGpio_write(DIRECT_LINK_PORT,DIRECT_LINK_PIN,hGPIO_PIN_HIGH);
}

void pydAckTrigger(void)
{
  hGpio_write(DIRECT_LINK_PORT,DIRECT_LINK_PIN,hGPIO_PIN_LOW);
  hGpio_changeToOutput(DIRECT_LINK_PORT,DIRECT_LINK_PIN);
  hTimer_udelay(10);
  hGpio_disableInterrupt(DIRECT_LINK_PORT,DIRECT_LINK_PIN);
  hGpio_changeToInput(DIRECT_LINK_PORT, DIRECT_LINK_PIN, 0);
  hGpio_write(DIRECT_LINK_PORT,DIRECT_LINK_PIN,hGPIO_PIN_HIGH);
}




