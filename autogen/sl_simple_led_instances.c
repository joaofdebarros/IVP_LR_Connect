/***************************************************************************//**
 * @file
 * @brief LED Driver Instances
 *******************************************************************************
 * # License
 * <b>Copyright 2019 Silicon Laboratories Inc. www.silabs.com</b>
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

#include "sl_simple_led.h"
#include "sl_gpio.h"

#include "sl_simple_led_LED_AZUL_config.h"
#include "sl_simple_led_LED_VERDE_config.h"
#include "sl_simple_led_LED_VERMELHO_config.h"

sl_simple_led_context_t simple_led_azul_context = {
  .port = SL_SIMPLE_LED_LED_AZUL_PORT,
  .pin = SL_SIMPLE_LED_LED_AZUL_PIN,
  .polarity = SL_SIMPLE_LED_LED_AZUL_POLARITY,
};

const sl_led_t sl_led_led_azul = {
  .context = &simple_led_azul_context,
  .init = sl_simple_led_init,
  .turn_on = sl_simple_led_turn_on,
  .turn_off = sl_simple_led_turn_off,
  .toggle = sl_simple_led_toggle,
  .get_state = sl_simple_led_get_state,
};
sl_simple_led_context_t simple_led_verde_context = {
  .port = SL_SIMPLE_LED_LED_VERDE_PORT,
  .pin = SL_SIMPLE_LED_LED_VERDE_PIN,
  .polarity = SL_SIMPLE_LED_LED_VERDE_POLARITY,
};

const sl_led_t sl_led_led_verde = {
  .context = &simple_led_verde_context,
  .init = sl_simple_led_init,
  .turn_on = sl_simple_led_turn_on,
  .turn_off = sl_simple_led_turn_off,
  .toggle = sl_simple_led_toggle,
  .get_state = sl_simple_led_get_state,
};
sl_simple_led_context_t simple_led_vermelho_context = {
  .port = SL_SIMPLE_LED_LED_VERMELHO_PORT,
  .pin = SL_SIMPLE_LED_LED_VERMELHO_PIN,
  .polarity = SL_SIMPLE_LED_LED_VERMELHO_POLARITY,
};

const sl_led_t sl_led_led_vermelho = {
  .context = &simple_led_vermelho_context,
  .init = sl_simple_led_init,
  .turn_on = sl_simple_led_turn_on,
  .turn_off = sl_simple_led_turn_off,
  .toggle = sl_simple_led_toggle,
  .get_state = sl_simple_led_get_state,
};

const sl_led_t *sl_simple_led_array[] = {
  &sl_led_led_azul,
  &sl_led_led_verde,
  &sl_led_led_vermelho
};

void sl_simple_led_init_instances(void)
{
  sl_led_init(&sl_led_led_azul);
  sl_led_init(&sl_led_led_verde);
  sl_led_init(&sl_led_led_vermelho);
}
