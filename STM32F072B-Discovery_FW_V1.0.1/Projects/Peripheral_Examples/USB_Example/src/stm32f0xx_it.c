/**
  ******************************************************************************
  * @file    USB_Example/stm32f0xx_it.c 
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    17-January-2014
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and 
  *          peripherals interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2014 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */ 

/* Includes ------------------------------------------------------------------*/
#include "stm32f0xx_it.h"

/** @addtogroup STM32F072B_DISCOVERY
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
extern __IO uint32_t Gv_EOA;
extern USB_CORE_HANDLE USB_Device_dev;
extern uint8_t Send_Buffer[2];
extern uint8_t PrevXferDone;

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M0 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
}

/******************************************************************************/
/*                 STM32F0xx Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f0xx.s).                                            */
/******************************************************************************/


void USB_IRQHandler(void)
{
  USB_Istr();
}

/**
  * @brief  This function handles Touch Sensing Controller Handler.
  * @param  None
  * @retval None
  */
void TSC_IRQHandler(void)
{
#if TSLPRM_TSC_IODEF > 0 // Default = Input Floating
  /* Set IO default in Output PP Low to discharge all capacitors */
  TSC->CR &= (uint32_t)(~(1 << 4));
#endif
  TSC->ICR |= 0x03; /* Clear EOAF and MCEF flags */
  Gv_EOA = 1; /* To inform the main loop routine of the End Of Acquisition */
}
/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval None
  */
void EXTI0_1_IRQHandler(void)
{ 
  if (EXTI_GetITStatus(USER_BUTTON_EXTI_LINE) != RESET)
  {
    if((PrevXferDone)  && (USB_Device_dev.dev.device_status==USB_CONFIGURED))
    {
      Send_Buffer[0] = 0x05; 
      
      if (STM_EVAL_PBGetState(BUTTON_USER) != Bit_RESET)
      {
        Send_Buffer[1] = 0x01;
      }
      else
      {
        Send_Buffer[1] = 0x00;
      }
      
      USBD_HID_SendReport (&USB_Device_dev, Send_Buffer, 2);  
      PrevXferDone = 0;
    }
    
    /* Clear the EXTI line pending bit */
    EXTI_ClearITPendingBit(USER_BUTTON_EXTI_LINE);
  }
}

/**
  * @}
  */ 

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
