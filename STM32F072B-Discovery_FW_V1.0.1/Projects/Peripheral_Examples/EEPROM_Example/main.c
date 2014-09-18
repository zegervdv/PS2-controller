/**
  ******************************************************************************
  * @file    EEPROM_Example/main.c 
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

/** @addtogroup EEPROM_Example
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
typedef enum {FAILED = 0, PASSED = !FAILED} TestStatus; 

/* Private define ------------------------------------------------------------*/
#define sEE_WRITE_ADDRESS1        0x50
#define sEE_READ_ADDRESS1         0x50

/* Private macro -------------------------------------------------------------*/    
#define BUFFER_SIZE1             (countof(Tx1Buffer)-1)
#define BUFFER_SIZE2             (countof(Tx2Buffer)-1)
#define sEE_WRITE_ADDRESS2       (sEE_WRITE_ADDRESS1 + BUFFER_SIZE1)
#define sEE_READ_ADDRESS2        (sEE_READ_ADDRESS1 + BUFFER_SIZE1)
#define countof(a) (sizeof(a) / sizeof(*(a)))
/* Private variables ---------------------------------------------------------*/
uint8_t sEEConnected =1;
static __IO uint32_t TimingDelay;
uint8_t Tx1Buffer[] = "/* STM32F072B I2C Firmware Library EEPROM driver example";
uint8_t Tx2Buffer[] = "/* STM32F0xx I2C Firmware Library EEPROM driver example : \
I2C1 interfacing with M24LR64 EEPROM */";

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
TestStatus Buffercmp(uint8_t* pBuffer1, uint8_t* pBuffer2, uint16_t BufferLength);
  
/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int main(void)
{
 uint8_t Rx1Buffer[BUFFER_SIZE1] = {0}, Rx2Buffer[BUFFER_SIZE2] = {0};
 __IO TestStatus TransferStatus1 = FAILED, TransferStatus2 = FAILED;
 __IO uint16_t NumDataRead = 0; 
  RCC_ClocksTypeDef RCC_Clocks;
  
  /*!< At this stage the microcontroller clock setting is already configured, 
  this is done through SystemInit() function which is called from startup
  file (startup_stm32f0xx.s) before to branch to application main.
  To reconfigure the default setting of SystemInit() function, refer to
  system_stm32f0xx.c file */ 
  
  /* SysTick end of count event each 10ms */
  RCC_GetClocksFreq(&RCC_Clocks);
  SysTick_Config(RCC_Clocks.HCLK_Frequency / 100);
  
  /* Initialize LEDs, User_Button on STM32F072B-DISCO board ***********/
  STM_EVAL_PBInit(BUTTON_USER, BUTTON_MODE_EXTI); 
  
  STM_EVAL_LEDInit(LED3);
  STM_EVAL_LEDInit(LED5);
  STM_EVAL_LEDInit(LED6);
  
  /* Initialize the I2C EEPROM driver ----------------------------------------*/
  sEE_Init();  
 
  /* Wait for EEPROM standby state */
  sEE_WaitEepromStandbyState(); 
  
  /* Using sEE_WaitEepromStandbyState(), we wait for EEPROM standby state. If EEPROM 
     is not connected program goes to sEE_TIMEOUT_UserCallback() timeout function in 
     which sEEConnected is set to 0 */  
  if (sEEConnected == 1)
  {
    /* First write in the memory followed by a read of the written data ------*/
    /* Write on I2C EEPROM from sEE_WRITE_ADDRESS1 */
    sEE_WriteBuffer(Tx1Buffer, sEE_WRITE_ADDRESS1, BUFFER_SIZE1); 
    
    /* Wait for EEPROM standby state */
    sEE_WaitEepromStandbyState();  
    
    /* Set the Number of data to be read */
    NumDataRead = BUFFER_SIZE1;
    
    /* Read from I2C EEPROM from sEE_READ_ADDRESS1 */
    sEE_ReadBuffer(Rx1Buffer, sEE_READ_ADDRESS1, (uint16_t *)(&NumDataRead)); 
    /* Check if the data written to the memory is read correctly */
    
    TransferStatus1 = Buffercmp(Tx1Buffer, Rx1Buffer, BUFFER_SIZE1);
    
    if(TransferStatus1 != FAILED)
    {
      STM_EVAL_LEDOn(LED5);
      Delay(10);
    }
    else 
    {
      STM_EVAL_LEDOn(LED3);
    }
    /* Second write in the memory followed by a read of the written data -----*/
    /* Write on I2C EEPROM from sEE_WRITE_ADDRESS2 */
    sEE_WriteBuffer(Tx2Buffer, sEE_WRITE_ADDRESS2, BUFFER_SIZE2); 
    
    /* Wait for EEPROM standby state */
    sEE_WaitEepromStandbyState();  
    
    /* Set the Number of data to be read */
    NumDataRead = BUFFER_SIZE2;  
    
    /* Read from I2C EEPROM from sEE_READ_ADDRESS2 */
    sEE_ReadBuffer(Rx2Buffer, sEE_READ_ADDRESS2, (uint16_t *)(&NumDataRead));
    /* Check if the data written to the memory is read correctly */
    TransferStatus2 = Buffercmp(Tx2Buffer, Rx2Buffer, BUFFER_SIZE2);
    
    if(TransferStatus2 != FAILED)
    {
      STM_EVAL_LEDOn(LED6);
      Delay(15);
    }
    else 
    {
      STM_EVAL_LEDOn(LED3);
    }
    /* Free all used resources */
    sEE_DeInit();
  }
  else
  {
    STM_EVAL_LEDOn(LED3);
  }
  
  /* Infinite loop */
  while (1)
  {
    
  }  
}

/**
  * @brief  Compares two buffers.
  * @param  pBuffer1, pBuffer2: buffers to be compared.
  * @param  BufferLength: buffer's length
  * @retval PASSED: pBuffer1 identical to pBuffer2
  *         FAILED: pBuffer1 differs from pBuffer2
  */
TestStatus Buffercmp(uint8_t* pBuffer1, uint8_t* pBuffer2, uint16_t BufferLength)
{
  while(BufferLength--)
  {
    if(*pBuffer1 != *pBuffer2)
    {
      return FAILED;
    }
    
    pBuffer1++;
    pBuffer2++;
  }

  return PASSED;  
}

/**
  * @brief  Basic management of the timeout situation.
  * @param  None.
  * @retval 0.
  */
uint32_t sEE_TIMEOUT_UserCallback(void)
{
  
  sEEConnected = 0;
  
  return 0;
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
