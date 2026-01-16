/*
 * packetRadio.c
 *
 *  Created on: 15 de set. de 2025
 *      Author: diego.marinho
 */


#include "packetRadio.h"


/*
 * Globals
 */




/*
 * Macros
 */


/*
 * Privates
 */






/*
 * Publics
 */

bool packet_data_demount_radio(uint8_t *inData, uint8_t inLen, packet_voidRadio_t *packet){
  uint8_t i;
  packet->cmd = inData[0];
  for(i = 0; i < inLen; i++){
      packet->data[i] = inData[i+1];
  }

  return true;
}
