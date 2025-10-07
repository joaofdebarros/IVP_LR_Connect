/*
 * packet.c
 *
 *  Created on: 9 de ago de 2024
 *      Author: diego.marinho
 */

#include "packet.h"


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

packet_error_e packet_data_demount(uint8_t *inData, uint8_t inLen, packet_void_t *packet){
  uint8_t i;
  packet->cmd = inData[0];
  for(i = 0; i < inLen; i++){
      packet->data[i] = inData[i+1];
  }

  return PACKET_OK;
}






