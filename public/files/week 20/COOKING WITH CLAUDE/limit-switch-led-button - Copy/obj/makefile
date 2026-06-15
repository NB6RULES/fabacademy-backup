################################################################################
# MRS Version: 2.4.0
# Automatically-generated file. Do not edit!
################################################################################
-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include User/subdir.mk
-include Startup/subdir.mk
-include Peripheral/src/subdir.mk
-include Debug/subdir.mk
-include Core/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
SECONDARY_FLASH += \
limit-switch-led-button.hex \

SECONDARY_LIST += \
limit-switch-led-button.lst \

SECONDARY_SIZE += \
limit-switch-led-button.siz \


# All Target
all: 
	$(MAKE) --no-print-directory main-build 

main-build: limit-switch-led-button.elf secondary-outputs

# Tool invocations
limit-switch-led-button.elf: $(OBJS) $(USER_OBJS_ESCAPE)
	@	riscv-none-embed-gcc -march=rv32ecxw -mabi=ilp32e -msmall-data-limit=0 -msave-restore -fmax-errors=20 -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized -g -T "c:\Users\nadec\mounriver-studio-projects\limit-switch-led-button\Ld\Link.ld" -nostartfiles -Xlinker --gc-sections -Wl,-Map,"limit-switch-led-button.map" --specs=nano.specs --specs=nosys.specs -o "limit-switch-led-button.elf" $(OBJS) $(LIBS) -lprintf
limit-switch-led-button.hex: limit-switch-led-button.elf
	@	riscv-none-embed-objcopy -O ihex "limit-switch-led-button.elf" "limit-switch-led-button.hex"
limit-switch-led-button.lst: limit-switch-led-button.elf
	@	riscv-none-embed-objdump --all-headers --demangle --disassemble -M xw "limit-switch-led-button.elf" > "limit-switch-led-button.lst"
limit-switch-led-button.siz: limit-switch-led-button.elf
	riscv-none-embed-size --format=berkeley "limit-switch-led-button.elf"

# Other Targets
clean:
	-$(RM) $(DIR_OBJS) $(SECONDARY_FLASH)$(SECONDARY_LIST)$(SECONDARY_SIZE) limit-switch-led-button.elf
	-$(RM) $(DIR_EXPANDS) $(CALLGRAPH_DOT)
	-$(RM) $(DIR_DEPS)
secondary-outputs: $(SECONDARY_FLASH) $(SECONDARY_LIST) $(SECONDARY_SIZE)

.PHONY: all clean dependents

-include ../makefile.targets