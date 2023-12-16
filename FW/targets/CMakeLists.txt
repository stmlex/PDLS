# region ThreadX
FetchContent_Declare(
  threadx
  GIT_REPOSITORY https://github.com/azure-rtos/threadx.git
  GIT_TAG        v6.3.0_rel
)
FetchContent_Populate(threadx)
set(RTOS_DIR ${threadx_SOURCE_DIR})
file(GLOB RTOS_SOURCES ${threadx_SOURCE_DIR}/common/src/*.c)
# endregion

#region GUIX
FetchContent_Declare(
  guix
  GIT_REPOSITORY https://github.com/azure-rtos/guix.git
  GIT_TAG        v6.3.0_rel
)
FetchContent_Populate(guix)
set(GUIX_DIR ${guix_SOURCE_DIR})
file(GLOB GUIX_SOURCES ${guix_SOURCE_DIR}/common/src/*.c)
# endregion

add_subdirectory(stm32g474)
add_subdirectory(desktop)
