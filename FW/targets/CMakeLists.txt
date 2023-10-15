# Submodules
FetchContent_Declare(
  freertos
  GIT_REPOSITORY https://github.com/FreeRTOS/FreeRTOS-Kernel.git
  GIT_TAG        V10.6.1
)
FetchContent_Populate(freertos)

FetchContent_Declare(
    lvgl
    GIT_REPOSITORY https://github.com/lvgl/lvgl.git
    GIT_TAG        v8.3.10
)
FetchContent_Populate(lvgl)

FetchContent_Declare(
    lv_drivers
    GIT_REPOSITORY https://github.com/lvgl/lv_drivers.git
    GIT_TAG        v6.1.1
)
FetchContent_Populate(lv_drivers)

set(FREERTOS_DIR ${freertos_SOURCE_DIR})
set(PORT_DIR ${freertos_SOURCE_DIR}/portable)

file(GLOB FREERTOS_SOURCES ${FREERTOS_DIR}/*.c)

add_subdirectory(stm32g474)
add_subdirectory(desktop)
