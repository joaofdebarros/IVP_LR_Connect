/*
 * hGpio_erf32.c
 *
 *  Created on: July 17, 2024
 *      Author: diego.marinho
 */
#include "hplatform/hDriver/hGpio.h"


#ifdef HDRIVER_MCU_EFR32


/* Drivers */
#include "em_gpio.h"
#include "gpiointerrupt.h"
/*
 * Weak Callback
 */

void __attribute__((weak)) hGpio_Callback(uint32_t pin){

}

/*
 * Callback
 */
void GPIO_EXTI_Callback(uint16_t GPIO_Pin){
  hGpio_Callback((uint32_t)GPIO_Pin);
}

void hGpio_write(uint32_t gpio, uint32_t pin, hGPIO_PIN_STATE_e e){
  if(e == hGPIO_PIN_LOW){
      GPIO_PinOutClear((GPIO_Port_TypeDef)gpio, (unsigned int)pin);
  }
  else if(e == hGPIO_PIN_HIGH){
      GPIO_PinOutSet((GPIO_Port_TypeDef)gpio, (unsigned int)pin);
  }
}

void hGpio_toggle(uint32_t gpio, uint32_t pin){
  GPIO_PinOutToggle((GPIO_Port_TypeDef)gpio, (unsigned int)pin);
}

void hGpio_ledToggle(const sl_led_t *led_handle, bool uEconomic){
  if(uEconomic){
      sl_led_toggle(led_handle);
  }else{
      sl_led_turn_off(led_handle);
  }
}

void hGpio_ledTurnOn(const sl_led_t *led_handle, bool uEconomic){
  if(uEconomic){
      sl_led_turn_on(led_handle);
  }else{
      sl_led_turn_off(led_handle);
  }
}

void hGpio_ledTurnOff(const sl_led_t *led_handle, bool uEconomic){
  sl_led_turn_off(led_handle);
}

hGPIO_PIN_STATE_e hGpio_read(uint32_t gpio, uint32_t pin){
  hGPIO_PIN_STATE_e bitstatus;
  bitstatus = GPIO_PinInGet((GPIO_Port_TypeDef)gpio, (unsigned int)pin);
  return bitstatus;
}

void hGpio_changeToOutput(uint32_t gpio, uint32_t pin){
  GPIO_PinModeSet((GPIO_Port_TypeDef)gpio, (unsigned int)pin,gpioModePushPull,0);
}

void hGpio_changeToInput(uint32_t gpio, uint32_t pin, hGPIO_INTERRUPT_e e){
  GPIO_PinModeSet((GPIO_Port_TypeDef)gpio,(unsigned int)pin,gpioModeInput,0);
}

void hGpio_enableInterrupt(uint32_t gpio, uint32_t pin){
  GPIO_ExtIntConfig((GPIO_Port_TypeDef)gpio,
                    (unsigned int)pin,
                    (unsigned int)pin,
                    true,
                    false,
                    true);
}

void hGpio_disableInterrupt(uint32_t gpio, uint32_t pin){
  //GPIOINT_CallbackUnRegister((unsigned int)pin);
  GPIO_ExtIntConfig((GPIO_Port_TypeDef)gpio,
                    (unsigned int)pin,
                    (unsigned int)pin,
                    false,
                    false,
                    false);
}

#endif


