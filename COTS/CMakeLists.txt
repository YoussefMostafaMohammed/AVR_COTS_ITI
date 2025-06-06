cmake_minimum_required(VERSION 3.1...3.22)

# Project Configuration
project(Test_Kbad C)
set(MCU atmega32)       # Target microcontroller
set(F_CPU 8000000UL)    # Clock frequency

#---------------------------------------
# AVR Toolchain Configuration
#---------------------------------------
set(CMAKE_SYSTEM_NAME Generic)

# Build libraries first
add_subdirectory(2-MCAL/MDIO)
add_subdirectory(2-MCAL/MPORT)
add_subdirectory(2-MCAL/MEXIT)
add_subdirectory(2-MCAL/MGIE)
add_subdirectory(3-HAL/HSEVENSEG)
add_subdirectory(3-HAL/HLED)
add_subdirectory(3-HAL/HSWITCH)
add_subdirectory(3-HAL/HCLCD)
add_subdirectory(3-HAL/HKPAD)


set(CMAKE_C_COMPILER /usr/bin/avr-gcc)
set(MCU atmega32)       # Set your microcontroller
set(PROGRAMMER usbasp)    # Set your programmer ID

# AVR-specific paths
find_path(AVR_INCLUDE_DIR avr/io.h
  PATHS /usr/lib/avr/include /usr/avr/include
  REQUIRED
)

# Compiler/Linker Flags
#---------------------------------------------------
add_compile_options(
  -mmcu=${MCU}
  -DF_CPU=${F_CPU}
  -Os
  -Wall
  -Wextra
  -ffunction-sections
  -fdata-sections
  -I${AVR_INCLUDE_DIR}  # Explicitly include AVR headers
)

add_link_options(
  -mmcu=${MCU}
  -Wl,--gc-sections     # Remove unused sections
)

# Prevent host system headers from being used
include_directories(${AVR_INCLUDE_DIR})
set(CMAKE_C_FLAGS "-nostdinc")

#---------------------------------------
# Project Structure
#---------------------------------------
if(${PROJECT_NAME} STREQUAL "Binary_Counter")
    set(AssignmentDir Assignment_1)
elseif(${PROJECT_NAME} STREQUAL "Control_Led")
    set(AssignmentDir Assignment_1)
elseif(${PROJECT_NAME} STREQUAL "Control_3_Leds")
    set(AssignmentDir Assignment_2)
elseif(${PROJECT_NAME} STREQUAL "TestLedSwitch")
    set(AssignmentDir Assignment_3)
elseif(${PROJECT_NAME} STREQUAL "TestSevenSeg")
    set(AssignmentDir Assignment_4)
elseif(${PROJECT_NAME} STREQUAL "Test_HCLCD")
    set(AssignmentDir Assignment_5)
elseif(${PROJECT_NAME} STREQUAL "Alian_Invation")
    set(AssignmentDir Assignment_6)
elseif(${PROJECT_NAME} STREQUAL "Test_Kbad")
    set(AssignmentDir Assignment_7)
endif()
#---------------------------------------
# Source Files and Targets
#---------------------------------------
file(GLOB APP_SOURCES 
  ${CMAKE_SOURCE_DIR}/4-APP/${AssignmentDir}/${PROJECT_NAME}/*.c
)

# Main executable
add_executable(${PROJECT_NAME}.elf ${APP_SOURCES})

# Link libraries
target_link_libraries(${PROJECT_NAME}.elf 
  PRIVATE 
  MDIO
  MPORT
  HSEVENSEG
  HLED
  HSWITCH
  HCLCD
  HKPAD
  MEXIT
  MGIE
)

#---------------------------------------
# Flashing/Burning
#---------------------------------------
include(${CMAKE_SOURCE_DIR}/CmakeScript.cmake)
FlashAndBurn()
