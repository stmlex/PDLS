include(${PROJECT_SOURCE_DIR}/cmake/common.cmake)
include(${PROJECT_SOURCE_DIR}/cmake/desktop.cmake)

# region RTOS build
if(WIN32)
	set(RTOS_PORT_DIR ${RTOS_DIR}/ports/win32/vs_2019)
	set(GUIX_PORT_DIR ${GUIX_DIR}/ports/win32)
	set(RTOS_LINK_LIBRARIES winmm)
elseif(UNIX)
	set(RTOS_PORT_DIR ${RTOS_DIR}/ports/linux/gnu)
	set(GUIX_PORT_DIR ${GUIX_DIR}/ports/linux/gnu)
	set(RTOS_LINK_LIBRARIES pthread rt)
endif()

file(GLOB RTOS_PORT_SOURCES ${RTOS_PORT_DIR}/src/*.c)
add_library(rtos_desktop STATIC ${RTOS_SOURCES} ${RTOS_PORT_SOURCES})
target_include_directories(rtos_desktop PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}/config
	${RTOS_DIR}/common/inc
	${RTOS_PORT_DIR}/inc
)
target_link_libraries(rtos_desktop PUBLIC ${RTOS_LINK_LIBRARIES})
target_compile_definitions(rtos_desktop PUBLIC TX_INCLUDE_USER_DEFINE_FILE)
# endregion

# region GUIX
file(GLOB_RECURSE GUIX_PORT_SOURCES ${GUIX_PORT_DIR}/src/*.c)
add_library(guix_desktop STATIC ${GUIX_SOURCES} ${GUIX_PORT_SOURCES})
target_include_directories(guix_desktop PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}/config
	${GUIX_DIR}/common/inc
	${GUIX_PORT_DIR}/inc
)
target_link_libraries(guix_desktop PUBLIC rtos_desktop)
target_compile_definitions(rtos_desktop PUBLIC GX_INCLUDE_USER_DEFINE_FILE)
# endregion

# Add sources
file(GLOB_RECURSE DESKTOP_SOURCES
	${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
	${APP_DIR}/*.cpp
	${GUIX_RES}/*.c
)

# Buid DESKTOP target
add_executable(${DESKTOP_TARGET} ${DESKTOP_SOURCES})

# Include paths
target_include_directories(${DESKTOP_TARGET} PRIVATE
	${APP_DIR}
	${DESKTOP_INCLUDE_DIR}
)
# Link libraries
target_link_libraries(${DESKTOP_TARGET}
	rtos_desktop
	guix_desktop
)