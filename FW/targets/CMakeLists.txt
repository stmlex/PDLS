# region Submodules
FetchContent_Declare(
  freertos
  GIT_REPOSITORY https://github.com/FreeRTOS/FreeRTOS-Kernel.git
  GIT_TAG        V10.6.1
)
FetchContent_Populate(freertos)

FetchContent_Declare(
    lvgl
    GIT_REPOSITORY https://github.com/lvgl/lvgl.git
    GIT_TAG        v8.3.11
)
FetchContent_Populate(lvgl)

FetchContent_Declare(
    lv_drivers
    GIT_REPOSITORY https://github.com/lvgl/lv_drivers.git
    GIT_TAG        release/v8.3
)
FetchContent_Populate(lv_drivers)
# endregion

# region FreeRTOS common
set(FREERTOS_DIR ${freertos_SOURCE_DIR})
file(GLOB FREERTOS_SOURCES ${FREERTOS_DIR}/*.c)
# endregion

# region LVGL common
set(LVGL_DIR ${lvgl_SOURCE_DIR})
set(LVGL_INCLUDE_DIR ${lvgl_SOURCE_DIR}/src)

file(GLOB_RECURSE LVGL_SOURCES ${LVGL_DIR}/src/*.c)
# endregion

# region LVGL drivers
set(LVGL_DRIVERS_DIR ${lv_drivers_SOURCE_DIR})
file(GLOB_RECURSE LVGL_DRIVERS_SOURCES ${LVGL_DRIVERS_DIR}/*.c)
# endregion

add_subdirectory(stm32g474)
add_subdirectory(desktop)
