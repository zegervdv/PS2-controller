#include "stm32f0xx_conf.h"
#include "stm32f072b_discovery.h"
#include "usbd_hid_core.h"
#include "usbd_usr.h"
#include "usbd_desc.h"
#include "usbd_custom_hid_core.h"
#include <string.h>

#define ADC_R_Y  (0) //PA1
#define ADC_R_X  (1) //PA2
#define ADC_L_Y  (2) //PA4
#define ADC_L_X  (3) //PA5
#define USB_BUFFER (int)(5)

ADC_InitTypeDef ADC_InitStructure;
DMA_InitTypeDef DMA_InitStructure;
TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
TIM_OCInitTypeDef TIM_OCInitStructure;
USART_InitTypeDef USART_InitStructure;

volatile uint8_t sample_value[4] = {0};

uint8_t Send_Buffer[USB_BUFFER];
uint8_t PrevXferDone = 1;
USB_CORE_HANDLE  USB_Device_dev;

void init_ADC(void);
void init_USART(void);
void USART_Write(uint8_t* data, uint8_t size);
void Delay(__IO uint32_t);

int main(int argc, char const* argv[])
{
  // Initialize SysTick
  RCC_ClocksTypeDef RCC_Clocks;
  RCC_GetClocksFreq(&RCC_Clocks);
  SysTick_Config(RCC_Clocks.HCLK_Frequency / 1000);
  STM_EVAL_LEDInit(LED3); 
  STM_EVAL_LEDInit(LED4); 
  STM_EVAL_LEDInit(LED5); 
  STM_EVAL_LEDInit(LED6); 

  init_ADC();
  init_USART();

  USBD_Init(&USB_Device_dev, &USR_desc, &USBD_HID_cb, &USR_cb);
  init_ADC();
  while(1) {
    if (sample_value[ADC_R_Y] > 0x90){
      STM_EVAL_LEDOn(LED3);
    } else {
      STM_EVAL_LEDOff(LED3);
    }
    if (sample_value[ADC_R_X] > 0x90){
      STM_EVAL_LEDOn(LED5);
    }else {
      STM_EVAL_LEDOff(LED5);
    }
    if (sample_value[ADC_L_Y] > 0x90) {
      STM_EVAL_LEDOn(LED6);
    }else{
      STM_EVAL_LEDOff(LED6);
    }
    if (sample_value[ADC_L_X] > 0x90) {
      STM_EVAL_LEDOn(LED4);
    }else{
      STM_EVAL_LEDOff(LED4);
    }

    if ((PrevXferDone) && (USB_Device_dev.dev.device_status == USB_CONFIGURED)) {
      Send_Buffer[0] = sample_value[0];
      Send_Buffer[1] = sample_value[1];
      Send_Buffer[2] = sample_value[2];
      Send_Buffer[3] = sample_value[3];

      Send_Buffer[USB_BUFFER - 1] = 0x00;

      USBD_HID_SendReport(&USB_Device_dev, Send_Buffer, USB_BUFFER);
      PrevXferDone = 0;
    }

    /* USART_Write((uint8_t*)sample_value, 2); */
    Delay(100);
  }

  return 0;
}

void init_ADC() {
  GPIO_InitTypeDef GPIO_InitStructure;
  ADC_DeInit(ADC1);

  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOC, ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_4;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_4;
  GPIO_Init(GPIOC, &GPIO_InitStructure);

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
  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
  DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
  DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
  DMA_InitStructure.DMA_Priority = DMA_Priority_High;
  DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;

  DMA_Init(DMA1_Channel1, &DMA_InitStructure);
  DMA_Cmd(DMA1_Channel1, ENABLE);

  ADC_StructInit(&ADC_InitStructure);

  ADC_InitStructure.ADC_Resolution = ADC_Resolution_8b;
  ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;
  ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_Rising;
  ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_T1_CC4;
  ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
  ADC_InitStructure.ADC_ScanDirection = ADC_ScanDirection_Upward;
  ADC_Init(ADC1, &ADC_InitStructure);

  ADC_ChannelConfig(ADC1, ADC_Channel_1, ADC_SampleTime_7_5Cycles);
  ADC_ChannelConfig(ADC1, ADC_Channel_4, ADC_SampleTime_7_5Cycles);
  ADC_ChannelConfig(ADC1, ADC_Channel_13, ADC_SampleTime_7_5Cycles);
  ADC_ChannelConfig(ADC1, ADC_Channel_14, ADC_SampleTime_7_5Cycles);

  ADC_GetCalibrationFactor(ADC1);

  ADC_DMARequestModeConfig(ADC1, ADC_DMAMode_Circular);
  ADC_DMACmd(ADC1, ENABLE);
  ADC_Cmd(ADC1, ENABLE);
  while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_ADEN));
  ADC_StartOfConversion(ADC1);
}

void init_USART() {
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
  GPIO_InitTypeDef GPIO_InitStructure;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_1);
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_1);

  USART_InitStructure.USART_BaudRate = 115200;
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  USART_InitStructure.USART_Parity = USART_Parity_No;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
  USART_Init(USART1, &USART_InitStructure);
  USART_Cmd(USART1, ENABLE);
}

void USART_Write(uint8_t* data, uint8_t size) {
  int i = 0;
  for(i = 0; i < size; i++) { 
    while(USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);
    USART_SendData(USART1, *data++);
  }
}

