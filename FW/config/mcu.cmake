# region MCU GLOBAL PROPERTY
set(STM32G474_TARGET               ws474_fw)

# region HAL
set(HAL_INCLUDE_DIRS
    # Put here your include dirs, one in each line, relative to CMakeLists.txt file location
    ${STM32G474_TARGET_PATH}/Core/Inc
    ${STM32G474_TARGET_PATH}/Drivers/STM32G4xx_HAL_Driver/Inc
    ${STM32G474_TARGET_PATH}/Drivers/STM32G4xx_HAL_Driver/Inc/Legacy
    ${STM32G474_TARGET_PATH}/Drivers/CMSIS/Device/ST/STM32G4xx/Include
    ${STM32G474_TARGET_PATH}/Drivers/CMSIS/Include
    ${STM32G474_TARGET_PATH}/Middlewares/ST/STM32_USBPD_Library/Devices/STM32G4XX/inc
    ${STM32G474_TARGET_PATH}/Middlewares/ST/STM32_USBPD_Library/Core/inc
    ${STM32G474_TARGET_PATH}/Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc
    ${STM32G474_TARGET_PATH}/Middlewares/ST/STM32_USB_Device_Library/Core/Inc
    ${STM32G474_TARGET_PATH}/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2
    ${STM32G474_TARGET_PATH}/USB_Device/App
    ${STM32G474_TARGET_PATH}/USB_Device/Target
    ${STM32G474_TARGET_PATH}/USBPD
    ${STM32G474_TARGET_PATH}/USBPD/App
)
# endregion

# region RTT
set(RTT_LIB rtt)
set(RTT_VERSION SEGGER_RTT_V762c)
set(RTT_DIR ${LIBS_DIR}/${RTT_VERSION})
set(RTT_INCLUDE_DIRS
    ${RTT_DIR}/Config
    ${RTT_DIR}/RTT)
# Add sources
file(GLOB_RECURSE RTT_SOURCES
    ${RTT_DIR}/RTT/*.c
    ${RTT_DIR}/RTT/*.S
    ${RTT_DIR}/Syscalls/SEGGER_RTT_Syscalls_GCC.c
)
# endregion

# Put here your symbols (preprocessor defines), one in each line
# Encapsulate them with double quotes for safety purpose
set(symbols_SYMB
    $<$<CONFIG:DEBUG>:"DEBUG">
    $<$<CONFIG:RELASE>:"NDEBUG">
    "USE_HAL_DRIVER"
    "USE_FULL_LL_DRIVER"
    "STM32G474xx"
    "USBPD_PORT_COUNT=1"
    "USBPDCORE_LIB_PD3_CONFIG_MINSNK"
)

set(CPU_PARAMETERS -mthumb
    # This needs attention to properly set for used MCU
    -mcpu=cortex-m4
    -mfpu=fpv5-d16
    -mfloat-abi=hard)

set(ARM_NONE_EABI_FLAGS
    ${CPU_PARAMETERS}
    -Wall
    -Wextra
    -Wpedantic
    -Wno-unused-parameter
    -fdata-sections
    -ffunction-sections
    -fdiagnostics-color=always
    # Full debug configuration
    $<$<CONFIG:DEBUG>: -Og -g3 -ggdb>
    # Release
    $<$<CONFIG:RELEASE>:-Os -s>
    # Release with DEBUG
    $<$<CONFIG:RelWithDebInfo>:-Os -g3 -ggdb>
)

# Set linker script
set(STM32G474_LINKER_SCRIPT ${PROJECT_SOURCE_DIR}/targets/stm32g474/STM32G474RBTx_FLASH.ld)

set(STM32G474_LINKER_OPTION
    -T${STM32G474_LINKER_SCRIPT}
    ${CPU_PARAMETERS}
    -Wl,-Map=${CMAKE_PROJECT_NAME}.map
    -specs=nano.specs
    -specs=nosys.specs
    -u _printf_float                # STDIO float formatting support
    -Wl,--start-group
    -fno-exceptions
    -fno-rtti
    -Wl,--end-group
    -Wl,--print-memory-usage
)
# endregion