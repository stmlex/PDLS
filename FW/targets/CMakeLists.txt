
set(FREERTOS_PORT GCC_ARM_CM4F CACHE STRING "" FORCE)

add_library(freertos_config INTERFACE)
target_include_directories(freertos_config
  SYSTEM INTERFACE
  ${CMAKE_CURRENT_SOURCE_DIR}/stm32g474/Core/Inc) # The config file directory
target_compile_definitions(freertos_config INTERFACE projCOVERAGE_TEST=0)
target_compile_options(freertos_config INTERFACE ${ARM_NONE_EABI_FLAGS}
)

FetchContent_Declare(
  freertos
  GIT_REPOSITORY https://github.com/FreeRTOS/FreeRTOS-Kernel.git
  GIT_TAG        V10.6.1
)
FetchContent_MakeAvailable(freertos)

add_subdirectory(stm32g474)
add_subdirectory(desktop)
