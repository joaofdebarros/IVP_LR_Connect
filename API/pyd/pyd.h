/*
 * pyd.h
 *
 *  Created on: 17 de mai de 2021
 *      Author: fausto.fujikawa
 */

#ifndef PYD_H_
#define PYD_H_

#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "motion.h"
#include "boards/chipset/efr32.h"
#include "stack/include/ember.h"

//-----------------------------------------------------------------------------
// Defines
//-----------------------------------------------------------------------------
#define PYD_MODE_FORCED      0
#define PYD_MODE_INT         1
#define PYD_MODE_WAKE_UP     2

#define PYD_SEN_VERY_LOW    250
#define PYD_SEN_LOW         50
#define PYD_SEN_MED         15
#define PYD_SEN_HIGH        5

//-----------------------------------------------------------------------------
// Variables
//-----------------------------------------------------------------------------
typedef union
{
    uint8_t byteConf;

    struct
    {
        uint8_t wdwTime     :2;
        uint8_t pulseCtr    :2;
        uint8_t blindTime   :4;
    } sAlarmConf;

    struct
    {
        uint8_t reserved1   :1;
        uint8_t hpf         :1;
        uint8_t reserved    :2;
        uint8_t signalSource :2;
        uint8_t opMode      :2;
    } sOpMode;

}
uByteConf;

typedef union
{
   uint32_t pydRegisters;

   struct
   {
      uint8_t pulseMode;
      uByteConf operationConf;
      uByteConf alarm;
      uint8_t thresholdVal;
   } sPYDType;

}
uPYDType;

extern uPYDType pydConf;

//-----------------------------------------------------------------------------
// Prototypes
//-----------------------------------------------------------------------------
void pydInit(uint8_t sensibilidade);
void pydConfig(uint32_t config);
void pydRead(void);
void pydAckTrigger(void);

#endif /* PYD_H_ */
