################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include simplicity_sdk_2025.6.2/util/third_party/printf/src/subdir.mk
-include simplicity_sdk_2025.6.2/util/third_party/printf/subdir.mk
-include simplicity_sdk_2025.6.2/util/third_party/mbedtls/library/subdir.mk
-include simplicity_sdk_2025.6.2/util/silicon_labs/silabs_core/buffer_manager/subdir.mk
-include simplicity_sdk_2025.6.2/protocol/flex/stack/framework/subdir.mk
-include simplicity_sdk_2025.6.2/protocol/flex/stack/core/subdir.mk
-include simplicity_sdk_2025.6.2/protocol/flex/stack/config/subdir.mk
-include simplicity_sdk_2025.6.2/protocol/flex/poll/subdir.mk
-include simplicity_sdk_2025.6.2/protocol/flex/app-framework-common/subdir.mk
-include simplicity_sdk_2025.6.2/platform/service/udelay/src/subdir.mk
-include simplicity_sdk_2025.6.2/platform/service/token_manager/legacy/src/subdir.mk
-include simplicity_sdk_2025.6.2/platform/service/sleeptimer/src/subdir.mk
-include simplicity_sdk_2025.6.2/platform/service/sl_main/src/subdir.mk
-include simplicity_sdk_2025.6.2/platform/service/power_manager/src/sleep_loop/subdir.mk
-include simplicity_sdk_2025.6.2/platform/service/power_manager/src/common/subdir.mk
-include simplicity_sdk_2025.6.2/platform/service/mpu/src/subdir.mk
-include simplicity_sdk_2025.6.2/platform/service/memory_manager/src/subdir.mk
-include simplicity_sdk_2025.6.2/platform/service/iostream/src/subdir.mk
-include simplicity_sdk_2025.6.2/platform/service/interrupt_manager/src/subdir.mk
-include simplicity_sdk_2025.6.2/platform/service/hfxo_manager/src/subdir.mk
-include simplicity_sdk_2025.6.2/platform/service/device_manager/src/subdir.mk
-include simplicity_sdk_2025.6.2/platform/service/device_manager/devices/subdir.mk
-include simplicity_sdk_2025.6.2/platform/service/device_manager/clocks/subdir.mk
-include simplicity_sdk_2025.6.2/platform/service/device_init/src/subdir.mk
-include simplicity_sdk_2025.6.2/platform/service/clock_manager/src/subdir.mk
-include simplicity_sdk_2025.6.2/platform/service/cli/src/subdir.mk
-include simplicity_sdk_2025.6.2/platform/security/sl_component/sl_psa_driver/src/subdir.mk
-include simplicity_sdk_2025.6.2/platform/security/sl_component/sl_mbedtls_support/src/subdir.mk
-include simplicity_sdk_2025.6.2/platform/security/sl_component/se_manager/src/subdir.mk
-include simplicity_sdk_2025.6.2/platform/radio/rail_lib/plugin/rail_util_pti/subdir.mk
-include simplicity_sdk_2025.6.2/platform/radio/rail_lib/plugin/rail_util_power_manager_init/subdir.mk
-include simplicity_sdk_2025.6.2/platform/radio/rail_lib/plugin/pa-conversions/subdir.mk
-include simplicity_sdk_2025.6.2/platform/radio/rail_lib/plugin/fem_util/subdir.mk
-include simplicity_sdk_2025.6.2/platform/peripheral/src/subdir.mk
-include simplicity_sdk_2025.6.2/platform/emlib/src/subdir.mk
-include simplicity_sdk_2025.6.2/platform/emdrv/ustimer/src/subdir.mk
-include simplicity_sdk_2025.6.2/platform/emdrv/nvm3/src/subdir.mk
-include simplicity_sdk_2025.6.2/platform/emdrv/gpiointerrupt/src/subdir.mk
-include simplicity_sdk_2025.6.2/platform/emdrv/dmadrv/src/subdir.mk
-include simplicity_sdk_2025.6.2/platform/driver/leddrv/src/subdir.mk
-include simplicity_sdk_2025.6.2/platform/driver/gpio/src/subdir.mk
-include simplicity_sdk_2025.6.2/platform/driver/debug/src/subdir.mk
-include simplicity_sdk_2025.6.2/platform/driver/button/src/subdir.mk
-include simplicity_sdk_2025.6.2/platform/common/src/subdir.mk
-include simplicity_sdk_2025.6.2/platform/Device/SiliconLabs/FGM23/Source/subdir.mk
-include simplicity_sdk_2025.6.2/hardware/driver/mx25_flash_shutdown/src/sl_mx25_flash_shutdown_eusart/subdir.mk
-include simplicity_sdk_2025.6.2/hardware/driver/configuration_over_swo/src/subdir.mk
-include simplicity_sdk_2025.6.2/hardware/board/src/subdir.mk
-include simplicity_sdk_2025.6.2/app/common/util/app_rta/src/bm/subdir.mk
-include simplicity_sdk_2025.6.2/app/common/util/app_queue/subdir.mk
-include simplicity_sdk_2025.6.2/app/common/util/app_log/subdir.mk
-include simplicity_sdk_2025.6.2/app/common/util/app_button_press/subdir.mk
-include privAPI/subdir.mk
-include hplatform/hDriver/source/subdir.mk
-include boards/chipset/subdir.mk
-include autogen/subdir.mk
-include Application/subdir.mk
-include API/pyd/subdir.mk
-include API/packet/subdir.mk
-include API/memory/subdir.mk
-include API/battery/subdir.mk
-include API/PacketRadio/subdir.mk
-include API/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

OPTIONAL_TOOL_DEPS := \
$(wildcard ../makefile.defs) \
$(wildcard ../makefile.init) \
$(wildcard ../makefile.targets) \


BUILD_ARTIFACT_NAME := IVP_LR_Connect
BUILD_ARTIFACT_EXTENSION := axf
BUILD_ARTIFACT_PREFIX :=
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: main-build

# Main-build Target
main-build: IVP_LR_Connect.axf

# Tool invocations
IVP_LR_Connect.axf: $(OBJS) $(USER_OBJS) makefile objects.mk $(OPTIONAL_TOOL_DEPS)
	@echo 'Building target: $@'
	@echo 'Invoking: GNU ARM C Linker'
	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m33 -mthumb -T "C:\Users\joao.victor\SimplicityStudio\v5_workspace\IVP_LR_Connect\autogen\linkerfile.ld" -Wl,--wrap=_free_r -Wl,--wrap=_malloc_r -Wl,--wrap=_calloc_r -Wl,--wrap=_realloc_r -fno-lto -Wl,--no-warn-rwx-segments -Xlinker --gc-sections -Xlinker -Map="IVP_LR_Connect.map" -mfpu=fpv5-sp-d16 -mfloat-abi=hard --specs=nano.specs -o IVP_LR_Connect.axf -Wl,--start-group "./API/PacketRadio/packetRadio.o" "./API/battery/battery.o" "./API/hNetwork.o" "./API/memory/memory.o" "./API/packet/packet.o" "./API/pyd/motion.o" "./API/pyd/pyd.o" "./Application/application.o" "./Application/callbacks.o" "./app_cli.o" "./app_init.o" "./app_process.o" "./main.o" "./autogen/app_framework_event_table.o" "./autogen/app_rta_init.o" "./autogen/callback_dispatcher.o" "./autogen/rail_config.o" "./autogen/sl_board_default_init.o" "./autogen/sl_cli_command_table.o" "./autogen/sl_cli_instances.o" "./autogen/sl_event_handler.o" "./autogen/sl_iostream_handles.o" "./autogen/sl_iostream_init_eusart_instances.o" "./autogen/sl_power_manager_handler.o" "./autogen/sl_simple_button_instances.o" "./autogen/sl_simple_led_instances.o" "./autogen/sli_cli_hooks.o" "./boards/chipset/efr32.o" "./hplatform/hDriver/source/hADC_efr32.o" "./hplatform/hDriver/source/hGpio_erf32.o" "./hplatform/hDriver/source/hTimer_efr32.o" "./privAPI/Radio.o" "./privAPI/privCallback.o" "./simplicity_sdk_2025.6.2/app/common/util/app_button_press/app_button_press.o" "./simplicity_sdk_2025.6.2/app/common/util/app_log/app_log.o" "./simplicity_sdk_2025.6.2/app/common/util/app_queue/app_queue.o" "./simplicity_sdk_2025.6.2/app/common/util/app_rta/src/bm/app_rta_bm.o" "./simplicity_sdk_2025.6.2/hardware/board/src/sl_board_control_gpio.o" "./simplicity_sdk_2025.6.2/hardware/board/src/sl_board_init.o" "./simplicity_sdk_2025.6.2/hardware/driver/configuration_over_swo/src/sl_cos.o" "./simplicity_sdk_2025.6.2/hardware/driver/mx25_flash_shutdown/src/sl_mx25_flash_shutdown_eusart/sl_mx25_flash_shutdown.o" "./simplicity_sdk_2025.6.2/platform/Device/SiliconLabs/FGM23/Source/startup_fgm23.o" "./simplicity_sdk_2025.6.2/platform/Device/SiliconLabs/FGM23/Source/system_fgm23.o" "./simplicity_sdk_2025.6.2/platform/common/src/sl_assert.o" "./simplicity_sdk_2025.6.2/platform/common/src/sl_core_cortexm.o" "./simplicity_sdk_2025.6.2/platform/common/src/sl_slist.o" "./simplicity_sdk_2025.6.2/platform/common/src/sl_string.o" "./simplicity_sdk_2025.6.2/platform/common/src/sl_syscalls.o" "./simplicity_sdk_2025.6.2/platform/driver/button/src/sl_button.o" "./simplicity_sdk_2025.6.2/platform/driver/button/src/sl_simple_button.o" "./simplicity_sdk_2025.6.2/platform/driver/debug/src/sl_debug_swo.o" "./simplicity_sdk_2025.6.2/platform/driver/gpio/src/sl_gpio.o" "./simplicity_sdk_2025.6.2/platform/driver/leddrv/src/sl_led.o" "./simplicity_sdk_2025.6.2/platform/driver/leddrv/src/sl_simple_led.o" "./simplicity_sdk_2025.6.2/platform/emdrv/dmadrv/src/dmadrv.o" "./simplicity_sdk_2025.6.2/platform/emdrv/gpiointerrupt/src/gpiointerrupt.o" "./simplicity_sdk_2025.6.2/platform/emdrv/nvm3/src/nvm3.o" "./simplicity_sdk_2025.6.2/platform/emdrv/nvm3/src/nvm3_cache.o" "./simplicity_sdk_2025.6.2/platform/emdrv/nvm3/src/nvm3_default_common_linker.o" "./simplicity_sdk_2025.6.2/platform/emdrv/nvm3/src/nvm3_hal_flash.o" "./simplicity_sdk_2025.6.2/platform/emdrv/nvm3/src/nvm3_lock.o" "./simplicity_sdk_2025.6.2/platform/emdrv/nvm3/src/nvm3_object.o" "./simplicity_sdk_2025.6.2/platform/emdrv/nvm3/src/nvm3_page.o" "./simplicity_sdk_2025.6.2/platform/emdrv/nvm3/src/nvm3_utils.o" "./simplicity_sdk_2025.6.2/platform/emdrv/ustimer/src/ustimer.o" "./simplicity_sdk_2025.6.2/platform/emlib/src/em_burtc.o" "./simplicity_sdk_2025.6.2/platform/emlib/src/em_cmu.o" "./simplicity_sdk_2025.6.2/platform/emlib/src/em_emu.o" "./simplicity_sdk_2025.6.2/platform/emlib/src/em_eusart.o" "./simplicity_sdk_2025.6.2/platform/emlib/src/em_gpio.o" "./simplicity_sdk_2025.6.2/platform/emlib/src/em_iadc.o" "./simplicity_sdk_2025.6.2/platform/emlib/src/em_ldma.o" "./simplicity_sdk_2025.6.2/platform/emlib/src/em_msc.o" "./simplicity_sdk_2025.6.2/platform/emlib/src/em_prs.o" "./simplicity_sdk_2025.6.2/platform/emlib/src/em_rmu.o" "./simplicity_sdk_2025.6.2/platform/emlib/src/em_system.o" "./simplicity_sdk_2025.6.2/platform/emlib/src/em_timer.o" "./simplicity_sdk_2025.6.2/platform/emlib/src/em_wdog.o" "./simplicity_sdk_2025.6.2/platform/peripheral/src/sl_hal_eusart.o" "./simplicity_sdk_2025.6.2/platform/peripheral/src/sl_hal_gpio.o" "./simplicity_sdk_2025.6.2/platform/peripheral/src/sl_hal_prs.o" "./simplicity_sdk_2025.6.2/platform/peripheral/src/sl_hal_sysrtc.o" "./simplicity_sdk_2025.6.2/platform/radio/rail_lib/plugin/fem_util/sl_fem_util.o" "./simplicity_sdk_2025.6.2/platform/radio/rail_lib/plugin/pa-conversions/pa_conversions_efr32.o" "./simplicity_sdk_2025.6.2/platform/radio/rail_lib/plugin/rail_util_power_manager_init/sl_rail_util_power_manager_init.o" "./simplicity_sdk_2025.6.2/platform/radio/rail_lib/plugin/rail_util_pti/sl_rail_util_pti.o" "./simplicity_sdk_2025.6.2/platform/security/sl_component/se_manager/src/sl_se_manager.o" "./simplicity_sdk_2025.6.2/platform/security/sl_component/se_manager/src/sl_se_manager_attestation.o" "./simplicity_sdk_2025.6.2/platform/security/sl_component/se_manager/src/sl_se_manager_cipher.o" "./simplicity_sdk_2025.6.2/platform/security/sl_component/se_manager/src/sl_se_manager_entropy.o" "./simplicity_sdk_2025.6.2/platform/security/sl_component/se_manager/src/sl_se_manager_hash.o" "./simplicity_sdk_2025.6.2/platform/security/sl_component/se_manager/src/sl_se_manager_key_derivation.o" "./simplicity_sdk_2025.6.2/platform/security/sl_component/se_manager/src/sl_se_manager_key_handling.o" "./simplicity_sdk_2025.6.2/platform/security/sl_component/se_manager/src/sl_se_manager_signature.o" "./simplicity_sdk_2025.6.2/platform/security/sl_component/se_manager/src/sl_se_manager_util.o" "./simplicity_sdk_2025.6.2/platform/security/sl_component/se_manager/src/sli_se_manager_mailbox.o" "./simplicity_sdk_2025.6.2/platform/security/sl_component/sl_mbedtls_support/src/mbedtls_ccm.o" "./simplicity_sdk_2025.6.2/platform/security/sl_component/sl_mbedtls_support/src/se_aes.o" "./simplicity_sdk_2025.6.2/platform/security/sl_component/sl_mbedtls_support/src/sl_mbedtls.o" "./simplicity_sdk_2025.6.2/platform/security/sl_component/sl_mbedtls_support/src/sl_psa_crypto.o" "./simplicity_sdk_2025.6.2/platform/security/sl_component/sl_mbedtls_support/src/sli_psa_crypto.o" "./simplicity_sdk_2025.6.2/platform/security/sl_component/sl_psa_driver/src/sl_psa_its_nvm3.o" "./simplicity_sdk_2025.6.2/platform/security/sl_component/sl_psa_driver/src/sli_psa_driver_common.o" "./simplicity_sdk_2025.6.2/platform/security/sl_component/sl_psa_driver/src/sli_psa_driver_init.o" "./simplicity_sdk_2025.6.2/platform/security/sl_component/sl_psa_driver/src/sli_psa_trng.o" "./simplicity_sdk_2025.6.2/platform/security/sl_component/sl_psa_driver/src/sli_se_driver_aead.o" "./simplicity_sdk_2025.6.2/platform/security/sl_component/sl_psa_driver/src/sli_se_driver_builtin_keys.o" "./simplicity_sdk_2025.6.2/platform/security/sl_component/sl_psa_driver/src/sli_se_driver_cipher.o" "./simplicity_sdk_2025.6.2/platform/security/sl_component/sl_psa_driver/src/sli_se_driver_key_derivation.o" "./simplicity_sdk_2025.6.2/platform/security/sl_component/sl_psa_driver/src/sli_se_driver_key_management.o" "./simplicity_sdk_2025.6.2/platform/security/sl_component/sl_psa_driver/src/sli_se_driver_mac.o" "./simplicity_sdk_2025.6.2/platform/security/sl_component/sl_psa_driver/src/sli_se_driver_signature.o" "./simplicity_sdk_2025.6.2/platform/security/sl_component/sl_psa_driver/src/sli_se_opaque_driver_aead.o" "./simplicity_sdk_2025.6.2/platform/security/sl_component/sl_psa_driver/src/sli_se_opaque_driver_cipher.o" "./simplicity_sdk_2025.6.2/platform/security/sl_component/sl_psa_driver/src/sli_se_opaque_driver_mac.o" "./simplicity_sdk_2025.6.2/platform/security/sl_component/sl_psa_driver/src/sli_se_opaque_key_derivation.o" "./simplicity_sdk_2025.6.2/platform/security/sl_component/sl_psa_driver/src/sli_se_transparent_driver_aead.o" "./simplicity_sdk_2025.6.2/platform/security/sl_component/sl_psa_driver/src/sli_se_transparent_driver_cipher.o" "./simplicity_sdk_2025.6.2/platform/security/sl_component/sl_psa_driver/src/sli_se_transparent_driver_hash.o" "./simplicity_sdk_2025.6.2/platform/security/sl_component/sl_psa_driver/src/sli_se_transparent_driver_mac.o" "./simplicity_sdk_2025.6.2/platform/security/sl_component/sl_psa_driver/src/sli_se_transparent_key_derivation.o" "./simplicity_sdk_2025.6.2/platform/security/sl_component/sl_psa_driver/src/sli_se_version_dependencies.o" "./simplicity_sdk_2025.6.2/platform/service/cli/src/sl_cli.o" "./simplicity_sdk_2025.6.2/platform/service/cli/src/sl_cli_arguments.o" "./simplicity_sdk_2025.6.2/platform/service/cli/src/sl_cli_command.o" "./simplicity_sdk_2025.6.2/platform/service/cli/src/sl_cli_input.o" "./simplicity_sdk_2025.6.2/platform/service/cli/src/sl_cli_io.o" "./simplicity_sdk_2025.6.2/platform/service/cli/src/sl_cli_tokenize.o" "./simplicity_sdk_2025.6.2/platform/service/clock_manager/src/sl_clock_manager.o" "./simplicity_sdk_2025.6.2/platform/service/clock_manager/src/sl_clock_manager_hal_s2.o" "./simplicity_sdk_2025.6.2/platform/service/clock_manager/src/sl_clock_manager_init.o" "./simplicity_sdk_2025.6.2/platform/service/clock_manager/src/sl_clock_manager_init_hal_s2.o" "./simplicity_sdk_2025.6.2/platform/service/device_init/src/sl_device_init_dcdc_s2.o" "./simplicity_sdk_2025.6.2/platform/service/device_manager/clocks/sl_device_clock_efr32xg23.o" "./simplicity_sdk_2025.6.2/platform/service/device_manager/devices/sl_device_peripheral_hal_efr32xg23.o" "./simplicity_sdk_2025.6.2/platform/service/device_manager/src/sl_device_clock.o" "./simplicity_sdk_2025.6.2/platform/service/device_manager/src/sl_device_gpio.o" "./simplicity_sdk_2025.6.2/platform/service/device_manager/src/sl_device_peripheral.o" "./simplicity_sdk_2025.6.2/platform/service/hfxo_manager/src/sl_hfxo_manager.o" "./simplicity_sdk_2025.6.2/platform/service/hfxo_manager/src/sl_hfxo_manager_hal_s2.o" "./simplicity_sdk_2025.6.2/platform/service/interrupt_manager/src/sl_interrupt_manager_cortexm.o" "./simplicity_sdk_2025.6.2/platform/service/iostream/src/sl_iostream.o" "./simplicity_sdk_2025.6.2/platform/service/iostream/src/sl_iostream_eusart.o" "./simplicity_sdk_2025.6.2/platform/service/iostream/src/sl_iostream_retarget_stdio.o" "./simplicity_sdk_2025.6.2/platform/service/iostream/src/sl_iostream_stdlib_config.o" "./simplicity_sdk_2025.6.2/platform/service/iostream/src/sl_iostream_uart.o" "./simplicity_sdk_2025.6.2/platform/service/memory_manager/src/sl_memory_manager.o" "./simplicity_sdk_2025.6.2/platform/service/memory_manager/src/sl_memory_manager_dynamic_reservation.o" "./simplicity_sdk_2025.6.2/platform/service/memory_manager/src/sl_memory_manager_pool.o" "./simplicity_sdk_2025.6.2/platform/service/memory_manager/src/sl_memory_manager_pool_common.o" "./simplicity_sdk_2025.6.2/platform/service/memory_manager/src/sl_memory_manager_region.o" "./simplicity_sdk_2025.6.2/platform/service/memory_manager/src/sl_memory_manager_retarget.o" "./simplicity_sdk_2025.6.2/platform/service/memory_manager/src/sli_memory_manager_common.o" "./simplicity_sdk_2025.6.2/platform/service/mpu/src/sl_mpu_s2.o" "./simplicity_sdk_2025.6.2/platform/service/power_manager/src/common/sl_power_manager_common.o" "./simplicity_sdk_2025.6.2/platform/service/power_manager/src/common/sl_power_manager_em4.o" "./simplicity_sdk_2025.6.2/platform/service/power_manager/src/sleep_loop/sl_power_manager.o" "./simplicity_sdk_2025.6.2/platform/service/power_manager/src/sleep_loop/sl_power_manager_debug.o" "./simplicity_sdk_2025.6.2/platform/service/power_manager/src/sleep_loop/sl_power_manager_hal_s2.o" "./simplicity_sdk_2025.6.2/platform/service/sl_main/src/sl_main_init.o" "./simplicity_sdk_2025.6.2/platform/service/sl_main/src/sl_main_init_memory.o" "./simplicity_sdk_2025.6.2/platform/service/sl_main/src/sl_main_process_action.o" "./simplicity_sdk_2025.6.2/platform/service/sleeptimer/src/sl_sleeptimer.o" "./simplicity_sdk_2025.6.2/platform/service/sleeptimer/src/sl_sleeptimer_hal_burtc.o" "./simplicity_sdk_2025.6.2/platform/service/sleeptimer/src/sl_sleeptimer_hal_sysrtc.o" "./simplicity_sdk_2025.6.2/platform/service/sleeptimer/src/sl_sleeptimer_hal_timer.o" "./simplicity_sdk_2025.6.2/platform/service/token_manager/legacy/src/sl_token_def.o" "./simplicity_sdk_2025.6.2/platform/service/token_manager/legacy/src/sl_token_manager.o" "./simplicity_sdk_2025.6.2/platform/service/token_manager/legacy/src/sl_token_manufacturing.o" "./simplicity_sdk_2025.6.2/platform/service/token_manager/legacy/src/sl_token_manufacturing_generic.o" "./simplicity_sdk_2025.6.2/platform/service/udelay/src/sl_udelay.o" "./simplicity_sdk_2025.6.2/platform/service/udelay/src/sl_udelay_armv6m_gcc.o" "./simplicity_sdk_2025.6.2/protocol/flex/app-framework-common/app_framework_common.o" "./simplicity_sdk_2025.6.2/protocol/flex/app-framework-common/app_framework_common_cb.o" "./simplicity_sdk_2025.6.2/protocol/flex/app-framework-common/app_framework_sleep.o" "./simplicity_sdk_2025.6.2/protocol/flex/app-framework-common/app_framework_stack_cb.o" "./simplicity_sdk_2025.6.2/protocol/flex/poll/poll.o" "./simplicity_sdk_2025.6.2/protocol/flex/stack/config/ember-configuration.o" "./simplicity_sdk_2025.6.2/protocol/flex/stack/config/stack-callback-stubs.o" "./simplicity_sdk_2025.6.2/protocol/flex/stack/config/stack-stubs.o" "./simplicity_sdk_2025.6.2/protocol/flex/stack/core/sl-connect-rail-assert.o" "./simplicity_sdk_2025.6.2/protocol/flex/stack/core/sl-connect-watchdog.o" "./simplicity_sdk_2025.6.2/protocol/flex/stack/core/sli-connect-api.o" "./simplicity_sdk_2025.6.2/protocol/flex/stack/core/sli-connect-token.o" "./simplicity_sdk_2025.6.2/protocol/flex/stack/framework/sl-connect-info.o" "./simplicity_sdk_2025.6.2/protocol/flex/stack/framework/sl-connect-power-manager.o" "./simplicity_sdk_2025.6.2/protocol/flex/stack/framework/sli-connect-random.o" "./simplicity_sdk_2025.6.2/util/silicon_labs/silabs_core/buffer_manager/buffer-management.o" "./simplicity_sdk_2025.6.2/util/silicon_labs/silabs_core/buffer_manager/buffer-queue.o" "./simplicity_sdk_2025.6.2/util/third_party/mbedtls/library/aes.o" "./simplicity_sdk_2025.6.2/util/third_party/mbedtls/library/block_cipher.o" "./simplicity_sdk_2025.6.2/util/third_party/mbedtls/library/ccm.o" "./simplicity_sdk_2025.6.2/util/third_party/mbedtls/library/cipher.o" "./simplicity_sdk_2025.6.2/util/third_party/mbedtls/library/cipher_wrap.o" "./simplicity_sdk_2025.6.2/util/third_party/mbedtls/library/constant_time.o" "./simplicity_sdk_2025.6.2/util/third_party/mbedtls/library/platform.o" "./simplicity_sdk_2025.6.2/util/third_party/mbedtls/library/platform_util.o" "./simplicity_sdk_2025.6.2/util/third_party/mbedtls/library/psa_crypto.o" "./simplicity_sdk_2025.6.2/util/third_party/mbedtls/library/psa_crypto_aead.o" "./simplicity_sdk_2025.6.2/util/third_party/mbedtls/library/psa_crypto_cipher.o" "./simplicity_sdk_2025.6.2/util/third_party/mbedtls/library/psa_crypto_client.o" "./simplicity_sdk_2025.6.2/util/third_party/mbedtls/library/psa_crypto_driver_wrappers_no_static.o" "./simplicity_sdk_2025.6.2/util/third_party/mbedtls/library/psa_crypto_ecp.o" "./simplicity_sdk_2025.6.2/util/third_party/mbedtls/library/psa_crypto_ffdh.o" "./simplicity_sdk_2025.6.2/util/third_party/mbedtls/library/psa_crypto_hash.o" "./simplicity_sdk_2025.6.2/util/third_party/mbedtls/library/psa_crypto_mac.o" "./simplicity_sdk_2025.6.2/util/third_party/mbedtls/library/psa_crypto_pake.o" "./simplicity_sdk_2025.6.2/util/third_party/mbedtls/library/psa_crypto_rsa.o" "./simplicity_sdk_2025.6.2/util/third_party/mbedtls/library/psa_crypto_se.o" "./simplicity_sdk_2025.6.2/util/third_party/mbedtls/library/psa_crypto_slot_management.o" "./simplicity_sdk_2025.6.2/util/third_party/mbedtls/library/psa_crypto_storage.o" "./simplicity_sdk_2025.6.2/util/third_party/mbedtls/library/psa_util.o" "./simplicity_sdk_2025.6.2/util/third_party/mbedtls/library/threading.o" "./simplicity_sdk_2025.6.2/util/third_party/printf/printf.o" "./simplicity_sdk_2025.6.2/util/third_party/printf/src/iostream_printf.o" "C:/Users/joao.victor/SimplicityStudio/SDKs/simplicity_sdk//protocol/flex/libs/libconnect-frequency-hopping-library-efr32xg2x-gcc.a" "C:/Users/joao.victor/SimplicityStudio/SDKs/simplicity_sdk//protocol/flex/libs/libconnect-packet-queue-library-efr32xg2x-gcc.a" "C:/Users/joao.victor/SimplicityStudio/SDKs/simplicity_sdk//protocol/flex/libs/libconnect-parent-support-library-efr32xg2x-gcc.a" "C:/Users/joao.victor/SimplicityStudio/SDKs/simplicity_sdk//protocol/flex/libs/libconnect-psa-security-library-efr32xg2x-gcc.a" "C:/Users/joao.victor/SimplicityStudio/SDKs/simplicity_sdk//protocol/flex/libs/libconnect-stack-common-library-efr32xg2x-gcc.a" "C:/Users/joao.victor/SimplicityStudio/SDKs/simplicity_sdk//protocol/flex/libs/libconnect-stack-counters-library-efr32xg2x-gcc.a" "C:/Users/joao.victor/SimplicityStudio/SDKs/simplicity_sdk//platform/radio/rail_lib/autogen/librail_release/librail_config_fgm230sa27hgn_gcc.a" "C:/Users/joao.victor/SimplicityStudio/SDKs/simplicity_sdk//platform/radio/rail_lib/autogen/librail_release/librail_module_efr32xg23_gcc_release.a" -lgcc -lc -lm -lnosys -Wl,--end-group -Wl,--start-group -lgcc -lc -lnosys -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

	@echo 'Building out file: IVP_LR_Connect.out'
	arm-none-eabi-objcopy "IVP_LR_Connect.axf" "IVP_LR_Connect.out"
	@echo ' '

	@echo 'Building hex file: IVP_LR_Connect.hex'
	arm-none-eabi-objcopy -O ihex "IVP_LR_Connect.axf" "IVP_LR_Connect.hex"
	@echo ' '

	@echo 'Building bin file: IVP_LR_Connect.bin'
	arm-none-eabi-objcopy -O binary "IVP_LR_Connect.axf" "IVP_LR_Connect.bin"
	@echo ' '

	@echo 'Building s37 file: IVP_LR_Connect.s37'
	arm-none-eabi-objcopy -O srec "IVP_LR_Connect.axf" "IVP_LR_Connect.s37"
	@echo ' '

	@echo 'Running size tool'
	arm-none-eabi-size "IVP_LR_Connect.axf" -A
	@echo ' '

# Other Targets
clean:
	-@$(foreach FILE, $(EXECUTABLES), $(shell $(RM) $(FILE)) )
	-@$(foreach FILE, $(OBJS), $(shell $(RM) $(FILE)) )
	-@$(foreach FILE, $(C_DEPS), $(shell $(RM) $(FILE)) )
	-$(RM) IVP_LR_Connect.axf
	-@echo ' '

.PHONY: all clean dependents main-build

-include ../makefile.targets
