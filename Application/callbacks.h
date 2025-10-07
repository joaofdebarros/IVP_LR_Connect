/*
 * callbacks.h
 *
 *  Created on: 18 de july de 2024
 *      Author: diego.marinho
 */

#ifndef APPLICATION_CALLBACKS_H_
#define APPLICATION_CALLBACKS_H_


#include <stdint.h>
#include <string.h>

//#include "hDriver.h"
#include "API/pyd/motion.h"
#include "API/packet/packet.h"

#include "application.h"

void callback_Direct_Link();
void callback_Timeout();

//void callback_Radio_Receive(uint8_t *data, uint8_t len);



#endif /* APPLICATION_CALLBACKS_H_ */
