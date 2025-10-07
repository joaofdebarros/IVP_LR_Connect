/*
 * pckDataStructure.h
 *
 *  Created on: 9 de ago de 2024
 *      Author: diego.marinho
 */

#ifndef ET001_PCKDATASTRUCTURE_H_
#define ET001_PCKDATASTRUCTURE_H_

#include <stdint.h>
#include <stdbool.h>

/*
 * defines
 */

#define PROP_ASYNC				(1 << 0)
#define PROP_DISCONNECT 		(1 << 1)

/*
 * Enumerates
 */
typedef enum SensorCmd_e{
  REGISTRATION = 21,
  MOTION_DETECTED = 22,
  SETUP_IVP,
	KEEP_ALIVE,
	STATUS_CENTRAL,
	TAMPER,


	CMD_UNKNOWN = 0xFF
}SensorCmd_e;


typedef struct{
		SensorCmd_e cmd;
		uint8_t data[8];
		uint8_t len;
}packet_void_t;

#endif /* ET001_PCKDATASTRUCTURE_H_ */
