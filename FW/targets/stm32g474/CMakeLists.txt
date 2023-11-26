include(${PROJECT_SOURCE_DIR}/cmake/common.cmake)
include(${PROJECT_SOURCE_DIR}/cmake/mcu.cmake)

# FreeRTOS build
list(APPEND FREERTOS_SOURCES ${FREERTOS_DIR}/portable/GCC/ARM_CM4F/port.c)
list(APPEND FREERTOS_SOURCES ${FREERTOS_DIR}/portable/MemMang/heap_4.c)

add_library(freertos_mcu STATIC ${FREERTOS_SOURCES})

target_include_directories(freertos_mcu PUBLIC
    ${FREERTOS_DIR}/include
    ${FREERTOS_PORT_DIR}/GCC/ARM_CM4F
    ${CMAKE_CURRENT_SOURCE_DIR}/Core/Inc
)

target_compile_definitions(freertos_mcu PRIVATE
    projCOVERAGE_TEST=0
)

target_compile_options(freertos_mcu PRIVATE
    -ggdb3
    -O0
    ${ARM_NONE_EABI_FLAGS}
)

# Add sources
file(GLOB_RECURSE HAL_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/*.c
    ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/*.s
)

list(FILTER HAL_SOURCES EXCLUDE REGEX "FreeRTOS\/.+\.c$")
list(APPEND HAL_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2/cmsis_os2.c)
list(REMOVE_ITEM HAL_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/Core/Src/app_freertos.c)

file(GLOB_RECURSE APP_SOURCES
    ${APP_DIR}/*.c
    ${APP_DIR}/*.cpp
)

# Build lib
add_executable(${STM32G474_TARGET} ${HAL_SOURCES} ${APP_SOURCES} ${RTT_SOURCES})

# Include paths
target_include_directories(${STM32G474_TARGET} PRIVATE ${HAL_INCLUDE_DIRS} ${APP_DIRS} ${RTT_INCLUDE_DIRS})

# Project symbols
target_compile_definitions(${STM32G474_TARGET} PRIVATE ${symbols_SYMB})

# Compiler options
target_compile_options(${STM32G474_TARGET} PRIVATE ${ARM_NONE_EABI_FLAGS})

# Linker options
target_link_options(${STM32G474_TARGET} PRIVATE ${STM32G474_LINKER_OPTION})

# Link libraries
target_link_libraries(${STM32G474_TARGET}
    PRIVATE
    freertos_mcu
    ${CMAKE_CURRENT_SOURCE_DIR}/Middlewares/ST/STM32_USBPD_Library/Core/lib/USBPDCORE_PD3_CONFIG_MINSNK_CM4_wc32.a
)

# # Convert output to hex and binary
add_custom_command(TARGET ${STM32G474_TARGET}
    POST_BUILD
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    COMMAND ${CMAKE_OBJCOPY} ARGS -O ihex -I elf32-littlearm ${STM32G474_TARGET} ${STM32G474_TARGET}.hex
    COMMAND ${CMAKE_OBJCOPY} ARGS -O binary -I elf32-littlearm ${STM32G474_TARGET} ${STM32G474_TARGET}.bin
)