/**
  ******************************************************************************
  * @file    TIM_TimeBase/main.c 
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

/** @addtogroup TIM_TimeBase
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/    
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
static void TIM_Config(void);

/* Private functions ---------------------------------------------------------*/

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
  system_stm32f0xx.c file
  */ 
  /* Initialize Leds mounted on STM32F072B-DISCO board ************************/  
  STM_EVAL_LEDInit(LED3);
  STM_EVAL_LEDInit(LED4);
  STM_EVAL_LEDInit(LED5);
  STM_EVAL_LEDInit(LED6); 
    
  /* TIM Configuration ---------------------------------------------------------
     In this example TIM7 counter clock (TIM7CLK) is set to APB1 clock (PCLK1), since
   APB1 prescaler is set to 1 and TIM7 prescaler is set to 0.
  
  In this example TIM7 input clock (TIM7CLK) is set to APB1 clock (PCLK1), 
  since APB1 prescaler is set to 1.   
  TIM7CLK = PCLK1 = HCLK = SystemCoreClock
  
  With Prescaler set to 479 and Period to 24999, the TIM7 counter is updated each 250 ms
  (i.e. and interrupt is generated each 250 ms)
     TIM7 counter clock = TIM7CLK /((Prescaler + 1)*(Period + 1))
                        = 48 MHz / ((25000)*(480))
                        = 4 Hz 
     ==> TIM7 counter period = 250 ms

  Note:
  SystemCoreClock variable holds HCLK frequency and is defined in system_stm32f0xx.c file.
  Each time the core clock (HCLK) changes, user had to call SystemCoreClockUpdate()
  function to update SystemCoreClock variable value. Otherwise, any configuration
  based on this variable will be incorrect. 
  ----------------------------------------------------------------------------*/
  TIM_Config();
  
  /* Infinite loop */
  while (1)
  {
  }
}

/**
  * @brief  Configure the TIM7 to generate an interrupt each 250ms.
  * @param  None
  * @retval None
  */
static void TIM_Config(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
  
  /* TIM7 clock enable */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM7, ENABLE);
  
  /* Enable the TIM7 gloabal Interrupt */
  NVIC_InitStructure.NVIC_IRQChannel = TIM7_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);

  /* -----------------------------------------------------------------------
   In this example TIM7 counter clock (TIM7CLK) is set to APB1 clock (PCLK1), since
   APB1 prescaler is set to 1 and TIM7 prescaler is set to 0.
  
  In this example TIM7 input clock (TIM7CLK) is set to APB1 clock (PCLK1), 
  since APB1 prescaler is set to 1.   
  TIM7CLK = PCLK1 = HCLK = SystemCoreClock
  
  With Prescaler set to 479 and Period to 24999, the TIM7 counter is updated each 250 ms
  (i.e. and interrupt is generated each 250 ms)
     TIM7 counter clock = TIM7CLK /((Prescaler + 1)*(Period + 1))
                        = 48 MHz / ((25000)*(480))
                        = 4 Hz 
     ==> TIM7 counter period = 250 ms

  Note:
  SystemCoreClock variable holds HCLK frequency and is defined in system_stm32f0xx.c file.
  Each time the core clock (HCLK) changes, user had to call SystemCoreClockUpdate()
  function to update SystemCoreClock variable value. Otherwise, any configuration
  based on this variable will be incorrect.    
  ----------------------------------------------------------------------- */ 
  /* Time base configuration */
  TIM_TimeBaseStructure.TIM_Period = 24999;
  TIM_TimeBaseStructure.TIM_Prescaler = 479;
  TIM_TimeBaseStructure.TIM_ClockDivision = 0;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
  TIM_TimeBaseInit(TIM7, &TIM_TimeBaseStructure);
  
  /* TIM Interrupts enable */
  TIM_ITConfig(TIM7, TIM_IT_Update, ENABLE);
  
  /* TIM7 enable counter */
  TIM_Cmd(TIM7, ENABLE);
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
