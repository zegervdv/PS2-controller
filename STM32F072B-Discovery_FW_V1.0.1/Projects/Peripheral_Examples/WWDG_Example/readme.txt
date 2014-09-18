/**
  @page WWDG_Example WWDG example
  
  @verbatim
  ******************** (C) COPYRIGHT 2014 STMicroelectronics *******************
  * @file    WWDG_Example/readme.txt 
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    17-January-2014
  * @brief   Description of the WWDG example.
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
  ******************************************************************************
  @endverbatim

@par WWDG_Example Description 

This example shows how to update at regular period the WWDG counter and how to
simulate a software fault generating an MCU WWDG reset on expiry of a programmed 
time period.

The WWDG timeout is set to 43.7 ms and the refresh window is set to 80. 
The WWDG counter is refreshed each 33 ms in the main program infinite loop to 
prevent a WWDG reset.
LED4 is also toggled each 33 ms indicating that the program is running.

An EXTI Line is connected to a GPIO pin, and configured to generate an interrupt
on the rising edge of the signal.  

The EXTI Line is used to simulate a software failure: once the EXTI Line event 
occurs, by pressing the Key User button, the corresponding interrupt is served.
In the ISR, a write to invalid address generates a Hardfault exception containing
an infinite loop and preventing to return to main program (the WWDG counter is 
not refreshed).
As a result, when the WWDG counter falls to 63, the WWDG reset occurs.
If the WWDG reset is generated, after the system resumes from reset, LED3 turns on.

If the EXTI Line event does not occur, the WWDG counter is indefinitely refreshed
in the main program infinite loop, and there is no WWDG reset.

@par Note This example can be used in RUN mode or DEBUG mode.

@par Directory contents 

  - WWDG_Example/stm32f0xx_conf.h    Library Configuration file
  - WWDG_Example/stm32f0xx_it.c      Interrupt handlers
  - WWDG_Example/stm32f0xx_it.h      Interrupt handlers header file
  - WWDG_Example/main.h              Header for main.c module  
  - WWDG_Example/main.c              Main program
  - WWDG_Example/system_stm32f0xx.c  STM32F0xx system source file
   
@par Hardware and Software environment

  - This example runs on STM32F072xx Devices.
  
  - This example has been tested with STMicroelectronics STM32F072B-DISCO Rev B 
    board and can be easily tailored to any other supported device 
    and development board.

  - STM32F072B-DISCO Set-up
    - LED3 and LED4 are used in this example.

@par How to use it ? 

In order to make the program work, you must do the following :

 + EWARM
    - Open the WWDG_Example.eww workspace 
    - Rebuild all files: Project->Rebuild all
    - Load project image: Project->Debug
    - Run program: Debug->Go(F5)
 
 + MDK-ARM
    - Open the WWDG_Example.uvproj project.
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
