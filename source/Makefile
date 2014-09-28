# Put your stlink folder here so make burn will work.
# STLINK=~/stlink.git

# Put your source files here (or *.c, etc)
SRCS = main.c system_stm32f0xx.c stm32f072b_discovery.c stm32f072b_it.c
SRCS += usb_bsp.c usbd_custom_hid_core.c usbd_desc.c usbd_pwr.c usbd_usr.c
SRCS += stm32f0xx_gpio.c stm32f0xx_rcc.c stm32f0xx_exti.c stm32f0xx_syscfg.c stm32f0xx_usart.c stm32f0xx_rtc.c stm32f0xx_misc.c stm32f0xx_adc.c stm32f0xx_dma.c stm32f0xx_tim.c stm32f0xx_crs.c
SRCS += usb_dcd_int.c usb_dcd.c usbd_ioreq.c usbd_req.c usb_core.c usbd_core.c

# Binaries will be generated with this name (.elf, .bin, .hex, etc)
PROJ_NAME=controller

# Put your STM32F4 library code directory here
STM_COMMON=../STM32F072B-Discovery_FW_V1.0.1
COMMON_SRC=.

# Normally you shouldn't need to change anything below this line!
#######################################################################################

CC=arm-none-eabi-gcc
OBJCOPY=arm-none-eabi-objcopy
SIZE=arm-none-eabi-size

CFLAGS  = -g -O0 -Wall -T$(COMMON_SRC)/STM32F072RB_FLASH.ld
CFLAGS += -mlittle-endian -mthumb -mcpu=cortex-m0 -mthumb-interwork
CFLAGS += -march=armv6-m
CLFAGS += -Wl,-gc-sections
CFLAGS += -I.

CFLAGS += -fno-strict-aliasing
CFLAGS += -DUSE_STDPERIPH_DRIVER
CFLAGS += -DSTM32F072xB
CFLAGS += -DINTERNAL_PULLUP

# CFLAGS += -L/usr/arm-none-eabi/lib/thumb/cortex-m4/float-abi-hard/fpuv4-sp-d16
CFLAGS += --specs=nosys.specs
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Darwin)
	LIBS += /usr/local/Cellar/arm-none-eabi-gcc/20140609/arm-none-eabi/lib/armv6-m/libm.a /usr/local/Cellar/arm-none-eabi-gcc/20140609/arm-none-eabi/lib/armv6-m/libc.a
else
	# LIBS += /usr/arm-none-eabi/lib/thumb/cortex-m4/float-abi-hard/fpuv4-sp-d16/libc.a /usr/arm-none-eabi/lib/thumb/cortex-m4/float-abi-hard/fpuv4-sp-d16/libm.a
	LIBS += /usr/arm-none-eabi/lib/thumb/cortex-m0/libm.a /usr/arm-none-eabi/lib/thumb/cortex-m0/libc.a
endif


vpath %.c \
			$(STM_COMMON)/Libraries/STM32F0xx_StdPeriph_Driver/src \
			$(STM_COMMON)/Libraries/CMSIS/Device/Source/Templates \
			$(STM_COMMON)/Utilities/STM32F072B-Discovery \
			$(STM_COMMON)/libraries/STM32_USB_Device_Library/Core/src \
			$(STM_COMMON)/libraries/STM32_USB_Device_Driver/src \
			$(COMMON_SRC)	

# Include files from STM libraries
CFLAGS += -I$(STM_COMMON)/Utilities/STM32F072B-Discovery
CFLAGS += -I$(STM_COMMON)/Libraries/CMSIS/Include -I$(STM_COMMON)/Libraries/CMSIS/Device/Include
CFLAGS += -I$(STM_COMMON)/Libraries/STM32F0xx_StdPeriph_Driver/inc
CFLAGS += -I$(STM_COMMON)/Libraries/STM32_USB_Device_Library/Core/inc
CFLAGS += -I$(STM_COMMON)/Libraries/STM32_USB_Device_Driver/inc
CFLAGS += -I$(STM_COMMON)/Libraries/STM32_USB_Device_Library/Class/hid/inc
CFLAGS += -I$(COMMON_SRC)

# add startup file to build
SRCS += $(STM_COMMON)/Libraries/CMSIS/Device/Source/Templates/TrueSTUDIO/startup_stm32f072.s

OBJS = $(SRCS:.c=.o)


.PHONY: proj

all: proj
	$(SIZE) $(PROJ_NAME).elf


program: CFLAGS += -DPROGRAM
program: all

proj: $(PROJ_NAME).elf

$(PROJ_NAME).elf: $(OBJS)
	$(CC) $(CFLAGS) $(USER_DEFINES) $^ -o $@ $(LIBPATHS) $(LIBS)
	$(OBJCOPY) -O ihex $(PROJ_NAME).elf $(PROJ_NAME).hex
	$(OBJCOPY) -O binary $(PROJ_NAME).elf $(PROJ_NAME).bin

clean:
	find . -name \*.o -type f -delete
	find . -name \*.lst -type f -delete
	rm -f $(PROJ_NAME).elf
	rm -f $(PROJ_NAME).bin
	rm -f $(PROJ_NAME).hex

# Flash the STM32F4
burn: proj
	st-flash write $(PROJ_NAME).bin 0x8000000
