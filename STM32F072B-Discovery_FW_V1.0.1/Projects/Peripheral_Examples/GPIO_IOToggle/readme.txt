/**
  @page GPIO_IOToggle GPIO IO Toggle example
  
  @verbatim
  ******************** (C) COPYRIGHT 2014 STMicroelectronics *******************
  * @file    GPIO_IOToggle/readme.txt 
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    17-January-2014
  * @brief   Description of the GPIO IO Toggle example.
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

@par GPIO_IOToggle Description 

  GPIO ports are connected on AHB bus, using BSRR and BRR registers, two cycles 
  are required to set a pin and two cycles to reset it. So GPIO pins can toggle 
  at AHB clock divided by 4.

  This example describes how to use BSRR and BRR (Port Bit Set/Reset Register
  High and Low) for maximum IO toggling.

  PC6, PC7, PC8 and PC9 (configured in output pushpull mode) toggles in a forever loop:
  - Set PC6, PC7, PC8 and PC9 by setting corresponding bits in BSRR register
  - Reset PC6, PC7, PC8 and PC9 by setting corresponding bits in BRR register

  In this example, HCLK is configured at 48 MHz so PC6, PC7, PC8 and PC9 toggle 
  at 12MHz.
  To achieve the maximum IO toggling frequency, you have to configure your compiler
  options for high speed optimization.

@par Directory contents 

  - GPIO_IOToggle/stm32f0xx_conf.h    Library Configuration file
  - GPIO_IOToggle/stm32f0xx_it.c       Interrupt handlers
  - GPIO_IOToggle/stm32f0xx_it.h      Interrupt handlers header file
  - GPIO_IOToggle/main.h              Header for main.c module  
  - GPIO_IOToggle/main.c              Main program
  - GPIO_IOToggle/system_stm32f0xx.c  STM32F0xx system source file
   
@par Hardware and Software environment

  - This example runs on STM32F072xx Devices.
  
  - This example has been tested with STMicroelectronics STM32F072B-DISCO RevB 
    board and can be easily tailored to any other supported device 
    and development board.

  - STM32F072B-DISCO Set-up
    - LED3, LED4, LED5 and LED6 are used in this example.

@par How to use it ? 

In order to make the program work, you must do the following :

 + EWARM
    - Open the GPIO_IOToggle.eww workspace 
    - Rebuild all files: Project->Rebuild all
    - Load project image: Project->Debug
    - Run program: Debug->Go(F5)
 
 + MDK-ARM
    - Open the GPIO_IOToggle.uvproj project.
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
