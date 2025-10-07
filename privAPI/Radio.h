/*
 * Radio.h
 *
 *  Created on: 13 de ago. de 2024
 *      Author: diego.marinho
 */

#ifndef PRIVAPI_RADIO_H_
#define PRIVAPI_RADIO_H_

#include <stdint.h>
#include "stack/include/ember.h"

typedef enum{
  RADIO_OK = 0,
  RADIO_ERROR
}status_radio_t;

status_radio_t radioMessageSend(uint8_t destination, uint8_t messageLength, uint8_t *data);
void privcallback_Radio_Receive(uint8_t *data,uint8_t length);


#endif /* PRIVAPI_RADIO_H_ */
