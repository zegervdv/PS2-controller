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

volatile uint8_t sample_value[4] = {0};

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
    // Send out test values
    sample_value[ADC_R_X] = (uint8_t)ADC_GetConversionValue(ADC1);

    if (sample_value[ADC_R_Y] > 0x90) {
      STM_EVAL_LEDOn(LED3);
    } else {
      STM_EVAL_LEDOff(LED3);
    }
    if (sample_value[ADC_R_X] > 0x90) {
      STM_EVAL_LEDOn(LED5);
    } else {
      STM_EVAL_LEDOff(LED5);
    }
    if (sample_value[ADC_L_Y] > 0x90) {
      STM_EVAL_LEDOn(LED6);
    } else {
      STM_EVAL_LEDOff(LED6);
    }
    if (sample_value[ADC_L_X] > 0x90) {
      STM_EVAL_LEDOn(LED4);
    } else {
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
    Delay(100);
  }

  return 0;
}

void init_ADC() {
  GPIO_InitTypeDef GPIO_InitStructure;
  ADC_InitTypeDef ADC_InitStructure;

  RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

  ADC_StructInit(&ADC_InitStructure);
  ADC_InitStructure.ADC_Resolution = ADC_Resolution_8b;
  ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
  ADC_InitStructure.ADC_ScanDirection = ADC_ScanDirection_Upward;
  ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
  ADC_Init(ADC1, &ADC_InitStructure);

  ADC_ChannelConfig(ADC1, ADC_Channel_4, ADC_SampleTime_7_5Cycles);
  ADC_Cmd(ADC1, ENABLE);

  while (!ADC_GetFlagStatus(ADC1, ADC_FLAG_ADRDY));
  ADC_StartOfConversion(ADC1);

}

