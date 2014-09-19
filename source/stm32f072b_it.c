#include "stm32f0xx_conf.h"
#include "usbd_custom_hid_core.h"

static __IO uint32_t TimingDelay;
void TimingDelay_Decrement(void);

extern __IO uint32_t Gv_EOA;
extern USB_CORE_HANDLE USB_Device_dev;
extern uint8_t Send_Buffer[2];
extern uint8_t PrevXferDone;

void SysTick_Handler(void) {
  TimingDelay_Decrement();
}

/**
  * @brief  Inserts a delay time.
  * @param  nTime: specifies the delay time length, in 10 ms.
  * @retval None
  */
void Delay(__IO uint32_t nTime)
{
  TimingDelay = nTime;

  while(TimingDelay != 0);
}

/**
  * @brief  Decrements the TimingDelay variable.
  * @param  None
  * @retval None
  */
void TimingDelay_Decrement(void)
{
  if (TimingDelay != 0x00)
  { 
    TimingDelay--;
  }
}

void USB_IRQHandler(void)
{
  USB_Istr();
}
