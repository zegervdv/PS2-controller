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

__IO  uint16_t sample_value[4] = {0};

uint8_t Send_Buffer[USB_BUFFER];
uint8_t PrevXferDone = 1;
USB_CORE_HANDLE  USB_Device_dev;

void init_ADC(void);
void init_USART(void);
void USART_Write(uint8_t* data, uint8_t size);
void Delay(__IO uint32_t);

int main(int argc, char const* argv[]) {
  // Initialize SysTick
  RCC_ClocksTypeDef RCC_Clocks;
  RCC_GetClocksFreq(&RCC_Clocks);
  SysTick_Config(RCC_Clocks.HCLK_Frequency / 1000);
  STM_EVAL_LEDInit(LED3);
  STM_EVAL_LEDInit(LED4);
  STM_EVAL_LEDInit(LED5);
  STM_EVAL_LEDInit(LED6);

  USBD_Init(&USB_Device_dev, &USR_desc, &USBD_HID_cb, &USR_cb);
  init_ADC();
  while (1) {
    while((DMA_GetFlagStatus(DMA1_FLAG_TC1)) == RESET);
    DMA_ClearFlag(DMA1_FLAG_TC1);

    if (sample_value[ADC_R_Y] > 0x400) {
      STM_EVAL_LEDOn(LED3);
    } else {
      STM_EVAL_LEDOff(LED3);
    }
    if (sample_value[ADC_R_X] > 0x400) {
      STM_EVAL_LEDOn(LED5);
    } else {
      STM_EVAL_LEDOff(LED5);
    }
    if (sample_value[ADC_L_Y] > 0x400) {
      STM_EVAL_LEDOn(LED6);
    } else {
      STM_EVAL_LEDOff(LED6);
    }
    if (sample_value[ADC_L_X] > 0x400) {
      STM_EVAL_LEDOn(LED4);
    } else {
      STM_EVAL_LEDOff(LED4);
    }

    if ((PrevXferDone) && (USB_Device_dev.dev.device_status == USB_CONFIGURED)) {
      Send_Buffer[0] = sample_value[0] >> 4;
      Send_Buffer[1] = sample_value[1] >> 4;
      Send_Buffer[2] = sample_value[2] >> 4;
      Send_Buffer[3] = sample_value[3] >> 4;

      Send_Buffer[USB_BUFFER - 1] = 0x00;

      USBD_HID_SendReport(&USB_Device_dev, Send_Buffer, USB_BUFFER);
      PrevXferDone = 0;
    }
    Delay(100);
  }

  return 0;
}

void init_ADC() {
  GPIO_InitTypeDef GPIO_InitStructure;
  ADC_InitTypeDef ADC_InitStructure;
  DMA_InitTypeDef DMA_InitStructure;

  RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_1 | GPIO_Pin_0;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

  ADC_StructInit(&ADC_InitStructure);
  ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;
  ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
  ADC_InitStructure.ADC_ScanDirection = ADC_ScanDirection_Upward;
  ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
  ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_T1_TRGO;
  ADC_Init(ADC1, &ADC_InitStructure);

  ADC_ChannelConfig(ADC1, ADC_Channel_4, ADC_SampleTime_239_5Cycles);
  ADC_ChannelConfig(ADC1, ADC_Channel_5, ADC_SampleTime_239_5Cycles);
  ADC_ChannelConfig(ADC1, ADC_Channel_1, ADC_SampleTime_239_5Cycles);
  ADC_ChannelConfig(ADC1, ADC_Channel_0, ADC_SampleTime_239_5Cycles);

  ADC_GetCalibrationFactor(ADC1);

  ADC_DMARequestModeConfig(ADC1, ADC_DMAMode_Circular);

  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);

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

  ADC_Cmd(ADC1, ENABLE);
  ADC_DMACmd(ADC1, ENABLE);

  DMA_Cmd(DMA1_Channel1, ENABLE);

  while (!ADC_GetFlagStatus(ADC1, ADC_FLAG_ADRDY));
  ADC_StartOfConversion(ADC1);
}

