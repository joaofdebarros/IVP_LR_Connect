/*
 * hTimer_stm32l.c
 *
 *  Created on: July 17, 2024
 *      Author: diego.marinho
 */

#include "hplatform/hDriver/hTimer.h"

#ifdef HDRIVER_MCU_EFR32
/* Drivers */


/*
 * Macros
 */

#ifndef HTIMER_HARDWARE_PERIPHERALS
#define HTIMER_HARDWARE_PERIPHERALS 4
#endif

#define CLK_TIM      2.097E6


/*
 * Enumerates
 */



/*
 * Structs and Unions
 */

typedef struct{
    uint32_t index;
    uint32_t freq;
    hTimer_mode_e mode;
    TIMER_TypeDef   *handle;
    uint8_t loaded;
}hTimer_struct_t;

static hTimer_struct_t Timer_Handles[HTIMER_HARDWARE_PERIPHERALS] = {0};

/*
 * Weak Callbacks
 */

void __attribute__((weak)) hTimer_Callback(uint32_t index){

}

/*
 * Prototypes
 */

hTimer_t hTimer_Create(uint32_t TimerIndex, uint32_t Freq, hTimer_mode_e Mode){
  hTimer_struct_t *u;
  u->handle = (TIMER_TypeDef*)TimerIndex;
  u->index = TimerIndex;
  return (hTimer_struct_t*)u;
}

void hTimer_setConfig(TIMER_TypeDef *TIM, uint32_t Freq){
  TIMER_Init_TypeDef timerInit     = TIMER_INIT_DEFAULT;
  timerInit.enable = false;


  CMU_ClockEnable(cmuClock_TIMER0, true);
  TIMER_Init(TIM, &timerInit);

  volatile uint32_t timerfreq = CMU_ClockFreqGet(cmuClock_TIMER0);
  volatile uint32_t timerTopval = timerfreq/Freq;
  TIMER_TopSet(TIM, timerTopval);

 TIMER_IntEnable(TIM, TIMER_IEN_OF);
  NVIC_EnableIRQ(TIMER0_IRQn);
}

void hTimer_Start(TIMER_TypeDef *TIM){
  uint32_t flags = TIMER_IntGet(TIM);
  TIMER_IntClear(TIM, flags);
  TIMER_Enable(TIM, true);
}

void hTimer_Stop(TIMER_TypeDef *TIM){
  uint32_t flags = TIMER_IntGet(TIM);
  TIMER_IntClear(TIM, flags);
  TIMER_Enable(TIM, false);
}

//void TIMER_IRQHandlerx(void)
//{
//  uint32_t flags = TIMER_IntGet(TIMER0);
//  TIMER_IntClear(TIMER0, flags);
//
//  hTimer_Callback(0);
//}

void hTimer_udelay(uint32_t delay){
  USTIMER_Delay(delay);
//  sl_sleeptimer_delay_millisecond(delay/1000);
}

#endif

#ifdef HDRIVER_MCU_STM32L

/* Drivers */
#include "stm32l0xx_hal_tim.h"

/*
 * Macros
 */

#ifndef HTIMER_HARDWARE_PERIPHERALS
#define HTIMER_HARDWARE_PERIPHERALS 4
#endif

#define CLK_TIM      2.097E6

/*
 * Enumerates
 */



/*
 * Structs and Unions
 */

typedef struct{
    uint32_t index;
    uint32_t freq;
    hTimer_mode_e mode;
    TIM_HandleTypeDef   *handle;
    uint8_t loaded;
}hTimer_struct_t;

static hTimer_struct_t Timer_Handles[HTIMER_HARDWARE_PERIPHERALS] = {0};

/*
 * Weak Callbacks
 */

void __attribute__((weak)) hTimer_Callback(uint32_t index){

}

/*
 * Private Callbacks
 */

hTimer_struct_t *__timer_get_free(){
    uint8_t i;
    hTimer_struct_t *ret = NULL;

    for (i=0; i<HTIMER_HARDWARE_PERIPHERALS; i++){
        if (Timer_Handles[i].loaded == 0){
            ret = &Timer_Handles[i];
            break;
        }
    }

    return ret;
}

hTimer_struct_t *__timer_get_handle(TIM_HandleTypeDef   *handle){
    uint8_t i;
    hTimer_struct_t *ret = NULL;

    for (i=0; i<HTIMER_HARDWARE_PERIPHERALS; i++){
        if (Timer_Handles[i].handle == handle){
            ret = &Timer_Handles[i];
            break;
        }
    }

    return ret;
}

//void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){
//    hTimer_struct_t *s;
//
//    s = __timer_get_handle(htim);
//    if (s != NULL){
//        hTimer_Callback(s->index);
//    }
//}

/*
 * Prototypes
 */

hTimer_t hTimer_Create(uint32_t TimerIndex, uint32_t Freq, hTimer_mode_e Mode){
    hTimer_struct_t *u;

    u = __timer_get_free();
    if (u != NULL){
    	u->handle = (TIM_HandleTypeDef*)TimerIndex;
    	u->index = TimerIndex;
    	u->freq = Freq;
    	if (Mode == HTIMER_MODE_ONE_SHOT){
    		HAL_TIM_OnePulse_Init(u->handle, TIM_OPMODE_SINGLE);
    	}
    	u->handle->Init.Period = (CLK_TIM/(u->handle->Init.Prescaler*u->freq)) - 1;
    	u->loaded = 1;
    	HAL_TIM_Base_Init(u->handle);
    }
    return (hTimer_struct_t*)u;
}

void hTimer_setConfig(hTimer_t handle, uint16_t prescaler, uint32_t Freq){
    hTimer_struct_t *u;

    u = (hTimer_struct_t*)handle;
    if (u != NULL){
    	u->freq = Freq;
    	u->handle->Init.Prescaler = prescaler;
    	u->handle->Init.Period = (CLK_TIM/(u->handle->Init.Prescaler*u->freq)) - 1;
    	HAL_TIM_Base_Init(u->handle);
    }
}

void hTimer_Start(hTimer_t handle){
    hTimer_struct_t *u;

    u = (hTimer_struct_t*)handle;
    if (u != NULL){
    	HAL_TIM_Base_Start(u->handle);
    }
}

void hTimer_Stop(hTimer_t handle){
    hTimer_struct_t *u;

    u = (hTimer_struct_t*)handle;
    if (u != NULL){
    	HAL_TIM_Base_Stop(u->handle);
    }
}

void hTimer_enableInterrupt(hTimer_t handle){
    hTimer_struct_t *u;

    u = (hTimer_struct_t*)handle;
    if (u != NULL){
    	HAL_TIM_Base_Start_IT(u->handle);
    }
}

void hTimer_disableInterrupt(hTimer_t handle){
    hTimer_struct_t *u;

    u = (hTimer_struct_t*)handle;
    if (u != NULL){
        HAL_TIM_Base_Stop_IT(u->handle);
    }
}

void hTimer_Delete(hTimer_t handle){
    hTimer_struct_t *u;

    u = (hTimer_struct_t*)handle;
    if (u != NULL){
        HAL_TIM_Base_DeInit(u->handle);
    }
}

uint32_t hTimer_getValue(hTimer_t handle){
    uint32_t ret;
    hTimer_struct_t *u;

    ret = 0;
    u = (hTimer_struct_t*)handle;
    if (u != NULL){
    	ret = u->handle->Instance->CNT;
    }
    return ret;
}

#endif

