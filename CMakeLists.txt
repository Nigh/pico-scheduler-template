cmake_minimum_required(VERSION 3.16)

set(FAMILY rp2040)
# Pull in SDK (must be before project)
include(pico_sdk_import.cmake)

project(RP2040_Template C CXX ASM)

pico_sdk_init()

add_definitions(-DG_LOG_ENABLED=1 -DEVT_LOG_ENABLED=1)
add_subdirectory(scheduler)

add_executable(${PROJECT_NAME} main.c)

# Link with the pico stdlib
# hardware_clocks hardware_i2c hardware_pio hardware_interp hardware_rtc hardware_uart hardware_irq hardware_resets
# pico_unique_id
# tinyusb_host tinyusb_device tinyusb_board
target_link_libraries(${PROJECT_NAME}
	scheduler
	pico_stdlib
	pico_sync
	hardware_adc
	hardware_sync
	tinyusb_device
)
target_include_directories(${PROJECT_NAME} PUBLIC
	${CMAKE_CURRENT_LIST_DIR}
    $ENV{PICO_SDK_PATH}/lib/tinyusb/hw/bsp/${FAMILY}
    $ENV{PICO_SDK_PATH}/lib/tinyusb/src
)
# Create map/bin/hex/uf2 files
pico_add_extra_outputs(${PROJECT_NAME})

# Disable USB serial
pico_enable_stdio_usb(${PROJECT_NAME} 0)
pico_enable_stdio_uart(${PROJECT_NAME} 0)
