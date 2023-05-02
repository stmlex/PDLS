include(${PROJECT_SOURCE_DIR}/config/common.cmake)
include(${PROJECT_SOURCE_DIR}/config/desktop.cmake)

set(CMAKE_C_COMPILER ${GCC_DESKTOP})
# Set defines
add_definitions(-DprojCOVERAGE_TEST=0)
add_definitions(-D_WINDOWS_)

# Add includes dir
include_directories(${DESKTOP_INCLUDE_DIR})
# Add sources
file(GLOB_RECURSE DESKTOP_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/*.c
    ${APP_DIR}/*.c)

# Buid DESKTOP target
add_executable(${DESKTOP_TARGET} ${DESKTOP_SOURCES})

# Include paths
target_include_directories(${DESKTOP_TARGET} PRIVATE
    ${APP_DIR}
)
