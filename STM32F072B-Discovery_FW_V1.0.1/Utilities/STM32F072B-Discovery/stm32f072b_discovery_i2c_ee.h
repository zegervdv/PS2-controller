/**
  ******************************************************************************
  * @file    stm32f072b_discovery_i2c_ee.h
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    27-December-2013
  * @brief   This file contains all the functions prototypes for 
  *          the stm32f072b_discovery_i2c_ee.c firmware driver.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2013 STMicroelectronics</center></h2>
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM32F072B_DISCOVERY_I2C_EE_H
#define __STM32F072B_DISCOVERY_I2C_EE_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f072b_discovery.h"
/** @addtogroup Utilities
  * @{
  */

/** @addtogroup STM32F072B_DISCOVERY
  * @{
  */
  
/** @addtogroup STM32F072B_DISCOVERY_I2C_EE
  * @{
  */  

/** @defgroup STM32F072B_DISCOVERY_I2C_EE_Exported_Types
  * @{
  */ 

/**
  * @}
  */
   
/** @addtogroup STM32F072B_DISCOVERY_LOW_LEVEL_I2C_EE
  * @{
  */
/**
  * @brief  I2C EEPROM Interface pins
  */  
#define sEE_I2C                          I2C2
#define sEE_I2C_CLK                      RCC_APB1Periph_I2C2
#define sEE_I2C_SCL_PIN                  GPIO_Pin_10                 /* PB.10 */
#define sEE_I2C_SCL_GPIO_PORT            GPIOB                       /* GPIOB */
#define sEE_I2C_SCL_GPIO_CLK             RCC_AHBPeriph_GPIOB
#define sEE_I2C_SCL_SOURCE               GPIO_PinSource10
#define sEE_I2C_SCL_AF                   GPIO_AF_1
#define sEE_I2C_SDA_PIN                  GPIO_Pin_11                 /* PB.11 */
#define sEE_I2C_SDA_GPIO_PORT            GPIOB                       /* GPIOB */
#define sEE_I2C_SDA_GPIO_CLK             RCC_AHBPeriph_GPIOB
#define sEE_I2C_SDA_SOURCE               GPIO_PinSource11
#define sEE_I2C_SDA_AF                   GPIO_AF_1
  
#define sEE_DIRECTION_TX                 0
#define sEE_DIRECTION_RX                 1  

/**
  * @}
  */  
   
/** @defgroup STM32F072B_DISCOVERY_I2C_EE_Exported_Constants
  * @{
  */

/* Select which EEPROM will be used with this driver */
#define sEE_M24LR64

/* Uncomment the following line to use the default sEE_TIMEOUT_UserCallback() 
   function implemented in stm320518_evel_i2c_ee.c file.
   sEE_TIMEOUT_UserCallback() function is called whenever a timeout condition 
   occur during communication (waiting on an event that doesn't occur, bus 
   errors, busy devices ...). */   
// #define USE_DEFAULT_TIMEOUT_CALLBACK

/* EEPROM hardware address and page size */ 
#define sEE_HW_ADDRESS         0xA0
#define sEE_PAGESIZE           4
                                
/* Maximum Timeout values for flags and events waiting loops. These timeouts are
   not based on accurate values, they just guarantee that the application will 
   not remain stuck if the I2C communication is corrupted.
   You may modify these timeout values depending on CPU frequency and application
   conditions (interrupts routines ...). */   
#define sEE_FLAG_TIMEOUT         ((uint32_t)0x1000)
#define sEE_LONG_TIMEOUT         ((uint32_t)(10 * sEE_FLAG_TIMEOUT))

   /* The I2C Timing is calculated respecting the following conditions:
      - I2C clock source frequency is the system clock: 48MHz
      - I2C speed frequency: 100KHz
      - Rise time: 122ns
      - Fall time: 4ns
   */
#define sEE_I2C_TIMING            0x40B22536
/* Maximum number of trials for sEE_WaitEepromStandbyState() function */
#define sEE_MAX_TRIALS_NUMBER     300
      
#define sEE_OK                    0
#define sEE_FAIL                  1     

/**
  * @}
  */ 
  
/** @defgroup STM32F072B_DISCOVERY_I2C_EE_Exported_Macros
  * @{
  */    
/**
  * @}
  */ 

/** @defgroup STM32F072B_DISCOVERY_I2C_EE_Exported_Functions
  * @{
  */ 
void sEE_DeInit(void);
void sEE_Init(void);
void sEE_LowLevel_Init(void);
void sEE_LowLevel_DeInit(void);
uint32_t sEE_ReadBuffer(uint8_t* pBuffer, uint16_t ReadAddr, uint16_t* NumByteToRead);
uint32_t sEE_WritePage(uint8_t* pBuffer, uint16_t WriteAddr, uint8_t* NumByteToWrite);
void     sEE_WriteBuffer(uint8_t* pBuffer, uint16_t WriteAddr, uint16_t NumByteToWrite);
uint32_t sEE_WaitEepromStandbyState(void);

/* USER Callbacks: These are functions for which prototypes only are declared in
   EEPROM driver and that should be implemented into user application. */  
/* sEE_TIMEOUT_UserCallback() function is called whenever a timeout condition 
   occur during communication (waiting on an event that doesn't occur, bus 
   errors, busy devices ...).
   You can use the default timeout callback implementation by uncommenting the 
   define USE_DEFAULT_TIMEOUT_CALLBACK in stm320518_evel_i2c_ee.h file.
   Typically the user implementation of this callback should reset I2C peripheral
   and reinitialize communication or in worst case reset all the application. */
uint32_t sEE_TIMEOUT_UserCallback(void);

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* __STM32F072B_DISCOVERY_I2C_EE_H */

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */ 

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
