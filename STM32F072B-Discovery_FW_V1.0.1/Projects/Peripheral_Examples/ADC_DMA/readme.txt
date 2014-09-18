/**
  @page ADC_DMA ADC1 conversion using DMA for Data transfer
  
  @verbatim
  ******************** (C) COPYRIGHT 2014 STMicroelectronics *******************
  * @file    ADC_DMA/readme.txt 
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    17-January-2014
  * @brief   Description of the ADC_DMA example.
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

@par ADC_DMA Description 

This example describes how to use the ADC1 and DMA to transfer continuously 
converted data from ADC1 to memory.
The ADC1 is configured to convert continuously channel12.
Each time an end of conversion occurs the DMA transfers, in circular mode, the
converted data from ADC1 DR register to the uhADC1ConvertedValue variable.

The converted value can be monitored by adding the variable "uhADC1ConvertedValue" 
to the debugger watch window. 

@par Directory contents 

  - ADC_DMA/stm32f0xx_conf.h    Library Configuration file
  - ADC_DMA/stm32f0xx_it.c      Interrupt handlers
  - ADC_DMA/stm32f0xx_it.h      Interrupt handlers header file
  - ADC_DMA/main.c              Main program
  - ADC_DMA/main.h              Main program header file
  - ADC_DMA/system_stm32f0xx.c  STM32F0xx system source file
         
@par Hardware and Software environment

  - This example runs on STM32F072xx Devices.
  
  - This example has been tested with STMicroelectronics STM32F072B-DISCO RevB 
    board and can be easily tailored to any other supported device 
    and development board.
    
  - STM32F072B-DISCO Set-up
    - Connect the external signal(ranges from 0 to 3.0V) to the ADC1 pin (PC.02) to be converted.

@par How to use it ? 

In order to make the program work, you must do the following :

 + EWARM
    - Open the ADC_DMA.eww workspace 
    - Rebuild all files: Project->Rebuild all
    - Load project image: Project->Debug
    - Run program: Debug->Go(F5)
  + MDK-ARM
    - Open the ADC_DMA.uvproj project.
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
