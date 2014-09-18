/**
  ******************************************************************************
  * @file    FLASH_Program/main.c 
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

/** @addtogroup STM32F072B_DISCOVERY_Examples
  * @{
  */

/** @addtogroup FLASH_Program
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
typedef enum {FAILED = 0, PASSED = !FAILED} TestStatus;
/* Private define ------------------------------------------------------------*/
#define FLASH_PAGE_SIZE         ((uint32_t)0x00000400)   /* FLASH Page Size */
#define FLASH_USER_START_ADDR   ((uint32_t)0x08006000)   /* Start @ of user Flash area */
#define FLASH_USER_END_ADDR     ((uint32_t)0x08007000)   /* End @ of user Flash area */
#define uwData_32               ((uint32_t)0x12345678)

/* Private macro -------------------------------------------------------------*/    
/* Private variables ---------------------------------------------------------*/
__IO FLASH_Status FLASHStatus = FLASH_COMPLETE;
__IO TestStatus MemoryProgramStatus = PASSED;

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int main(void)
{
  uint32_t uwEraseCounter = 0x00, uwAddress = 0x00;
  uint32_t uwData = 0x3210ABCD;
  uint32_t uwNbrOfPage = 0x00;
  
  /*!< At this stage the microcontroller clock setting is already configured, 
  this is done through SystemInit() function which is called from startup
  file (startup_stm32f0xx.s) before to branch to application main.
  To reconfigure the default setting of SystemInit() function, refer to
  system_stm32f0xx.c file
  */ 
  
  /* Initialize LEDs mounted on STM32F072B-DISCO board */
  STM_EVAL_LEDInit(LED3);
  STM_EVAL_LEDInit(LED5);
  
  /* Unlock the Flash to enable the flash control register access *************/ 
  FLASH_Unlock();
  
  /* Erase the user Flash area
  (area defined by FLASH_USER_START_ADDR and FLASH_USER_END_ADDR) ***********/
  
  /* Clear pending flags (if any) */  
  FLASH_ClearFlag(FLASH_FLAG_EOP | FLASH_FLAG_PGERR | FLASH_FLAG_WRPERR); 
  
  /* Define the number of page to be erased */
  uwNbrOfPage = (FLASH_USER_END_ADDR - FLASH_USER_START_ADDR) / FLASH_PAGE_SIZE;
  
  /* Erase the FLASH pages */
  for(uwEraseCounter = 0; (uwEraseCounter < uwNbrOfPage) && (FLASHStatus == FLASH_COMPLETE); uwEraseCounter++)
  {
    if (FLASH_ErasePage(FLASH_USER_START_ADDR + (FLASH_PAGE_SIZE * uwEraseCounter))!= FLASH_COMPLETE)
    {
      /* Error occurred while sector erase. 
      User can add here some code to deal with this error  */
      while (1)
      {
      }
    }
  }
  /* Program the user Flash area word by word
  (area defined by FLASH_USER_START_ADDR and FLASH_USER_END_ADDR) ***********/
  
  uwAddress = FLASH_USER_START_ADDR;
  
  while (uwAddress < FLASH_USER_END_ADDR)
  {
    if (FLASH_ProgramWord(uwAddress, uwData_32) == FLASH_COMPLETE)
    {
      uwAddress = uwAddress + 4;
    }
    else
    { 
      /* Error occurred while writing uwData in Flash memory. 
      User can add here some code to deal with this error */
      while (1)
      {
      }
    }
  }
  
  /* Lock the Flash to disable the flash control register access (recommended
  to protect the FLASH memory against possible unwanted operation) *********/
  FLASH_Lock(); 
  
  
  /* Check if the programmed uwData is OK 
  MemoryProgramStatus = 0: uwData programmed correctly
  MemoryProgramStatus != 0: number of words not programmed correctly ******/
  uwAddress = FLASH_USER_START_ADDR;
  MemoryProgramStatus = PASSED;
  
  while (uwAddress < FLASH_USER_END_ADDR)
  {
    uwData = *(__IO uint32_t *)uwAddress;
    
    if (uwData != uwData_32)
    {
      MemoryProgramStatus = FAILED;  
    }
    
    uwAddress = uwAddress + 4;
  }
  
  /* Check uwData correctness */
  if(MemoryProgramStatus != PASSED)
  {
    /* KO */
    /* Turn on LD3 */
    STM_EVAL_LEDOn(LED3);
  }
  else
  {
    /* OK */
    /* Turn on LD5 */
    STM_EVAL_LEDOn(LED5);    
  }
  
  /* Infinite loop */
  while (1)
  {
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

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
