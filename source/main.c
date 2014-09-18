#include "stm32f0xx_conf.h"
#include "stm32f072b_discovery.h"

#define ADC_R_Y  (uint8_t)(0) //PA0
#define ADC_R_X  (uint8_t)(1) //PA1
#define ADC_L_Y  (uint8_t)(2) //PA4
#define ADC_L_X  (uint8_t)(3) //PA5
ADC_InitTypeDef ADC_InitStructure;
GPIO_InitTypeDef GPIO_InitStructure;
DMA_InitTypeDef DMA_InitStructure;
TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
TIM_OCInitTypeDef TIM_OCInitStructure;

volatile uint16_t sample_value[4] = {0};

void init_ADC(void);

int main(int argc, char const* argv[])
{
  STM_EVAL_LEDInit(LED3); 
  STM_EVAL_LEDInit(LED4); 
  STM_EVAL_LEDInit(LED5); 
  STM_EVAL_LEDInit(LED6); 

  init_ADC();
 
  while(1) {
    if (sample_value[ADC_R_Y] > 0x0900){
      STM_EVAL_LEDOn(LED3);
    } else {
      STM_EVAL_LEDOff(LED3);
    }
    if (sample_value[ADC_R_X] > 0x0900){
      STM_EVAL_LEDOn(LED5);
    }else {
      STM_EVAL_LEDOff(LED5);
    }
    if (sample_value[ADC_L_Y] > 0x0900) {
      STM_EVAL_LEDOn(LED6);
    }else{
      STM_EVAL_LEDOff(LED6);
    }
    if (sample_value[ADC_L_X] > 0x0900) {
      STM_EVAL_LEDOn(LED4);
    }else{
      STM_EVAL_LEDOff(LED4);
    }
  }

  return 0;
}

void init_ADC() {
  ADC_DeInit(ADC1);

  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_4 | GPIO_Pin_5;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

  TIM_DeInit(TIM1);

  /* Time base configuration */
  TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
  TIM_TimeBaseStructure.TIM_Prescaler = (SystemCoreClock / 1000000) - 1; // 1 MHz, from 48 MHz
  TIM_TimeBaseStructure.TIM_Period = 1000 - 1; // 1 KHz
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
  TIM_TimeBaseStructure.TIM_ClockDivision = 0;
  TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
  TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);
 
  /* Output Compare PWM Mode configuration */
  TIM_OCStructInit(&TIM_OCInitStructure);
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; /* low edge by default */
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = 1;
  TIM_OC4Init(TIM1, &TIM_OCInitStructure);
 
  /* TIM1 enable counter */
  TIM_Cmd(TIM1, ENABLE);
 
  /* Main Output Enable */
  TIM_CtrlPWMOutputs(TIM1, ENABLE);

  DMA_DeInit(DMA1_Channel1);
  DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&ADC1->DR;
  DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)&sample_value[0];
  DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
  DMA_InitStructure.DMA_BufferSize = 4;
  DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
  DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
  DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
  DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
  DMA_InitStructure.DMA_Priority = DMA_Priority_High;
  DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;

  DMA_Init(DMA1_Channel1, &DMA_InitStructure);
  DMA_Cmd(DMA1_Channel1, ENABLE);

  ADC_StructInit(&ADC_InitStructure);

  ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;
  ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;
  ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_Rising;
  ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_T1_CC4;
  ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
  ADC_InitStructure.ADC_ScanDirection = ADC_ScanDirection_Upward;
  ADC_Init(ADC1, &ADC_InitStructure);

  ADC_ChannelConfig(ADC1, ADC_Channel_0, ADC_SampleTime_7_5Cycles);
  ADC_ChannelConfig(ADC1, ADC_Channel_1, ADC_SampleTime_7_5Cycles);
  ADC_ChannelConfig(ADC1, ADC_Channel_4, ADC_SampleTime_7_5Cycles);
  ADC_ChannelConfig(ADC1, ADC_Channel_5, ADC_SampleTime_7_5Cycles);

  ADC_GetCalibrationFactor(ADC1);

  ADC_DMARequestModeConfig(ADC1, ADC_DMAMode_Circular);
  ADC_DMACmd(ADC1, ENABLE);
  ADC_Cmd(ADC1, ENABLE);
  while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_ADEN));
  ADC_StartOfConversion(ADC1);
}
