/**
  @page IWDG_WinwdowMode IWDG Reset with window mode example
  
  @verbatim
  ******************** (C) COPYRIGHT 2014 STMicroelectronics *******************
  * @file    IWDG_WinwdowMode/readme.txt 
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    17-January-2014
  * @brief   Description of the IWDG Window Mode example.
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

@par IWDG_WinwdowMode Description 

This example shows how to update at regular period the IWDG reload counter and 
how to simulate a software fault generating an MCU IWDG reset on expiry of a 
programmed time period using Window mode.

The IWDG reload and window values are set respectively to 2000 and 1000.
In this case the refresh window is: 
  (2000-1000) / (LSI/16) = ~400 ms < refresh window < 2000 / (LSI/16) = ~800 ms
   
@note the refresh window may varies due to LSI frequency dispersion 

The IWDG counter is refreshed each 740 ms in the main program infinite loop to 
prevent a IWDG reset. LED5 is also toggled each 740 ms indicating that the 
program is running.

The EXTI Line is used to simulate a software failure: once the EXTI Line event 
occurs, by pressing the user push-button, the corresponding interrupt is 
served. In the ISR, a write to invalid address generates a Hardfault exception 
containing an infinite loop and preventing to return to main program (the IWDG 
reload counter is not refreshed).
As a result, when the IWDG counter reaches 00h, the IWDG reset occurs.
  
If the IWDG reset is generated, after the system resumes from reset, LED3 turns on.
If the EXTI Line event does not occur, the IWDG counter is indefinitely refreshed
in the main program infinite loop, and there is no IWDG reset.
  

@par Directory contents 

  - IWDG_WinwdowMode/stm32f0xx_conf.h    Library Configuration file
  - IWDG_WinwdowMode/stm32f0xx_it.c      Interrupt handlers
  - IWDG_WinwdowMode/stm32f0xx_it.h      Interrupt handlers header file
  - IWDG_WinwdowMode/main.h              Header for main.c module  
  - IWDG_WinwdowMode/main.c              Main program
  - IWDG_WinwdowMode/system_stm32f0xx.c  STM32F0xx system source file

   
@par Hardware and Software environment

  - This example runs on STM32F072xx Devices.
  
  - This example has been tested with STMicroelectronics STM32F072B-DISCO RevB
    board and can be easily tailored to any other supported device 
    and development board.

  - STM32F072B-DISCO Set-up
    - LED3 and LED5 are used in this example.

@par How to use it ? 

In order to make the program work, you must do the following :

 + EWARM
    - Open the IWDG_WinwdowMode.eww workspace 
    - Rebuild all files: Project->Rebuild all
    - Load project image: Project->Debug
    - Run program: Debug->Go(F5)
 
 + MDK-ARM
    - Open the IWDG_WinwdowMode.uvproj project.
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
