/***************************************************************************//**
 * @file
 * @brief app_init.c
 *******************************************************************************
 * # License
 * <b>Copyright 2018 Silicon Laboratories Inc. www.silabs.com</b>
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

// -----------------------------------------------------------------------------
//                                   Includes
// -----------------------------------------------------------------------------
#include "sl_component_catalog.h"
#include "app_log.h"
#include "sl_app_common.h"
#include "sl_sleeptimer.h"
#include "app_process.h"
#include "app_init.h"
#include "app_framework_common.h"
// Ensure that psa is initialized correctly
#include "psa/crypto.h"
#include "mbedtls/build_info.h"
#include "Application/application.h"
#include "sl_power_manager.h"
#include "API/memory/memory.h"
#include "poll.h"

// -----------------------------------------------------------------------------
//                              Macros and Typedefs
// -----------------------------------------------------------------------------
#define PSA_AES_KEY_ID 1

// -----------------------------------------------------------------------------
//                          Static Function Declarations
// -----------------------------------------------------------------------------
static void app_pm_callback(sl_power_manager_em_t from, sl_power_manager_em_t to);
static sl_power_manager_em_transition_event_handle_t pm_handle;
static sl_power_manager_em_transition_event_info_t pm_event_info =
{ SL_POWER_MANAGER_EVENT_TRANSITION_ENTERING_EM2, app_pm_callback };


// -----------------------------------------------------------------------------
//                                Global Variables
// -----------------------------------------------------------------------------
extern EmberKeyData security_key;
/// Connect security key id
extern psa_key_id_t security_key_id;
extern EmberEventControl *radio_control;
extern EmberEventControl *motionDetected_control;
extern EmberEventControl *timeout_control;
extern EmberEventControl *PeriodInstalation_control;
extern EmberEventControl *TimeoutAck_control;

extern uint8_t tx_power;
// -----------------------------------------------------------------------------
//                                Static Variables
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
//                          Public Function Definitions
// -----------------------------------------------------------------------------
/******************************************************************************
* Application framework init callback
******************************************************************************/
void emberAfInitCallback(void)
{
  uint8_t device_id = 0;
  EmberStatus em_status = EMBER_ERR_FATAL;

  emberAfPluginPollEnableShortPolling(true);

  application.IVP.pydConf.sPYDType.thresholdVal = 120;
  application.IVP.SensorStatus.Status.led_enabled = 1;
  application.IVP.SensorStatus.Status.energy_mode = ECONOMIC;
  tx_power = 150;
  application.Status_Operation = WAIT_REGISTRATION;
  application.Status_Central = DISARMED;

  memory_read(STATUSBYTE_MEMORY_KEY, &application.IVP.SensorStatus.Statusbyte);
  memory_read(SENSIBILITY_MEMORY_KEY, &application.IVP.pydConf.sPYDType.thresholdVal);
  memory_read(TXPOWER_MEMORY_KEY, &tx_power);
  memory_read(STATUSOP_MEMORY_KEY, &application.Status_Operation);
  memory_read(STATUSCENTRAL_MEMORY_KEY, &application.Status_Central);
  memory_read(ID_PARTITION_MEMORY_KEY, &application.IVP.ID_partition);

  set_tx(tx_power);

  // FORCANDO ARMADO E CONTINUO SEMPRE PARA TESTE
//  application.IVP.SensorStatus.Status.energy_mode = CONTINUOUS;
//  application.Status_Operation = WAIT_REGISTRATION;
//  application.Status_Central = ARMED;

  // Ensure that psa is initialized correctly
  psa_crypto_init();

  emberAfAllocateEvent(&report_control, &report_handler);
  emberAfAllocateEvent(&radio_control, &radio_handler);
  emberAfAllocateEvent(&motionDetected_control, &motionDetected_handler);
  emberAfAllocateEvent(&timeout_control, &timeout_handler);
  emberAfAllocateEvent(&TimeoutAck_control, &TimeoutAck_handler);

  // CLI info message
//  app_log_info("\nSensor\n");

  security_key_id = PSA_AES_KEY_ID;
  psa_key_attributes_t key_attr = psa_key_attributes_init();
  psa_status_t psa_status = psa_get_key_attributes(security_key_id, &key_attr);
  if (psa_status == PSA_ERROR_INVALID_HANDLE) {
//    app_log_info("No PSA AES key found, creating one.\n");
    psa_set_key_id(&key_attr, security_key_id);
    psa_set_key_algorithm(&key_attr, PSA_ALG_AEAD_WITH_SHORTENED_TAG(PSA_ALG_CCM, 4));
    psa_set_key_usage_flags(&key_attr, PSA_KEY_USAGE_ENCRYPT | PSA_KEY_USAGE_DECRYPT);
    psa_set_key_type(&key_attr, PSA_KEY_TYPE_AES);
    psa_set_key_bits(&key_attr, 128);

#ifdef PSA_KEY_LOCATION_SLI_SE_OPAQUE
    psa_set_key_lifetime(&key_attr,
                         PSA_KEY_LIFETIME_FROM_PERSISTENCE_AND_LOCATION(
                           PSA_KEY_LIFETIME_PERSISTENT,
                           PSA_KEY_LOCATION_SLI_SE_OPAQUE));
#else
#ifdef MBEDTLS_PSA_CRYPTO_STORAGE_C
    psa_set_key_lifetime(&key_attr,
                         PSA_KEY_LIFETIME_FROM_PERSISTENCE_AND_LOCATION(
                           PSA_KEY_LIFETIME_PERSISTENT,
                           PSA_KEY_LOCATION_LOCAL_STORAGE));
#else
    psa_set_key_lifetime(&key_attr,
                         PSA_KEY_LIFETIME_FROM_PERSISTENCE_AND_LOCATION(
                           PSA_KEY_LIFETIME_VOLATILE,
                           PSA_KEY_LOCATION_LOCAL_STORAGE));
#endif
#endif

    psa_status = psa_import_key(&key_attr,
                                security_key.contents,
                                (size_t)EMBER_ENCRYPTION_KEY_SIZE,
                                &security_key_id);

    if (psa_status == PSA_SUCCESS) {
//      app_log_info("Security key import successful, key id: %lu\n", security_key_id);
    } else {
//      app_log_info("Security Key import failed: %ld\n", psa_status);
    }
  } else {
//    app_log_info("PSA AES key found, using the existing one.\n");
  }

  em_status = emberSetPsaSecurityKey(security_key_id);

  em_status = emberNetworkInit();
//  app_log_info("Network status 0x%02X\n", em_status);

  sl_power_manager_subscribe_em_transition_event(&pm_handle, &pm_event_info);

//  if (em_status == EMBER_SUCCESS) {
    emberEventControlSetActive(*report_control);
//  }

#if defined(EMBER_AF_PLUGIN_BLE)
  bleConnectionInfoTableInit();
#endif
}
// -----------------------------------------------------------------------------
//                          Static Function Definitions
// -----------------------------------------------------------------------------
static void app_pm_callback(sl_power_manager_em_t from, sl_power_manager_em_t to){
  (void)from;
  if ( to == SL_POWER_MANAGER_EM2 ){
    extern uint8_t * emPendingOutgoingPacket;
    if (emPendingOutgoingPacket) {
      free(emPendingOutgoingPacket);
    }
  }
}


