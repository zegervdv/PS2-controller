/**
  @page DMA_FlashToRamTransfer DMA FLASH to RAM example
  
  @verbatim
  ******************** (C) COPYRIGHT 2014 STMicroelectronics *******************
  * @file    DMA_FlashToRamTransfer/readme.txt 
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    17-January-2014
  * @brief   Description of the DMA FLASH to RAM example.
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

@par DMA_FlashToRamTransfer Description 

This example provides a description of how to use a DMA channel to transfer 
a word data buffer from FLASH memory to embedded SRAM memory.

DMA1 Channel1 is configured to transfer the contents of a 32-word data buffer
stored in Flash memory to the reception buffer declared in RAM.

The start of transfer is triggered by software. DMA1 Channel1 memory-to-memory
transfer is enabled. Source and destination addresses incrementing is also enabled.
The transfer is started by setting the Channel enable bit for DMA1 Channel1.
At the end of the transfer, a Transfer Complete interrupt is generated since it
is enabled. Once interrupt is generated, the remaining data to be transferred is
read which must be equal to 0. The Transfer Complete Interrupt pending bit is
then cleared. A comparison between the source and destination buffers is done to
check that all data have been correctly transferred.

If the result of the check is ok LED5 turns on, otherwise LED3 turns on.


@par Directory contents 

  - DMA_FlashToRamTransfer/stm32f0xx_conf.h    Library Configuration file
  - DMA_FlashToRamTransfer/stm32f0xx_it.c      Interrupt handlers
  - DMA_FlashToRamTransfer/stm32f0xx_it.h      Interrupt handlers header file
  - DMA_FlashToRamTransfer/main.h              Header for main.c module  
  - DMA_FlashToRamTransfer/main.c              Main program
  - DMA_FlashToRamTransfer/system_stm32f0xx.c  STM32F0xx system source file
   
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
    - Open the DMA_FlashToRamTransfer.eww workspace 
    - Rebuild all files: Project->Rebuild all
    - Load project image: Project->Debug
    - Run program: Debug->Go(F5)

 + MDK-ARM
    - Open the DMA_FlashToRamTransfer.uvproj project.
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
