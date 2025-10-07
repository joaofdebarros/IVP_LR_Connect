/*
 * efr32.h
 *
 *  Created on: July 17, 2024
 *      Author: diego.marinho
 */

#ifndef CHIPSET_EFR32_H_
#define CHIPSET_EFR32_H_

/**************************************************************************
 * Includes
 **************************************************************************/
#include "hplatform/hDriver/hDriver.h"

/**************************************************************************
 * Gpio / Pins
 **************************************************************************/
/*
 * This defines are needed to keep compatibility with anothers chipsets
 */
//#define AT25_CS_GPIO_Port           0
//#define AUDIOSD_GPIO_Port           0
//#define FINGER_TS_GPIO_Port         0
//#define FINGER_ENABLE_GPIO_Port     0
//#define FINGER_VCC_GPIO_Port        0
//#define CR95_CTRL_GPIO_Port         0
//#define CR95_SS_GPIO_Port           0
//#define CR95_IRQOUT_GPIO_Port       0
//#define CR95_IRQIN_GPIO_Port        0
//#define PATI_WKUP_GPIO_Port         0
//#define KEYPAD_IRQ_GPIO_Port        0
//#define ACEL_INT1_GPIO_Port         0
//#define ACEL_INT2_GPIO_Port         0
#define LED_VERDE_PORT                  gpioPortA
#define LED_VERDE_PIN                   8
#define LED_AZUL_PORT                  gpioPortC
#define LED_AZUL_PIN                   1
#define LED_VERMELHO_PORT                  gpioPortA
#define LED_VERMELHO_PIN                   7

#define BUTTON0_PORT                  gpioPortA
#define BUTTON0_PIN                   10
#define BUTTON1_PORT                  gpioPortC
#define BUTTON1_PIN                   2

#define SER_IN_PORT                  gpioPortB
#define SER_IN_PIN                   1

#define DIRECT_LINK_PORT                  gpioPortB
#define DIRECT_LINK_PIN                   0

#define SENSE_LOW_PORT                  gpioPortA
#define SENSE_LOW_PIN                   6
#define SENSE_HIGH_PORT                  gpioPortA
#define SENSE_HIGH_PIN                   6
#define AF_PORT                  gpioPortC
#define AF_PIN                   5
#define RL_PORT                  gpioPortD
#define RL_PIN                   2

// Pins ins't necessary


/**************************************************************************
 * Max Peripherals
 **************************************************************************/
// efr32 has 2 uarts peripherals
#define HUSART_HARDWARE_PERIPHERALS     3
// efr32 has 4 timer peripherals to use in PWM
#define HPWM_HARDWARE_PERIPHERALS       3
// efr32 has 2 spi peripherals
#define HSPI_HARDWARE_PERIPHERALS       2
// efr32 has only one i2c
#define HI2C_HARDWARE_PERIPHERALS       1
// efr32 has onyl one i2s
#define HI2S_HARDWARE_PERIPHERALS       1
//efr32 has four timers in 16bits mode
#define HTIMER_HARDWARE_PERIPHERALS     4

/**************************************************************************
 * NVS Address Regions
 **************************************************************************/
#define NVS_FOTA_INFO           0x00
#define NVS_BLEKEY_DATA         0x01
#define NVS_CFG_DATA            0x03
#define NVS_ALARM_STATE         0x04
#define NVS_MAC_DATA            0x10

#define NVS_EB_MESSAGE          0x12

#define NVS_STATISTICS          0x20
#define NVS_STATISTICS_BCK      0x21

#define NVS_COMMAND_KEY         0x50

/**************************************************************************
 * Extern Peripheral Handlers
 **************************************************************************/
//extern hSpi_t hSPI[HSPI_HARDWARE_PERIPHERALS];
//extern hI2Cm_t hI2C[HI2C_HARDWARE_PERIPHERALS];
//extern hI2S_t hI2S[HI2S_HARDWARE_PERIPHERALS];
//extern hUsart_t hUSART[HUSART_HARDWARE_PERIPHERALS];
extern hTimer_t hTIMER[HTIMER_HARDWARE_PERIPHERALS];



#endif /* CHIPSET_EFR32_H_ */
