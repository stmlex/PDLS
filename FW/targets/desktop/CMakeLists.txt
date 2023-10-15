include(${PROJECT_SOURCE_DIR}/config/common.cmake)
include(${PROJECT_SOURCE_DIR}/config/desktop.cmake)

# FreeRTOS build
list(APPEND FREERTOS_SOURCES "${PORT_DIR}/ThirdParty/GCC/Posix/utils/wait_for_event.c")
list(APPEND FREERTOS_SOURCES "${PORT_DIR}/ThirdParty/GCC/Posix/port.c")
list(APPEND FREERTOS_SOURCES "${PORT_DIR}/MemMang/heap_4.c")

add_library(freertos_desktop STATIC ${FREERTOS_SOURCES})

target_include_directories(freertos_desktop PUBLIC
    ${FREERTOS_DIR}/include
    ${PORT_DIR}/ThirdParty/GCC/Posix
    ${PORT_DIR}/ThirdParty/GCC/Posix/utils
    ${CMAKE_CURRENT_SOURCE_DIR}/config
)

target_compile_options(freertos_desktop PRIVATE
    -DprojCOVERAGE_TEST=0
    -ggdb3
    -O0
)

# Add includes dir
include_directories(${DESKTOP_INCLUDE_DIR})
# Add sources
file(GLOB_RECURSE DESKTOP_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/*.c
    ${APP_DIR}/*.c
)

# Buid DESKTOP target
add_executable(${DESKTOP_TARGET} ${DESKTOP_SOURCES})

# Include paths
target_include_directories(${DESKTOP_TARGET} PRIVATE
    ${APP_DIR}
)

# Compiler options
target_compile_options(${DESKTOP_TARGET} PRIVATE
    -DprojCOVERAGE_TEST=0
)

# Link libraries
target_link_libraries(${DESKTOP_TARGET}
    PRIVATE
    freertos_desktop
    pthread
)
