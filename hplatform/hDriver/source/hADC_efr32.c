/*
 * hADC_efr32.c
 *
 *  Created on: 19 de nov. de 2024
 *      Author: diego.marinho
 */


#include "hplatform/hDriver/hADC.h"


/**
 * Inicializa o IADC para medir AVDD/4.
 */
void iadcInit(void) {
  CMU_ClockEnable(cmuClock_IADC0, true);

  // Configuração do clock do IADC
  IADC_Init_t iadcInit = IADC_INIT_DEFAULT;
  iadcInit.warmup = iadcWarmupNormal;  // TESTE MUDANDO O MODO DE WARMUP
  iadcInit.srcClkPrescale = IADC_calcSrcClkPrescale(IADC0, CLK_SRC_ADC_FREQ, 0);  // Clock de 1 MHz

  // Configuração geral do IADC
  IADC_AllConfigs_t iadcAllConfigs = IADC_ALLCONFIGS_DEFAULT;
  iadcAllConfigs.configs[0].reference = iadcCfgReferenceInt1V2;  // Referência interna de 1,2 V
  iadcAllConfigs.configs[0].vRef = VREF_MV;                      // Valor de referência para escalonamento

  // Configuração para conversões únicas
  IADC_InitSingle_t iadcSingleInit = IADC_INITSINGLE_DEFAULT;
  iadcSingleInit.dataValidLevel = _IADC_SINGLEFIFOCFG_DVL_VALID1;
  iadcSingleInit.triggerAction = iadcTriggerActionOnce;           // Uma conversão por vez
  iadcSingleInit.alignment = iadcAlignRight12;                    // Alinhamento à direita (12 bits)
  //iadcSingleInit.posInput = iadcPosInputAvddDiv4;                 // Canal interno AVDD/4
  //iadcSingleInit.negInput = iadcNegInputGnd;                      // Referência no GND

  IADC_SingleInput_t initSingleInput = IADC_SINGLEINPUT_DEFAULT;
  // Configure Input sources for single ended conversion
  initSingleInput.posInput = iadcPosInputAvdd;
  initSingleInput.negInput = iadcNegInputGnd;

  // Inicializa o IADC
  IADC_init(IADC0, &iadcInit, &iadcAllConfigs);

  // Initialize Single
  IADC_initSingle(IADC0, &iadcSingleInit, &initSingleInput);
}


