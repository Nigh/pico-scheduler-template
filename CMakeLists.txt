cmake_minimum_required(VERSION 3.16)

# Pull in SDK (must be before project)
include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)

project(RP2040_Template C CXX ASM)
set(FAMILY rp2040)
set(BOARD pico_sdk)



pico_sdk_init()

add_definitions(-DG_LOG_ENABLED=1 -DEVT_LOG_ENABLED=1)
add_subdirectory(scheduler)

# add_subdirectory($ENV{PICO_SDK_PATH}/lib/tinyusb build/tinyusb)
# include_directories($ENV{PICO_SDK_PATH}/lib/tinyusb/src)

add_executable(${PROJECT_NAME})

target_sources(${PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/main.c
	${CMAKE_CURRENT_LIST_DIR}/usb_descriptors.c
)

target_include_directories(${PROJECT_NAME} PUBLIC
	${CMAKE_CURRENT_LIST_DIR}
)
# Link with the pico stdlib
# hardware_clocks hardware_i2c hardware_pio hardware_interp hardware_rtc hardware_uart hardware_irq hardware_resets
# pico_unique_id
# tinyusb_host tinyusb_device tinyusb_board
target_link_libraries(${PROJECT_NAME} PUBLIC
	pico_stdlib
	tinyusb_device
	scheduler
	pico_sync
	hardware_adc
	hardware_sync
)
# Create map/bin/hex/uf2 files
pico_add_extra_outputs(${PROJECT_NAME})

# Disable USB serial
# pico_enable_stdio_usb(${PROJECT_NAME} 0)
# pico_enable_stdio_uart(${PROJECT_NAME} 0)
