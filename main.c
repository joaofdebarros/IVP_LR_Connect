/***************************************************************************//**
 * @file main.c
 * @brief main() function.
 *******************************************************************************
 * # License
 * <b>Copyright 2025 Silicon Laboratories Inc. www.silabs.com</b>
 *******************************************************************************
 *
 * SPDX-License-Identifier: Zlib
 *
 * The licensor of this software is Silicon Laboratories Inc.
 *
 * This software is provided 'as-is', without any express or implied
 * warranty. In no event will the authors be held liable for any damages
 * arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software. If you use this software
 *    in a product, an acknowledgment in the product documentation would be
 *    appreciated but is not required.
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 * 3. This notice may not be removed or altered from any source distribution.
 *
 ******************************************************************************/
#include "sl_component_catalog.h"
#include "sl_main_init.h"
#if defined(SL_CATALOG_POWER_MANAGER_PRESENT)
#include "sl_power_manager.h"
#endif
#if defined(SL_CATALOG_KERNEL_PRESENT)
#include "sl_main_kernel.h"
#else // SL_CATALOG_KERNEL_PRESENT
#include "sl_main_process_action.h"
#endif // SL_CATALOG_KERNEL_PRESENT

#include "gpiointerrupt.h"
#include "API/hNetwork.h"
#include "hplatform/hDriver/hGpio.h"
#include "API/pyd/pyd.h"
#include "poll.h"
#include "hplatform/hDriver/hADC.h"
#include "API/memory/memory.h"

uint8_t tx_power = 0;

static void gpioSetup(void);
void CallbackGPIO(uint8_t interrupt_no);
static void timerSetup(void);

int main(void)
{
  // Initialize Silicon Labs device, system, service(s) and protocol stack(s).
  // Note that if the kernel is present, the start task will be started and software
  // component initialization will take place there.

  sl_main_init();

  app_button_press_enable();

  sl_mx25_flash_shutdown();

  gpioSetup();
  timerSetup();
  set_tx(tx_power);
  iadcInit();

#if defined(SL_CATALOG_KERNEL_PRESENT)
  // Start the kernel. The start task will be executed (Highest priority) to complete
  // the Simplicity SDK components initialization and the user app_init() hook function will be called.
  sl_main_kernel_start();
#else // SL_CATALOG_KERNEL_PRESENT

  // User provided code.
  app_init();

  while (1) {
    // Silicon Labs components process action routine
    // must be called from the super loop.
    sl_main_process_action();

    // User provided code. Application process.
    app_process_action();

#if defined(SL_CATALOG_POWER_MANAGER_PRESENT)
    // Let the CPU go to sleep if the system allows it.
    sl_power_manager_sleep();
#endif
  }
#endif // SL_CATALOG_KERNEL_PRESENT
}

static void gpioSetup(void){
  GPIO_PinModeSet(SER_IN_PORT, SER_IN_PIN, gpioModePushPull, 0);
  GPIO_PinModeSet(SENSE_LOW_PORT, SENSE_LOW_PIN, gpioModePushPull, 1);
  // Configure Button PB0 as input and enable interrupt
  //GPIO_PinModeSet(DIRECT_LINK_PORT, DIRECT_LINK_PIN, gpioModeInputPull, 1);
  GPIO_PinModeSet(DIRECT_LINK_PORT, DIRECT_LINK_PIN, gpioModeInput, 0);
  GPIO_ExtIntConfig(DIRECT_LINK_PORT,
                    DIRECT_LINK_PIN,
                    DIRECT_LINK_PIN,
                    true,
                    false,
                    true);

  GPIOINT_CallbackRegister((uint8_t)DIRECT_LINK_PIN,(GPIOINT_IrqCallbackPtr_t)CallbackGPIO);

  // Enable EVEN interrupt to catch button press that changes slew rate
  NVIC_ClearPendingIRQ(GPIO_EVEN_IRQn);
  NVIC_EnableIRQ(GPIO_EVEN_IRQn);
}

static void timerSetup(void){
  USTIMER_Init();
}

void CallbackGPIO(uint8_t interrupt_no){
      GPIO_EXTI_Callback(interrupt_no);
}

