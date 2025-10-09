/*
 * hSpi.h
 *
 *  Created on: July 17, 2024
 *      Author: diego.marinho
 */

#ifndef TI_HDRIVERS_HTIMER_H_
#define TI_HDRIVERS_HTIMER_H_

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "em_timer.h"
#include "em_cmu.h"
#include "ustimer.h"


#ifdef HRTOS_IS_PRESENT
#include "hRtos.h"
#endif

/*
 * Macros
 */


/*
 * Enumerates
 */

typedef enum{
    HTIMER_MODE_ONE_SHOT,
    HTIMER_MODE_PERIODIC
} hTimer_mode_e;

/*
 * typedefs
 */

typedef void* hTimer_t;

/*
 * Weak Callbacks
 */

void hTimer_Callback(uint32_t index);


/*
 * Prototypes
 */

hTimer_t hTimer_Create(uint32_t TimerIndex, uint32_t Freq, hTimer_mode_e Mode);

void hTimer_setConfig(TIMER_TypeDef *TIM, uint32_t Freq);

void hTimer_Start(TIMER_TypeDef *TIM);

void hTimer_Stop(TIMER_TypeDef *TIM);

void hTimer_enableInterrupt(hTimer_t handle);

void hTimer_disableInterrupt(hTimer_t handle);

uint32_t hTimer_getValue(hTimer_t handle);

void hTimer_Delete(hTimer_t handle);

void hTimer_udelay(float delay);


#endif
