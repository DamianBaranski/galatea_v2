target_sources(${EXECUTABLE} PUBLIC
startup_stm32f303xc.s
sysmem.c
system_stm32f3xx.c
)

target_include_directories(${EXECUTABLE} PUBLIC 
${CMAKE_CURRENT_SOURCE_DIR}
)

