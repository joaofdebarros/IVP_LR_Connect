/*
 * privCallback.c
 *
 *  Created on: 14 de ago. de 2024
 *      Author: diego.marinho
 */

#include "privCallback.h"

void SL_WEAK callback_Radio_Receive(uint8_t *data, uint8_t len);

void privcallback_Radio_Receive(uint8_t *data,uint8_t length){
  callback_Radio_Receive(data,length);
}
