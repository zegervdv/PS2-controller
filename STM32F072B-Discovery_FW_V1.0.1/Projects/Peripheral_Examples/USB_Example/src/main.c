/**
  ******************************************************************************
  * @file    USB_Example/main.c 
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    17-January-2014
  * @brief   Main program body
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
#include "main.h"

/** @addtogroup STM32F072B_DISCOVERY
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
uint8_t Send_Buffer[2];
uint8_t PrevXferDone = 1;
USB_CORE_HANDLE  USB_Device_dev;

/* Private function prototypes -----------------------------------------------*/

/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int main(void)
{
  
  /*!< At this stage the microcontroller clock setting is already configured, 
  this is done through SystemInit() function which is called from startup
  file (startup_stm32f0xx.s) before to branch to application main.
  To reconfigure the default setting of SystemInit() function, refer to
  system_stm32f0xx.c file*/ 
  
  /* Initialize LEDs, User_Button on STM32F072B-DISCO board ***********/
  STM_EVAL_PBInit(BUTTON_USER, BUTTON_MODE_EXTI); 
  
  STM_EVAL_LEDInit(LED3);
  STM_EVAL_LEDInit(LED4);
  STM_EVAL_LEDInit(LED5);
  STM_EVAL_LEDInit(LED6);
  
  /* Initialize USB  */
  USBD_Init(&USB_Device_dev,
            &USR_desc, 
            &USBD_HID_cb, 
            &USR_cb);
  
  /* Init STMTouch driver */
  TSL_user_Init(); 
  
  while (1)
  {
    
    /* Execute STMTouch Driver state machine */
    if ((TSL_user_Action() == TSL_STATUS_OK) && (MyLinRots[0].p_Data->StateId == TSL_STATEID_DETECT))
    {       
      /* Execute sensors related tasks*/
      ProcessSensors(); 
    }
    else
    {
      MyLinRots[0].p_Data->RawPosition = 0;
      MyLinRots[0].p_Data->Position = 0;
    }
  }  
}

/**
  * @brief  Manage the activity on sensors when touched/released (example)
  * @param  None
  * @retval None
  */
void ProcessSensors(void)
{
  uint32_t TSC_RawPosition_1= 0;
  Send_Buffer[0] = 0x07;
  
  if((MyLinRots[0].p_Data->RawPosition) - (TSC_RawPosition_1) > 4)
  {
    if ((PrevXferDone) && (USB_Device_dev.dev.device_status == USB_CONFIGURED))
    {
      Send_Buffer[1] = (uint8_t)(MyLinRots[0].p_Data->RawPosition);
      
      USBD_HID_SendReport (&USB_Device_dev, Send_Buffer, 2);
      
      TSC_RawPosition_1 = MyLinRots[0].p_Data->RawPosition;
      PrevXferDone = 0;
    }
  }
}


#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif

/**
  * @}
  */


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
