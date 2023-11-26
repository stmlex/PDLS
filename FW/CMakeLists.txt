cmake_minimum_required(VERSION 3.22)

# Setup compiler settings
set(CMAKE_C_STANDARD                11)
set(CMAKE_C_STANDARD_REQUIRED       ON)
set(CMAKE_C_EXTENSIONS              ON)
set(CMAKE_CXX_STANDARD              20)
set(CMAKE_CXX_STANDARD_REQUIRED     ON)
set(CMAKE_CXX_EXTENSIONS            ON)

set_property(GLOBAL PROPERTY RULE_MESSAGES OFF)

include(cmake/common.cmake)
include(cmake/mcu.cmake)
include(cmake/desktop.cmake)
include(cmake/utils.cmake)
include(FetchContent)
# endregion

project(PDLS VERSION 0.5.0 LANGUAGES C CXX ASM)

LOG_INFO("Version:.........." ${CMAKE_PROJECT_VERSION})
LOG_INFO("Host system:......" ${CMAKE_SYSTEM_NAME})
LOG_INFO("Build type:......." ${CMAKE_BUILD_TYPE})
LOG_INFO("Desktop target:..." ${DESKTOP_TARGET})
LOG_INFO("MCU target:......." ${STM32G474_TARGET})

add_subdirectory(cmake)
add_subdirectory(targets)

# Added color compiler output
if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    add_compile_options(-fdiagnostics-color=always)
elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    add_compile_options(-fcolor-diagnostics)
endif()

# region Tests
message("******* [Unit test list] *******")
enable_testing()
# endregion
