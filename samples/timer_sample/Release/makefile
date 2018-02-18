################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
LSS += \
timer_sample.lss \

FLASH_IMAGE += \
timer_sample.hex \

EEPROM_IMAGE += \
timer_sample.eep \

SIZEDUMMY += \
sizedummy \


# All Target
all: timer_sample.elf secondary-outputs

# Tool invocations
timer_sample.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,timer_sample.map -mmcu=atmega644 -o "timer_sample.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

timer_sample.lss: timer_sample.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S timer_sample.elf  >"timer_sample.lss"
	@echo 'Finished building: $@'
	@echo ' '

timer_sample.hex: timer_sample.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex timer_sample.elf  "timer_sample.hex"
	@echo 'Finished building: $@'
	@echo ' '

timer_sample.eep: timer_sample.elf
	@echo 'Create eeprom image (ihex format)'
	-avr-objcopy -j .eeprom --no-change-warnings --change-section-lma .eeprom=0 -O ihex timer_sample.elf  "timer_sample.eep"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: timer_sample.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega644 timer_sample.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(FLASH_IMAGE)$(ELFS)$(OBJS)$(ASM_DEPS)$(EEPROM_IMAGE)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) timer_sample.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(EEPROM_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
