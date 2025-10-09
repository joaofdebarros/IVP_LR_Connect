#include "sl_event_handler.h"

#include "sl_board_init.h"
#include "sl_clock_manager.h"
#include "sl_hfxo_manager.h"
#include "pa_conversions_efr32.h"
#include "sl_rail_util_power_manager_init.h"
#include "sl_rail_util_pti.h"
#include "app_framework_common.h"
#include "sl_fem_util.h"
#include "sl_board_control.h"
#include "app_log.h"
#include "sl-connect-watchdog.h"
#include "sl_debug_swo.h"
#include "sl_gpio.h"
#include "gpiointerrupt.h"
#include "sl_iostream_init_eusart_instances.h"
#include "sl_iostream_stdlib_config.h"
#include "sl_mbedtls.h"
#include "sl_simple_button_instances.h"
#include "sl_simple_led_instances.h"
#include "sl_cli_instances.h"
#include "psa/crypto.h"
#include "sl_se_manager.h"
#include "sl_iostream_init_instances.h"
#include "nvm3_default.h"
#include "sl_cos.h"
#include "sl_iostream_handles.h"

void sli_driver_permanent_allocation(void)
{
}

void sli_service_permanent_allocation(void)
{
}

void sli_stack_permanent_allocation(void)
{
}

void sli_internal_permanent_allocation(void)
{
}

void sl_platform_init(void)
{
  sl_board_preinit();
  sl_clock_manager_runtime_init();
  sl_hfxo_manager_init_hardware();
  sl_board_init();
  nvm3_initDefault();
}

void sli_internal_init_early(void)
{
}

void sl_driver_init(void)
{
  sl_debug_swo_init();
  sl_gpio_init();
  GPIOINT_Init();
  sl_simple_button_init_instances();
  sl_simple_led_init_instances();
  sl_cos_send_config();
}

void sl_service_init(void)
{
  sl_board_configure_vcom();
  sl_hfxo_manager_init();
  sl_connect_watchdog_init();
  sl_iostream_stdlib_disable_buffering();
  sl_mbedtls_init();
  psa_crypto_init();
  sl_se_init();
  sl_iostream_init_instances_stage_1();
  sl_iostream_init_instances_stage_2();
  sl_cli_instances_init();
}

void sl_stack_init(void)
{
  sl_rail_util_pa_init();
  sl_rail_util_power_manager_init();
  sl_rail_util_pti_init();
  connect_stack_init();
  connect_app_framework_init();
  connect_sleep_init();
  sl_fem_util_init();
}

void sl_internal_app_init(void)
{
  app_log_init();
}

void sli_platform_process_action(void)
{
}

void sli_service_process_action(void)
{
  sl_cli_instances_tick();
}

void sli_stack_process_action(void)
{
  connect_stack_tick();
  connect_app_framework_tick();
}

void sli_internal_app_process_action(void)
{
}

void sl_iostream_init_instances_stage_1(void)
{
  sl_iostream_eusart_init_instances();
}

void sl_iostream_init_instances_stage_2(void)
{
  sl_iostream_set_console_instance();
}

