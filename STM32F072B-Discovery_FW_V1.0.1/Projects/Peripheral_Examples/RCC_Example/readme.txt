/**
  @page RCC_Example RCC example
  
  @verbatim
  ******************** (C) COPYRIGHT 2014 STMicroelectronics *******************
  * @file    RCC_Example/readme.txt 
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    17-January-2014
  * @brief   Description of the RCC example.
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

@par RCC_Example Description 

  This example shows how to use, for debug purpose, the RCC firmware to retrieve 
  the current status and frequencies of different on chip clocks. 
  You can see the "RCC_ClockFreq" structure content, which hold the frequencies of 
  different on chip clocks, using your toolchain debugger.

  This example handles also the High Speed External clock (HSE) failure detection:
  when the HSE clock disappears (broken or disconnected external Quartz); HSE, PLL
  are disabled (but no change on PLL config), HSI selected as system clock source
  and an interrupt (NMI) is generated. In the NMI ISR, the HSE, HSE ready interrupts
  are enabled, and once HSE clock recovers, the HSERDY interrupt is generated and in
  the RCC ISR routine the system clock is reconfigured to its previous state (before
  HSE clock failure). You can monitor the system clock on MCO pin(PA8).

  LED3 and LED4 are toggled with a timing defined by the Delay function.

@note - in this example we need HSE quartz (8MHz) in the board. 
      - On the STM32F072B-DISCO boards, to genertate the HSE failure you can 
      remove the HSE quartz from the socket.
      
      
@par Directory contents 

  - RCC_Example/stm32f0xx_conf.h    Library Configuration file
  - RCC_Example/stm32f0xx_it.c      Interrupt handlers
  - RCC_Example/stm32f0xx_it.h      Interrupt handlers header file
  - RCC_Example/main.h              Header for main.c module  
  - RCC_Example/main.c              Main program
  - RCC_Example/system_stm32f0xx.c  STM32F0xx system source file


@par Hardware and Software environment

  - This example runs on STM32F072xx Devices.
  
  - This example has been tested with STMicroelectronics STM32F072B-DISCO RevB 
    board and can be easily tailored to any other supported device 
    and development board.

  - STM32F072B-DISCO Set-up
    - LED3 and LED4 are used in this example.

@par How to use it ? 

In order to make the program work, you must do the following :

 + EWARM
    - Open the RCC_Example.eww workspace 
    - Rebuild all files: Project->Rebuild all
    - Load project image: Project->Debug
    - Run program: Debug->Go(F5)
    
 + MDK-ARM
    - Open the RCC_Example.uvproj project.
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
