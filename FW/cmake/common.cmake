set(APP     app)
set(APP_FW  app_fw)
# region GLOBAL PROPERTIES
set(STM32G474_TARGET_PATH           ${PROJECT_SOURCE_DIR}/targets/stm32g474)
set(DESKTOP_TARGET_PATH             ${PROJECT_SOURCE_DIR}/targets/desktop)

set(APP_DIR     ${PROJECT_SOURCE_DIR}/app)
set(GUIX_RES    ${APP_DIR}/guix)
set(DEBUG_DIR   ${APP_DIR}/debug)
set(UTILS_DIR   ${APP_DIR}/utils)
set(IO_DIR      ${APP_DIR}/io)
set(LIBS_DIR    ${PROJECT_SOURCE_DIR}/libs)

set(APP_DIRS
    ${APP_DIR}
    ${GUIX_RES}
    ${DEBUG_DIR}
    ${UTILS_DIR}
    ${IO_DIR}
)

set(COMMON_TYPES_TARGET common_types_test)
set(TEST_DIR            ${PROJECT_SOURCE_DIR}/test)

set(GCC_EMBEDDED    arm-none-eabi-gcc)
set(GCC_DESKTOP     gcc)