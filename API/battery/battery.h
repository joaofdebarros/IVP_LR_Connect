/*
 * battery.h
 *
 *  Created on: 19 de nov. de 2024
 *      Author: diego.marinho
 */

#ifndef BATTERY_BATTERY_H_
#define BATTERY_BATTERY_H_

#include "stdint.h"
#include "hplatform/hDriver/hADC.h"

typedef struct{
  uint16_t VBAT;
}battery_t;

extern battery_t battery;

uint32_t iadcRead(void);
uint32_t calculateVdd(void);


#endif /* BATTERY_BATTERY_H_ */
