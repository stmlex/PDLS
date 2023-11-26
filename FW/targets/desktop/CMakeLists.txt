include(${PROJECT_SOURCE_DIR}/cmake/common.cmake)
include(${PROJECT_SOURCE_DIR}/cmake/desktop.cmake)

if(WIN32)
	set(FREERTOS_PORT_DIR ${FREERTOS_DIR}/portable/MSVC-MingW)
	set(FREERTOS_LINK_LIB winmm)
	set(FREERTOS_DEFINITIONS
		"WIN32"
		_WIN32_WINNT=0x0400
		WINVER=0x400
	)
	set(LVGL_DRIVERS_DEFINITIONS USE_WIN32DRV)
elseif(UNIX)
	set(FREERTOS_PORT_DIR ${FREERTOS_PORT_DIR}/ThirdParty/GCC/Posix)
	set(FREERTOS_LINK_LIB pthread)
	set(LVGL_DRIVERS_DEFINITIONS USE_SDL)
else()
	message(FATAL_ERROR "Unsupported platform")
endif()

# region FreeRTOS build
list(APPEND FREERTOS_SOURCES ${FREERTOS_DIR}/portable/MemMang/heap_4.c)
file(GLOB_RECURSE FREERTOS_PORT_SOURCES ${FREERTOS_PORT_DIR}/*.c)

add_library(freertos_desktop STATIC ${FREERTOS_SOURCES} ${FREERTOS_PORT_SOURCES})

target_include_directories(freertos_desktop PUBLIC
	${FREERTOS_DIR}/include
	${FREERTOS_PORT_DIR}
	${CMAKE_CURRENT_SOURCE_DIR}/config
)
target_compile_options(freertos_desktop PRIVATE
	-DprojCOVERAGE_TEST=0
	-ggdb3
	-O0
)
target_compile_definitions(freertos_desktop PRIVATE ${FREERTOS_DEFINITIONS})
target_link_libraries(freertos_desktop PRIVATE ${FREERTOS_LINK_LIB})
# endregion

# region LVGL
add_library(lvgl_desktop STATIC ${LVGL_SOURCES})
target_include_directories(lvgl_desktop PUBLIC
	${LVGL_DIR}
	${CMAKE_CURRENT_SOURCE_DIR}/config
)
target_compile_definitions(lvgl_desktop PRIVATE
	LV_CONF_INCLUDE_SIMPLE
)
# endregion

# region LV drivers
add_library(lvgl_drivers_desktop STATIC ${LVGL_DRIVERS_SOURCES})
target_include_directories(lvgl_drivers_desktop PUBLIC
	${LVGL_DIR}
	${LVGL_DRIVERS_DIR}
	${CMAKE_CURRENT_SOURCE_DIR}/config
)
target_compile_definitions(lvgl_drivers_desktop PUBLIC
	LV_LVGL_H_INCLUDE_SIMPLE
	LV_CONF_INCLUDE_SIMPLE
	${LVGL_DRIVERS_DEFINITIONS}
)
# endregion

# Add includes dir
include_directories(${DESKTOP_INCLUDE_DIR})

# Add sources
file(GLOB_RECURSE DESKTOP_SOURCES
	${CMAKE_CURRENT_SOURCE_DIR}/*.c
	${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
	${APP_DIR}/*.c
	${APP_DIR}/*.cpp
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
	lvgl_drivers_desktop
	lvgl_desktop
)
