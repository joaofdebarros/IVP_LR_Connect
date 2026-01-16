/*
 * packetRadio.h
 *
 *  Created on: 15 de set. de 2025
 *      Author: diego.marinho
 */

#ifndef PACKETRADIO_PACKETRADIO_H_
#define PACKETRADIO_PACKETRADIO_H_

#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include "stdbool.h"
#include "API/PacketRadio/pckDataStructure.h"




/*
 * Macros
 */

/*
 * Enumerates
 */



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
}packetRadio_t;



/*
 * Externs
 */


/*
 * Function prototypes
 */

void packet_init(uint16_t header, uint16_t tail, uint8_t *key);

void packet_init_default();



bool packet_data_demount_radio(uint8_t *inData, uint8_t inLen, packet_voidRadio_t *packet);

bool packet_data_mountserial(volatile uint8_t *inData, uint16_t inLen, volatile uint8_t *outPacket, uint8_t *outLen,  uint8_t command, uint8_t *DataAux, uint8_t lenghtaux);

#endif /* PACKETRADIO_PACKETRADIO_H_ */
