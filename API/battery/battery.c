/*
 * battery.c
 *
 *  Created on: 19 de nov. de 2024
 *      Author: diego.marinho
 */
#include "API/battery/battery.h"

battery_t battery;

/**
 * Lê o valor do IADC para AVDD/4.
 *
 * @return Valor convertido pelo IADC.
 */
uint32_t iadcRead(void) {
    IADC_command(IADC0, iadcCmdStartSingle);  // Inicia a conversão única

    // Aguardar a conclusão da conversão
    while ((IADC0->STATUS & _IADC_STATUS_CONVERTING_MASK) != 0);

    // Ler o valor do FIFO de dados
    return IADC_pullSingleFifoResult(IADC0).data;
}

/**
 * Calcula a tensão de Vdd com base no valor lido do IADC.
 *
 * @return Tensão de Vdd em mV.
 */
uint32_t calculateVdd(void) {
    uint32_t iadcValue = iadcRead();  // Lê o valor do IADC
    return (iadcValue * VREF_MV * VDD_DIV_FACTOR) / IADC_RESOLUTION;
}
