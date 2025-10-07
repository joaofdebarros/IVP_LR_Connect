/*
 * hADC.h
 *
 *  Created on: 19 de nov. de 2024
 *      Author: diego.marinho
 */

#ifndef HDRIVER_HADC_H_
#define HDRIVER_HADC_H_


#include "em_iadc.h"
#include "em_cmu.h"
#include "em_chip.h"

#define VREF_MV          1200   // Tensão de referência em mV
#define IADC_RESOLUTION  4096   // Resolução do IADC (12 bits = 2^12)
#define VDD_DIV_FACTOR   4      // Fator de divisão aplicado a Vdd

#define CLK_SRC_ADC_FREQ          1000000 // CLK_SRC_ADC
#define CLK_ADC_FREQ              1000000 // CLK_ADC

#define IADC_INPUT_0_PORT_PIN     iadcPosInputPortAPin5;

// Set IADC timer cycles
#define TIMER_CYCLES              50000  // 50000 => 100   samples/second
                                         // 5000  => 1000  samples/second
                                         // 1000  => 5000  samples/second
                                         // 500   => 10000 samples/second
                                         // 200   => 25000 samples/second

/**
 * Inicializa o IADC para medir AVDD/4.
 */
void iadcInit(void);


#endif /* HDRIVER_HADC_H_ */
