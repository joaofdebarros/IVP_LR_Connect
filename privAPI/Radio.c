/*
 * Radio.c
 *
 *  Created on: 13 de ago. de 2024
 *      Author: diego.marinho
 */

#include "Radio.h"

extern EmberMessageOptions tx_options;

void SL_WEAK privcallback_Radio_Receive(uint8_t *data,uint8_t length);



status_radio_t radioMessageSend(uint8_t destination, uint8_t messageLength, uint8_t *data){
  EmberStatus status;
  status = emberMessageSend(destination,1,0,messageLength,data,tx_options);
  return status;
}

///**************************************************************************//**
// * This function is called when a message is received.
// *****************************************************************************/
//void emberAfIncomingMessageCallback(EmberIncomingMessage *message)
//{
//  privcallback_Radio_Receive(message->payload,message->length);
//}
