/**
  ******************************************************************************
  * @file    Projects\Demonstration\main.c 
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
#define L3G_Sensitivity_250dps     (float)   114.285f         /*!< gyroscope sensitivity with 250 dps full scale [LSB/dps]  */
#define L3G_Sensitivity_500dps     (float)    57.1429f        /*!< gyroscope sensitivity with 500 dps full scale [LSB/dps]  */
#define L3G_Sensitivity_2000dps    (float)    14.285f         /*!< gyroscope sensitivity with 2000 dps full scale [LSB/dps] */
/* Private macro -------------------------------------------------------------*/
#define ABS(x)  ((x) > 0 ? (x) : -(x)) 

/* Private variables ---------------------------------------------------------*/
static __IO uint32_t TimingDelay;
extern __IO uint32_t ButtonPressed;
USB_CORE_HANDLE  USB_Device_dev;

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
static uint8_t *USBD_HID_GetPos (void);

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
  
    /* Setup SysTick Timer for 1 msec interrupts.*/
  if (SysTick_Config(SystemCoreClock / 1000))
  { 
    /* Capture error */ 
    while (1);
  }     
  
  /* Initialize LEDs, User Button on STM32F072B-DISCO board ***********/
  STM_EVAL_PBInit(BUTTON_USER, BUTTON_MODE_EXTI); 
  
  STM_EVAL_LEDInit(LED3);
  STM_EVAL_LEDInit(LED4);
  STM_EVAL_LEDInit(LED5);
  STM_EVAL_LEDInit(LED6);
  
  /* Initialize Mems Gyroscope */
  Demo_GyroConfig();
  
  /* Initialize USB Device */
  USBD_Init(&USB_Device_dev,
            &USR_desc, 
            &USBD_HID_cb, 
            &USR_cb);
  
  /* Init STMTouch driver */
  TSL_user_Init(); 
  
   /* End of Initialisation */
  
    /* Delay 1s to select Test Program or to go directly through the demo*/
  Delay (1000);
  
  if (STM_EVAL_PBGetState(BUTTON_USER) == Bit_SET )
  {
    /* Wait for User button is released */
    while (STM_EVAL_PBGetState(BUTTON_USER) != Bit_RESET)
    {}
    
    /* Set ButtonPressed at 0 value  */ 
    ButtonPressed = 0;
    
    /* LED test : Blinking LEDs  */ 
    LED_Test();
    
    /* Wait for User button to be pressed to switch to USB Test
    the cursor move in square path and led On corresponding to such direction  */
    USB_Test();
    
    /* Move Discovery board to execute MEMS Test, Mems detect the angular rate
    and led On corresponding to such direction*/ 
    MEMS_Test();
    
    /* Wait for User button to be pressed to switch to Touch Sensor Test
    each TouchKey pointed correspond to specific Leds On, test can performed
    in both direction */ 
    LTS_Test();
  }
  
  /* Infinite loop */
  while (1)
  {  
    Demo();
  }
}

/**
* @brief  Demo regroup three chid demonstration on USB, Mems and LTS.
* @param  None
* @retval None
*/
void Demo(void)
{
  
  /*  Blinking LEDs & Wait for User button to be pressed to switch to MEMS demo */
  while (STM_EVAL_PBGetState(BUTTON_USER) != Bit_SET)
  {    
    /* Toggle LED3, LED4, LED5 & LED6 */
    STM_EVAL_LEDToggle(LED3);
    STM_EVAL_LEDToggle(LED6);
    STM_EVAL_LEDToggle(LED5);
    STM_EVAL_LEDToggle(LED4);
    
    /* Insert 100ms delay */
    Delay(100);   
  }
  /* Wait for User button is released */
  while (STM_EVAL_PBGetState(BUTTON_USER) != Bit_RESET)
  {}
  /* Turn Off Leds */   
  STM_EVAL_LEDOff(LED3);
  STM_EVAL_LEDOff(LED4);
  STM_EVAL_LEDOff(LED5);
  STM_EVAL_LEDOff(LED6);
  
  /* Move Discovery board to execute MEMS demo, Mems detect the angular rate
  and led On corresponding to such direction*/ 
  MEMS_Demo();
  
  /* Wait for User button to be pressed to switch to USB demo
  Mouse cursor moving corresponding to board move direction  */
  USB_Demo();
  
  /* Wait for User button to be pressed to switch to Touch Sensor Test
  each TouchKey pointed correspond to specific Leds On, test can performed
  in both direction */ 
  LTS_Test();
}

/**
* @brief  check LEDs and user button.
* @param  None
* @retval None
*/
void LED_Test(void)
{
  
  while (ButtonPressed!=1)
  { 
    /* Toggle LD3 */
    STM_EVAL_LEDToggle(LED3);
    /* Insert 50ms delay */
    Delay(50);
    /* Toggle LD5 */
    STM_EVAL_LEDToggle(LED5);
    /* Insert 50ms delay */
    Delay(50);
    if (ButtonPressed == 0x01)
    { 
      STM_EVAL_LEDOff(LED3);
      STM_EVAL_LEDOff(LED4);
      STM_EVAL_LEDOff(LED5);
      STM_EVAL_LEDOff(LED6);
    }
    else
    {    
      /* Toggle LD6 */
      STM_EVAL_LEDToggle(LED6);
      /* Insert 50ms delay */
      Delay(50);
      /* Toggle LD4 */
      STM_EVAL_LEDToggle(LED4);
      /* Insert 50ms delay */
      Delay(50);
    }    
  }
  /* Wait for User button is released */
  while (STM_EVAL_PBGetState(BUTTON_USER) != Bit_RESET)
  {}
  /* Turn Off Leds */   
  STM_EVAL_LEDOff(LED3);
  STM_EVAL_LEDOff(LED4);
  STM_EVAL_LEDOff(LED5);
  STM_EVAL_LEDOff(LED6);
  
}

/**
* @brief  Angular rate are detected when moving Discovery,MEMS Test :
*         Interrupt mode : LED3 On (Test KO) or LED5 is On (Interrupt mode OK)
*         polling mode : correspondent LED is ON
* @param  None
* @retval None
*/
void MEMS_Test(void)
{
  float Buffer[6] = {0};
  uint8_t Xval, Yval = 0x00;
  
  /* Test in Interrupt mode*/
  /* Enable INT1 interrupt */  
  L3GD20_INT1InterruptCmd(ENABLE);
  
  /* Configure interrupts on all axes */
  L3GD20_INT1InterruptConfig(L3GD20_AXES_INTERRUPT_ENABLE);
  
  /*  LED3 On */    
  STM_EVAL_LEDOn(LED3);
  
  /*  Wait for User button to be pressed to switch to polling mode */
  while (STM_EVAL_PBGetState(BUTTON_USER) != Bit_SET)
  {}
  /* Wait for User button is released */
  while (STM_EVAL_PBGetState(BUTTON_USER) != Bit_RESET)
  {}
    /* Turn Off Leds */   
  STM_EVAL_LEDOff(LED3);
  STM_EVAL_LEDOff(LED4);
  STM_EVAL_LEDOff(LED5);
  STM_EVAL_LEDOff(LED6);
  
  /* End of Test in Interrupt mode*/
  
  /* Start Test in polling mode*/
  while (STM_EVAL_PBGetState(BUTTON_USER) != Bit_SET)
  {
    /* Read Gyro Angular data */
    Demo_GyroReadAngRate(Buffer); 
    /* Update auto-reload and capture compare registers value*/
    Xval = ABS((int8_t)(Buffer[0]));
    Yval = ABS((int8_t)(Buffer[1])); 
    
    if ( Xval>Yval)
    {
      if ((int16_t)Buffer[0] > 40)
      { 
        /*  LED5 On */   
        STM_EVAL_LEDOff(LED3);
        STM_EVAL_LEDOff(LED4);
        STM_EVAL_LEDOn(LED5);
        STM_EVAL_LEDOff(LED6);
        
        /* Insert 250ms delay */ 
        Delay(25);
      }
      if ((int16_t)Buffer[0] < -40)
      { 
        /* LED4 On */
        STM_EVAL_LEDOff(LED3);
        STM_EVAL_LEDOn(LED4);
        STM_EVAL_LEDOff(LED5);
        STM_EVAL_LEDOff(LED6);
        
        /* Insert 250ms delay */ 
        Delay(25);
      }
    }
    else
    {
      if ((int16_t)Buffer[1] > 40)
      {
        /* LED3 On */
        STM_EVAL_LEDOn(LED3);
        STM_EVAL_LEDOff(LED4);
        STM_EVAL_LEDOff(LED5);
        STM_EVAL_LEDOff(LED6);     
        
        /* Insert 250ms delay */ 
        Delay(25);
      }
      if ((int16_t)Buffer[1] < -40)
      {
        /* LED6 On */
        STM_EVAL_LEDOff(LED3);
        STM_EVAL_LEDOff(LED4);
        STM_EVAL_LEDOff(LED5);
        STM_EVAL_LEDOn(LED6);   
        
        /* Insert 250ms delay */   
        Delay(25);
      } 
    }
  }
  
  /* Wait for User button is released */
  while (STM_EVAL_PBGetState(BUTTON_USER) != Bit_RESET)
  {}
  /* Turn Off Leds */   
  STM_EVAL_LEDOff(LED3);
  STM_EVAL_LEDOff(LED4);
  STM_EVAL_LEDOff(LED5);
  STM_EVAL_LEDOff(LED6);
}

/**
* @brief  MEMS Demo using polling mode, Angular rate are detected,
*         when moving Discovery, and correspondent LED is ON.
* @param  None
* @retval None
*/
void MEMS_Demo(void)
{
  float Buffer[6] = {0};
  uint8_t Xval, Yval = 0x00;
     
  while (STM_EVAL_PBGetState(BUTTON_USER) != Bit_SET)
  {
    /* Read Gyro Angular data */
    Demo_GyroReadAngRate(Buffer); 
    /* Update autoreload and capture compare registers value*/
    Xval = ABS((int8_t)(Buffer[0]));
    Yval = ABS((int8_t)(Buffer[1])); 
    
    if ( Xval>Yval)
    {
      if ((int16_t)Buffer[0] > 40)
      { 
        /*  LED5 On */   
        STM_EVAL_LEDOff(LED3);
        STM_EVAL_LEDOff(LED4);
        STM_EVAL_LEDOn(LED5);
        STM_EVAL_LEDOff(LED6);
        
        /* Insert 250ms delay */ 
        Delay(25);
      }
      if ((int16_t)Buffer[0] < -40)
      { 
        /* LED4 On */
        STM_EVAL_LEDOff(LED3);
        STM_EVAL_LEDOn(LED4);
        STM_EVAL_LEDOff(LED5);
        STM_EVAL_LEDOff(LED6);
        
        /* Insert 250ms delay */ 
        Delay(25);
      }
    }
    else
    {
      if ((int16_t)Buffer[1] > 40)
      {
        /* LED3 On */
        STM_EVAL_LEDOn(LED3);
        STM_EVAL_LEDOff(LED4);
        STM_EVAL_LEDOff(LED5);
        STM_EVAL_LEDOff(LED6);     
        
        /* Insert 250ms delay */ 
        Delay(25);
      }
      if ((int16_t)Buffer[1] < -40)
      {
        /* LED6 On */
        STM_EVAL_LEDOff(LED3);
        STM_EVAL_LEDOff(LED4);
        STM_EVAL_LEDOff(LED5);
        STM_EVAL_LEDOn(LED6);   
        
        /* Insert 250ms delay */   
        Delay(25);
      } 
    }
  }
  
  /* Wait for User button is released */
  while (STM_EVAL_PBGetState(BUTTON_USER) != Bit_RESET)
  {}
  /* Turn Off Leds */   
  STM_EVAL_LEDOff(LED3);
  STM_EVAL_LEDOff(LED4);
  STM_EVAL_LEDOff(LED5);
  STM_EVAL_LEDOff(LED6);
}

/**
* @brief  Configure the Mems to gyroscope application.
* @param  None
* @retval None
*/
void Demo_GyroConfig(void)
{
  L3GD20_InitTypeDef L3GD20_InitStructure;
  L3GD20_FilterConfigTypeDef L3GD20_FilterStructure;
  
  /* Configure Mems L3GD20 */
  L3GD20_InitStructure.Power_Mode = L3GD20_MODE_ACTIVE;
  L3GD20_InitStructure.Output_DataRate = L3GD20_OUTPUT_DATARATE_1;
  L3GD20_InitStructure.Axes_Enable = L3GD20_AXES_ENABLE;
  L3GD20_InitStructure.Band_Width = L3GD20_BANDWIDTH_1;
  L3GD20_InitStructure.BlockData_Update = L3GD20_BlockDataUpdate_Single;
  L3GD20_InitStructure.Endianness = L3GD20_BLE_LSB;
  L3GD20_InitStructure.Full_Scale = L3GD20_FULLSCALE_2000;
  L3GD20_Init(&L3GD20_InitStructure);
  
  L3GD20_FilterStructure.HighPassFilter_Mode_Selection =L3GD20_HPM_NORMAL_MODE_RES;
  L3GD20_FilterStructure.HighPassFilter_CutOff_Frequency = L3GD20_HPFCF_0;
  L3GD20_FilterConfig(&L3GD20_FilterStructure) ;
  
  L3GD20_FilterCmd(L3GD20_HIGHPASSFILTER_ENABLE);
}

/**
* @brief  Calculate the angular Data rate Gyroscope.
* @param  pfData : Data out pointer
* @retval None
*/
void Demo_GyroReadAngRate (float* pfData)
{
  uint8_t tmpbuffer[6] ={0};
  int16_t RawData[3] = {0};
  uint8_t tmpreg = 0;
  float sensitivity = 0;
  int i =0;
  
  L3GD20_Read(&tmpreg,L3GD20_CTRL_REG4_ADDR,1);
  
  L3GD20_Read(tmpbuffer,L3GD20_OUT_X_L_ADDR,6);
  
  /* check in the control register 4 the data alignment (Big Endian or Little Endian)*/
  if(!(tmpreg & 0x40))
  {
    for(i=0; i<3; i++)
    {
      RawData[i]=(int16_t)(((uint16_t)tmpbuffer[2*i+1] << 8) + tmpbuffer[2*i]);
    }
  }
  else
  {
    for(i=0; i<3; i++)
    {
      RawData[i]=(int16_t)(((uint16_t)tmpbuffer[2*i] << 8) + tmpbuffer[2*i+1]);
    }
  }
  
  /* Switch the sensitivity value set in the CRTL4 */
  switch(tmpreg & 0x30)
  {
  case 0x00:
    sensitivity=L3G_Sensitivity_250dps;
    break;
    
  case 0x10:
    sensitivity=L3G_Sensitivity_500dps;
    break;
    
  case 0x20:
    sensitivity=L3G_Sensitivity_2000dps;
    break;
  default:
    sensitivity=L3G_Sensitivity_250dps;

  }
  /* divide by sensitivity */
  for(i=0; i<3; i++)
  {
    pfData[i]=(float)RawData[i]/sensitivity;
  }
}

/**
* @brief  Basic management of the timeout situation.
* @param  None.
* @retval None.
*/
uint32_t L3GD20_TIMEOUT_UserCallback(void)
{
  return 0;
} 


/**
* @brief  USB recognized as a standard mouse
*         cursor moving according to discovery moving
* @param  None 
* @retval None
*/
void USB_Demo(void)
{
  
  uint8_t *buf;
  
  STM_EVAL_LEDOn(LED3);
  STM_EVAL_LEDOff(LED6);
  
  while ((STM_EVAL_PBGetState(BUTTON_USER) != Bit_SET))
  {
    buf = USBD_HID_GetPos();
    
    if((buf[1] != 0) ||(buf[2] != 0))
    {
      USBD_HID_SendReport (&USB_Device_dev, 
                           buf,
                           4);
      /* Insert 50ms delay */ 
      Delay (5);   
    }
  }
  
  /* Wait for User button is released */ 
  while (STM_EVAL_PBGetState(BUTTON_USER) != Bit_RESET)
  {} 
  
  /* Turn Off Leds */   
  STM_EVAL_LEDOff(LED3);
  STM_EVAL_LEDOff(LED4);
  STM_EVAL_LEDOff(LED5);
  STM_EVAL_LEDOff(LED6);
  
}

/**
* @brief  USB already configured, connect USB cable to the Host (PC)
*         Green LED is On and USB is detected and recognized as a standard mouse
* @param  None 
* @retval None
*/
void USB_Test(void)
{
  
  while ((STM_EVAL_PBGetState(BUTTON_USER) != Bit_SET))
  {
    STM_EVAL_LEDOn(LED5);
    
  }
  
  /* Wait for User button is released */ 
  while (STM_EVAL_PBGetState(BUTTON_USER) != Bit_RESET)
  {} 
  /* Turn Off Leds */   
  STM_EVAL_LEDOff(LED3);
  STM_EVAL_LEDOff(LED4);
  STM_EVAL_LEDOff(LED5);
  STM_EVAL_LEDOff(LED6);
  
}

/**
* @brief  USB device HID GetPosition 
* @param  None
* @retval Pointer to report
*/
static uint8_t *USBD_HID_GetPos (void)
{   
  static uint8_t HID_Buffer [4];  
  static float Buffer[6] = {0};
  
  /* Read Gyro Angular data */
  Demo_GyroReadAngRate(Buffer); 
  
  HID_Buffer[0] = 0;
  HID_Buffer[1] = -(int8_t)(Buffer[2])/6;
  HID_Buffer[2] = (int8_t)(Buffer[1])/6;
  HID_Buffer[3] = 0;
  
  STM_EVAL_LEDToggle(LED3);
  STM_EVAL_LEDToggle(LED6);
  
  return HID_Buffer;
}

/**
* @brief  configure linear touch sensor (LTS),
*         Leds On corresponding to the current LTS TouchKey pointed 
* @param  None 
* @retval None
*/
void LTS_Test(void)
{
  
  while ((STM_EVAL_PBGetState(BUTTON_USER) != Bit_SET))
  {
    /* Execute STMTouch Driver state machine */
    if (TSL_user_Action() == TSL_STATUS_OK)
    {       
      ProcessSensors(); // Execute sensors related tasks
    }
  }
  /* Wait for User button is released */ 
  while (STM_EVAL_PBGetState(BUTTON_USER) != Bit_RESET)
  {} 
    /* Turn Off Leds */   
  STM_EVAL_LEDOff(LED3);
  STM_EVAL_LEDOff(LED4);
  STM_EVAL_LEDOff(LED5);
  STM_EVAL_LEDOff(LED6);
  
  /* SysTick time base  was  modified during TLS Test, for this we reconfigure  
     the SysTick to have a time base of 1ms */
  if (SysTick_Config(SystemCoreClock / 1000))
  { 
    /* Capture error */ 
    while (1);
  }
  
}



/**
  * @brief  Manage the activity on sensors when touched/released (example)
  * @param  None
  * @retval None
  */
void ProcessSensors(void)
{
  STM_EVAL_LEDOff(LED3);
  STM_EVAL_LEDOff(LED4);
  STM_EVAL_LEDOff(LED5);
  STM_EVAL_LEDOff(LED6);
  
  if ((MyLinRots[0].p_Data->StateId == TSL_STATEID_DETECT) ||
      (MyLinRots[0].p_Data->StateId == TSL_STATEID_DEB_RELEASE_DETECT))
  {
    if (MyLinRots[0].p_Data->Position > 0)
    {
      STM_EVAL_LEDOn(LED6);
    }
    
    if (MyLinRots[0].p_Data->Position >= 48)
    {
      STM_EVAL_LEDOn(LED5);
    }
    
    if (MyLinRots[0].p_Data->Position >= 80)
    {
      STM_EVAL_LEDOn(LED3);
    }
    
    if (MyLinRots[0].p_Data->Position >= 112)
    {
      STM_EVAL_LEDOn(LED4);
    }
  }
  
}

/**
  * @brief  Executed when a sensor is in Off state
  * @param  None
  * @retval None
  */
void MyLinRots_OffStateProcess(void)
{
  /* Add here your own processing when a sensor is in Off state */
}

/**
  * @brief  Executed at each timer interruption (option must be enabled)
  * @param  None
  * @retval None
  */
void TSL_CallBack_TimerTick(void)
{
}

/**
  * @brief  Executed when a sensor is in Error state
  * @param  None
  * @retval None
  */
void MyLinRots_ErrorStateProcess(void)
{
  /* Add here your own processing when a sensor is in Error state */
  TSL_linrot_SetStateOff();
  STM_EVAL_LEDOn(LED3);
  STM_EVAL_LEDOff(LED4);
  STM_EVAL_LEDOff(LED5);
  STM_EVAL_LEDOff(LED6);
  while(1)
  {
    STM_EVAL_LEDToggle(LED3);
    STM_EVAL_LEDToggle(LED6);
    /* Insert 1s delay */   
    Delay(100);
  }
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


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
