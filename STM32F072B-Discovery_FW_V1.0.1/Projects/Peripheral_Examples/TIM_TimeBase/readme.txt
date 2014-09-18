/**
  @page TIM_TimeBase Time Base generation example
  
  @verbatim
  ******************** (C) COPYRIGHT 2014 STMicroelectronics *******************
  * @file    TIM_TimeBase/readme.txt 
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    17-January-2014
  * @brief   Description of the Time Base generation example.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2014 STMicroelectronics</center></h2>
  *
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
  @endverbatim

@par TIM_TimeBase Description 

This example shows how to configure the TIM peripheral in Upcounting mode  
with the corresponding Interrupt request in order to generate time base.
    
The TIM7CLK frequency is set to  APB1 clock (PCLK1), since APB1 prescaler is set 
to 1 and TIM7 prescaler is set to 0. TIM7CLK = PCLK1 = HCLK = SystemCoreClock.
To get TIM7 counter updated at 4 Hz, the Prescaler and Period are computed as following:
     TIM7 counter clock = TIM7CLK /((Prescaler + 1)*(Period + 1))
                        = 48 MHz / ((25000)*(480))
                        = 4 Hz 
                        
SystemCoreClock is set to 48MHz.

The timer generates an interrupt each  250ms and 4 leds (LED3, LED4, 
LED5 and LED6) are toggled with frequency equal to 2Hz: 

@par Directory contents 

  - TIM_TimeBase/stm32f0xx_conf.h    Library Configuration file
  - TIM_TimeBase/stm32f0xx_it.c      Interrupt handlers
  - TIM_TimeBase/stm32f0xx_it.h      Interrupt handlers header file
  - TIM_TimeBase/main.h              Header for main.c module  
  - TIM_TimeBase/main.c              Main program
  - TIM_TimeBase/system_stm32f0xx.c  STM32F0xx system source file

   
@par Hardware and Software environment

  - This example runs on STM32F072xx Devices.
  
  - This example has been tested with STMicroelectronics STM32F072B-DISCO 
    (STM32F0xx) board and can be easily tailored to any other supported device 
    and development board.

  - STM32F072B-DISCO Set-up
    - LED3, LED4, LED5 and LED6 are used in this example.

@par How to use it ? 

In order to make the program work, you must do the following :

 + EWARM
    - Open the TIM_TimeBase.eww workspace 
    - Rebuild all files: Project->Rebuild all
    - Load project image: Project->Debug
    - Run program: Debug->Go(F5)
 + MDK-ARM
    - Open the TIM_TimeBase.uvproj project.
    - Rebuild all files: Project->Rebuild all target files.
    - Load project image: Debug->Start/Stop Debug Session.
    - Run program: Debug->Run (F5).

 + TrueSTUDO
    - Open the TrueSTUDIO toolchain.
    - Click on File->Switch Workspace->Other and browse to TrueSTUDIO workspace
      directory.
    - Click on File->Import, select General->'Existing Projects into Workspace'
      and then click "Next".
    - Browse to the TrueSTUDIO workspace directory, select the project.
    - Rebuild all project files: Select the project in the "Project explorer" 
      window then click on Project->build project menu.
    - Run program: Run->Debug (F11).
       
 * <h3><center>&copy; COPYRIGHT STMicroelectronics</center></h3>
 */
