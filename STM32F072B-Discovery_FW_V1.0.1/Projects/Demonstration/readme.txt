/**
  @page STM32F072B-DISCOVERY_Demonstration   STM32F072B-DISCOVERY demonstration firmware
  
  @verbatim
  ******************** (C) COPYRIGHT 2014 STMicroelectronics *******************
  * @file    readme.txt 
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    17-January-2014
  * @brief   Description of the STM32F072B-DISCOVERY demonstration firmware
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

@par Demo Description 
 
The provided demonstration firmware help you to manage MEMS, Linear touch sensor
and USB device integrated on STM32F072B-DISCO board.
 
Follow the sequence below to configure the STM32F072B-DISCO board and launch the
demo application:
  - Ensure that the jumpers JP2 and CN5 are set to “on” (Discovery mode)
  - Connect the STM32F072B-DISCO board to a PC with a USB cable type'A to mini-B'
    through the USB connector CN1 to power the board. Red LED LD2 (PWR), 
    LD1 (COM) then lights up and four LEDs LD3, LD4, LD5, LD6 are blinking.
  - Pressing the user button B1, enables the MEMS sensor. The four LEDs LD3, LD4,
    LD5, LD6 will indicate the board motion direction
    Right : LED5 is ON.
    Left  : LED4 is ON.
    UP    : LED3 is ON.
    DOWN  : LED6 is ON.
 - Pressing the user button B1, enables the USB USER CN2 and convert the
   STM32F072B-DISCO board as a standard mouse (LD3, LD6 are blinking).
   connect a second USB type A/mini-B cable through CN2 and the PC, then move
   the board (horizontally and vertically)and see the mouse cursor moves according to the motion direction.
 - Pressing the user button B1, enables the Linear touch sensor LS1, then four
   LEDs LD3, LD4, LD5, LD6 will be On or Off according to finger’s position on
   the Linear Sensor.
 - Pressing the user button B1, to re launch the demo application.   

@par Directory contents 

  - stm32f0xx_conf.h    Library Configuration file
  - stm32f0xx_it.c      Interrupt handlers
  - stm32f0xx_it.h      Interrupt handlers header file
  - main.c              Main program
  - system_stm32f0xx.c  STM32F0xx system source file


@par Hardware and Software environment

  - This example runs on STM32F072xx Devices.
    
  - This example has been tested with STMicroelectronics STM32F072B-DISCO board RevB
    can be easily tailored to any other supported device and development board.      

@par How to use it ? 

In order to make the program work, you must do the following :

 + EWARM
    - Open the STM32F072B-Discovery_Demo.eww workspace 
    - Rebuild all files: Project->Rebuild all
    - Load project image: Project->Debug
    - Run program: Debug->Go(F5)

 + MDK-ARM
    - Open the STM32F072B-Discovery_Demo.uvproj project.
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
