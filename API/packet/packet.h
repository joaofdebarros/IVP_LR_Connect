/*
 * packet.h
 *
 *  Created on: 9 de ago de 2024
 *      Author: diego.marinho
 */

#ifndef API_ET001_PACKET_H_
#define API_ET001_PACKET_H_


#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include "API/packet/pckDataStructure.h"




/*
 * Macros
 */

/*
 * Enumerates
 */

typedef enum{
  PACKET_OK,
  PACKET_FAIL
}packet_error_e;

/*
 * Structs and Unions
 */



typedef struct{
    uint16_t header;
    uint8_t version;
    uint8_t encrypted;
    uint16_t id_user;
    uint8_t len;
    uint8_t IV[16];
    uint8_t data[256];
    uint16_t tail;
}packet_t;



/*
 * Externs
 */


/*
 * Function prototypes
 */

void packet_init(uint16_t header, uint16_t tail, uint8_t *key);

void packet_init_default();



packet_error_e packet_data_demount(uint8_t *inData, uint8_t inLen, packet_void_t *packet);

packet_error_e packet_data_mountserial(volatile uint8_t *inData, uint16_t inLen, volatile uint8_t *outPacket, uint8_t *outLen,  uint8_t command, uint8_t *DataAux, uint8_t lenghtaux);


#endif /* API_ET001_PACKET_H_ */
