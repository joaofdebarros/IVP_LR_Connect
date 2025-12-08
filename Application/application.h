/*
 * application.h
 *
 *  Created on: 12 de ago. de 2024
 *      Author: diego.marinho
 */

#ifndef APPLICATION_APPLICATION_H_
#define APPLICATION_APPLICATION_H_

#include "API/packet/packet.h"
#include "API/packet/pckDataStructure.h"
#include "API/pyd/pyd.h"
#include "app_log.h"
#include "privAPI/Radio.h"
#include "API/battery/battery.h"
#include "sl_simple_led_instances.h"
#include "API/memory/memory.h"
#include "API/hNetwork.h"

#define SLOW_SPEED_BLINK  1000
#define MED_SPEED_BLINK   200
#define FAST_SPEED_BLINK  100
#define MAX_QUEUE_PACKETS 3
#define MAX_QUEUE_PACKET_ATTEMPTS 10

typedef enum{
  SENSOR_IDLE = 0,
  SENSOR_CONFIGURANDO,
  SENSOR_CONFIGURADO
}Status_Sensor_t;

typedef enum{
  WAIT_REGISTRATION = 0,
  PERIOD_INSTALATION,
  OPERATION_MODE,
  BOOT,
  RESETTING
}Status_Operation_t;

typedef enum{
  CONTINUOUS = 0,
  ECONOMIC,
  UECONOMIC
}Energy_Mode_t;

typedef enum{
  CONTROL = 0,
  MOTION_DETECT,
  OPEN_CLOSE_DETECT,
  GATE
}Type;

typedef enum{
  DISARMED = 0,
  ARMED
}Status_Central_t;

typedef enum{
  LONG_RANGE = 0,
  MID_RANGE
}Range_t;

typedef enum{
  VERMELHO = 0,
  VERDE,
  AZUL
}LED_t;

typedef enum{
  SUCCESS,
  FAIL
}IVP_config_error_e;

typedef enum{
  HARDWARE_FULL_RESET,
  LR_FULL_RESET,
  LR_DISCONNECT
}leaving_method_t;

typedef union
{
    uint8_t Statusbyte;

    struct
    {
        Status_Operation_t operation             :2;
        Status_Central_t statusCentral         :1;
        Energy_Mode_t energy_mode           :2;
        uint8_t led_enabled           :1;
        uint8_t reserved              :2;
    } Status;

}
SensorStatus_t;

typedef struct{
  packet_void_t Packet;
  SensorCmd_e LastCMD;
  IVP_config_error_e error;
}application_radio_t;

typedef struct{
  uPYDType pydConf;
  SensorStatus_t SensorStatus;
  uint32_t ID_partition;
  leaving_method_t leaving_method;
}application_IVP_t;

typedef struct{
  application_radio_t radio;
  application_IVP_t IVP;
  Status_Operation_t Status_Operation;
  Status_Central_t Status_Central;
}application_t;

extern application_t application;

/*
 * Prototypes
 */
EmberStatus radio_send_packet(packet_void_t *pck, bool retrying);
void radio_handler(void);
void timeout_handler(void);
void motionDetected_handler(void);
void PeriodInstalation_handler(void);
void TimeoutAck_handler(void);
void TurnPIROff(Energy_Mode_t energy_mode);
void led_blink(uint8_t led, uint8_t blinks, uint16_t speed);
void led_handler(sl_sleeptimer_timer_handle_t *handle, void *data);
void Queue_manager(packet_void_t *pck);
#endif /* APPLICATION_APPLICATION_H_ */
