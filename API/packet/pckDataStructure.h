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
  IVP_REGISTRATION = 21,
  MOTION_DETECTED = 22,
  SENSOR_PARTITION = 40,
  SETUP_IVP,
	KEEP_ALIVE,
	STATUS_CENTRAL,
	TAMPER,
	LEAVE_NETWORK,

	CMD_UNKNOWN = 0xFF
}SensorCmd_e;

typedef union
{
    uint8_t Registerbyte;

    struct
    {
        uint8_t Type                  :5;
        uint8_t range                 :2;
        uint8_t reserved              :1;
    } Status;

}

Register_Sensor_t;

typedef struct{
		SensorCmd_e cmd;
		uint8_t data[8];
		uint8_t len;
}packet_void_t;

typedef struct{
    bool slot_used;
    uint8_t attempts;
    packet_void_t packet;
}send_queue_t;

#endif /* ET001_PCKDATASTRUCTURE_H_ */
