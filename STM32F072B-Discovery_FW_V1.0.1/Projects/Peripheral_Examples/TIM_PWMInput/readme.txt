/**
  @page TIM_PWMInput TIM PWM Input example
  
  @verbatim
  ******************** (C) COPYRIGHT 2014 STMicroelectronics *******************
  * @file    TIM_PWMInput/readme.txt 
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    17-January-2014
  * @brief   Description of the TIM PWM Input example.
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

@par TIM_PWMInput Description 

This example shows how to use the TIM peripheral to measure the frequency and 
duty cycle of an external signal.

The TIMxCLK frequency is set to SystemCoreClock (Hz), the Prescaler is 0 so the 
counter clock is SystemCoreClock (Hz).
SystemCoreClock is set to 48 MHz.

TIM2 is configured in PWM Input Mode: the external signal is connected to 
TIM2 Channel2 used as input pin.
To measure the frequency and the duty cycle we use the TIM2 CC2 interrupt request,
so In the TIM2_IRQHandler routine, the frequency and the duty cycle of the external 
signal are computed. 
The "Frequency" variable contains the external signal frequency:
External Signal Frequency = SystemCoreClock / TIM2_CCR2 in Hz, 
The "DutyCycle" variable contains the external signal duty cycle:
External Signal DutyCycle = (TIM2_CCR1*100)/(TIM2_CCR2) in %.

The minimum frequency value to measure is 732 Hz (SystemCoreClock / CCR MAX).

@par Note: 
  SystemCoreClock variable holds HCLK frequency and is defined in system_stm32f0xx.c file.
  Each time the core clock (HCLK) changes, user had to call SystemCoreClockUpdate()
  function to update SystemCoreClock variable value. Otherwise, any configuration
  based on this variable will be incorrect.
  

 

@par Directory contents 

  - TIM_PWMInput/stm32f0xx_conf.h    Library Configuration file
  - TIM_PWMInput/stm32f0xx_it.c      Interrupt handlers
  - TIM_PWMInput/stm32f0xx_it.h      Interrupt handlers header file
  - TIM_PWMInput/main.h              Header for main.c module  
  - TIM_PWMInput/main.c              Main program
  - TIM_PWMInput/system_stm32f0xx.c  STM32F0xx system source file
   
@par Hardware and Software environment

  - This example runs on STM32F072xx Devices.
  
  - This example has been tested with STMicroelectronics STM32F072B-DISCO RevB
    board and can be easily tailored to any other supported device 
    and development board.
  - STM32F072B-DISCO Set-up
      - Connect the external signal to the TIM2 CH2 pin (PB.03) to measure the 
        frequency.
      
@par How to use it ? 

In order to make the program work, you must do the following :

 + EWARM
    - Open the TIM_PWMInput.eww workspace 
    - Rebuild all files: Project->Rebuild all
    - Load project image: Project->Debug
    - Run program: Debug->Go(F5)

 + MDK-ARM
    - Open the TIM_PWMInput.uvproj project.
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
