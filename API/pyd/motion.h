/*
 * motion.h
 *
 *  Created on: 17 de mai de 2021
 *      Author: fausto.fujikawa
 */

#ifndef MOTION_H_
#define MOTION_H_

#include "pyd.h"
#include "boards/chipset/efr32.h"
#include "API/packet/pckDataStructure.h"

//-----------------------------------------------------------------------------
// Defines
//-----------------------------------------------------------------------------
#define MOTION_COUNTER_1S   100
#define MOTION_COUNTER_2S   2 * MOTION_COUNTER_1S
#define MOTION_COUNTER_5S   5 * MOTION_COUNTER_1S

//-----------------------------------------------------------------------------
// Variables
//-----------------------------------------------------------------------------
extern volatile uint8_t lastSensitivityMatched;
extern volatile uint16_t motionCounterTimer;

//-----------------------------------------------------------------------------
// Prototypes
//-----------------------------------------------------------------------------
void motionCheckSensitivy(void);
void motionDetected(void);

#endif /* MOTION_H_ */
