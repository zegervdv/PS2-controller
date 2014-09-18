/**
  @page FLASH_Program FLASH Program example
  
  @verbatim
  ******************** (C) COPYRIGHT 2014 STMicroelectronics *******************
  * @file    FLASH_Program/readme.txt 
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    17-January-2014
  * @brief   Description of the FLASH Program example.
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

@par FLASH_Program Description 

This example provides a description of how to program the STM32F0xx FLASH.

After Reset, the Flash memory Program/Erase Controller is locked. To unlock it,
the FLASH_Unlock function is used.
Before programming the desired addresses, an erase operation is performed using 
the flash erase page feature. The erase procedure starts with the calculation of
the number of pages to be used. Then all these pages will be erased one by one by
calling FLASH_ErasePage function. 

Once this operation is finished, the programming operation will be performed by 
using the FLASH_ProgramWord function. The written data is then checked and the
result of the programming operation is stored into the MemoryProgramStatus variable.
If MemoryProgramStatus is equal to PASSED LED5 turns on, otherwise LED3 turns on.


@par Directory contents 

  - FLASH_Program/stm32f0xx_conf.h    Library Configuration file
  - FLASH_Program/stm32f0xx_it.c      Interrupt handlers
  - FLASH_Program/stm32f0xx_it.h      Interrupt handlers header file
  - FLASH_Program/main.h              Header for main.c module  
  - FLASH_Program/main.c              Main program
  - FLASH_Program/system_stm32f0xx.c  STM32F0xx system source file

   
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
    - Open the FLASH_Program.eww workspace 
    - Rebuild all files: Project->Rebuild all
    - Load project image: Project->Debug
    - Run program: Debug->Go(F5)
 
 + MDK-ARM
    - Open the FLASH_Program.uvproj project.
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
