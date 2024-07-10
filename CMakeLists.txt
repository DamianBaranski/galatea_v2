cmake_minimum_required(VERSION 3.15.3)

project(galatea_v2)

enable_language(C CXX ASM)


set(EXECUTABLE ${PROJECT_NAME}.elf)

add_executable(${EXECUTABLE})
add_subdirectory(src)

set_property(TARGET ${EXECUTABLE} PROPERTY CXX_STANDARD 11)

target_compile_definitions(${EXECUTABLE} PRIVATE
        -DUSE_HAL_DRIVER
        -DSTM32F303xx
        )

target_compile_options(${EXECUTABLE} PRIVATE
        -c -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -DUSE_HAL_DRIVER -DSTM32F303xx -DSTM32F303xC -Og -Wall -fdata-sections -ffunction-sections
	-g -F dwarf
        )

target_link_options(${EXECUTABLE} PRIVATE
	-T${CMAKE_SOURCE_DIR}/src/arch/stm32f303/LinkerScript.ld
        -mcpu=cortex-m4
        -mthumb
        -mfloat-abi=hard
        -specs=nano.specs
        -lc
        -lm
        -lnosys
        -Wl,-Map=${PROJECT_NAME}.map,--cref
        -Wl,--gc-sections
	-g -F dwarf
        )

# Print executable size
add_custom_command(TARGET ${EXECUTABLE}
        POST_BUILD
        COMMAND arm-none-eabi-size ${EXECUTABLE})

# Create hex file
add_custom_command(TARGET ${EXECUTABLE}
        POST_BUILD
        COMMAND arm-none-eabi-objcopy -O ihex ${EXECUTABLE} ${PROJECT_NAME}.hex
        COMMAND arm-none-eabi-objcopy -O binary ${EXECUTABLE} ${PROJECT_NAME}.bin)
