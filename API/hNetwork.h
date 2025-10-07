/*
 * hNetwork.h
 *
 *  Created on: 11 de out. de 2024
 *      Author: diego.marinho
 */

#ifndef API_HNETWORK_H_
#define API_HNETWORK_H_

// -----------------------------------------------------------------------------
//                                   Includes
// -----------------------------------------------------------------------------
#include "stdbool.h"
#include "sl_sensor_sink_config.h"
#include <string.h>
#include "em_chip.h"
#include "stack/include/ember.h"

// -----------------------------------------------------------------------------
//                          Static Function Declarations
// -----------------------------------------------------------------------------
bool check_channel(uint16_t channel);

void join_sleepy(uint16_t channel);
void leave(void);
void set_tx(uint16_t channel);

#endif /* API_HNETWORK_H_ */
