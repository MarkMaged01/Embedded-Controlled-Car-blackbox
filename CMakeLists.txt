cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# == DO NOT EDIT THE FOLLOWING LINES for the Raspberry Pi Pico VS Code Extension to work ==
if(WIN32)
    set(USERHOME $ENV{USERPROFILE})
else()
    set(USERHOME $ENV{HOME})
endif()
set(sdkVersion 2.0.0)
set(toolchainVersion 13_2_Rel1)
set(picotoolVersion 2.0.0)
set(picoVscode ${USERHOME}/.pico-sdk/cmake/pico-vscode.cmake)
if (EXISTS ${picoVscode})
    include(${picoVscode})
endif()
# ====================================================================================
set(PICO_BOARD arduino_nano_rp2040_connect CACHE STRING "Board type")

# Pull in Raspberry Pi Pico SDK (must be before project)
include(pico_sdk_import.cmake)

project(Arduino_test C CXX ASM)

# Initialise the Raspberry Pi Pico SDK
pico_sdk_init()

# Include Arduino-Pico headers
include_directories(${CMAKE_SOURCE_DIR}/arduino-pico)

# Add executable. Default name is the project name, version 0.1
add_executable(Arduino_test 
            Arduino_test.c
            IR.c
            hardware_control.c
            nina_w102.c
            hc05.c
            )

pico_set_program_name(Arduino_test "Arduino_test")
pico_set_program_version(Arduino_test "0.1")

# Modify the below lines to enable/disable output over UART/USB
pico_enable_stdio_uart(Arduino_test 0)  # UART is disabled
pico_enable_stdio_usb(Arduino_test 1)  # USB is enabled

# Add the standard library to the build
target_link_libraries(Arduino_test pico_stdlib)

# Add the standard include files to the build
target_include_directories(Arduino_test PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}
)

# Include the FatFs library (if used for SD card support)
target_include_directories(Arduino_test PRIVATE
    ${CMAKE_SOURCE_DIR}/libraries/FatFs/include
)

# Link necessary libraries for MPU6050 and other peripherals
target_link_libraries(Arduino_test 
    hardware_i2c
    hardware_gpio
    hardware_pwm
)

# ===================== MPU6050 and Wire Library Configuration =====================
# Add GY87.c and other sources if needed
target_sources(Arduino_test PRIVATE
    GY87.c
    libraries/MPU6050/mpu6050.c  # Ensure the mpu6050.c is added here
)

# Include directories for the MPU6050 library (adjust the path if necessary)
target_include_directories(Arduino_test PRIVATE
    ${CMAKE_SOURCE_DIR}/libraries/MPU6050
)
# ==================================================================================
pico_add_extra_outputs(Arduino_test)
