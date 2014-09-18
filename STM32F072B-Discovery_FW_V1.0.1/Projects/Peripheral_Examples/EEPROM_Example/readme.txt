/**
  @page EEPROM_Example EEPROM Example
  
  @verbatim
  ******************** (C) COPYRIGHT 2014 STMicroelectronics *******************
  * @file    EEPROM_Example/readme.txt 
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    17-January-2014
  * @brief   Description of the EEPROM example.
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

@par EEPROM_Example Description 

This example describes how to use the I2C to communicate with EEPROM memory.
Before starting test, a check is done to verify existence of EEPROM device. If
an EEPROM is connected, the test will be done otherwise LED3 turns ON indicating 
the absence of the EEPROM.
After I2C and IOs configuration, a first write operation is done. Then a read 
operation is made and the written and read values are compared. If the result of 
comparison is OK, LED5 turns on. Otherwise LED3 turns ON.
Once this test finish, a second write operation is done. Then a read 
operation is made and the written and read values are compared. If the result of 
comparison is OK, LED6 turns on. Otherwise LED3 turns ON.

@par Directory contents 

  - EEPROM_Example/stm32f0xx_conf.h    Library Configuration file
  - EEPROM_Example/stm32f0xx_it.c      Interrupt handlers
  - EEPROM_Example/stm32f0xx_it.h      Interrupt handlers header file
  - EEPROM_Example/main.c              Main program
  - EEPROM_Example/main.h              Main program header file
  - EEPROM_Example/system_stm32f0xx.c  STM32F0xx system source file
  
         
@par Hardware and Software environment

  - This example runs on STM32F072xx Devices.
  
  - This example has been tested with STMicroelectronics STM32F072B-DISCO RevB
    board and can be easily tailored to any other supported device 
    and development board.
    
  - Plug RF EEPROM daughter board ANT7-M24LR-A into connector CN3 of STM32F072B-DISCO board.  


@par How to use it ? 

In order to make the program work, you must do the following :

 + EWARM
    - Open the EEPROM_Example.eww workspace 
    - Rebuild all files: Project->Rebuild all
    - Load project image: Project->Debug
    - Run program: Debug->Go(F5)
 
 + MDK-ARM
    - Open the EEPROM_Example.uvproj project.
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
