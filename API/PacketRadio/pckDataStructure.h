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

#define PROP_ASYNC        (1 << 0)
#define PROP_DISCONNECT     (1 << 1)

/*
 * Enumerates
 */
typedef enum SensorCmd_e{
  CONTROL_MOTOR,
  SENSOR_PARTITION
}SensorCmd_e;


typedef struct{
    SensorCmd_e cmd;
    uint8_t data[8];
    uint8_t len;
}packet_voidRadio_t;

typedef struct{
    bool slot_used;
    uint8_t attempts;
    packet_voidRadio_t packet;
    uint16_t nodeId;
}send_queue_t;

#endif /* ET001_PCKDATASTRUCTURE_H_ */
