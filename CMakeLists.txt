cmake_minimum_required(VERSION 3.10)

# 设置策略
if(POLICY CMP0123)
    cmake_policy(SET CMP0123 NEW)
endif()

# 在project命令之前设置工具链
set(CMAKE_TOOLCHAIN_FILE ${CMAKE_CURRENT_SOURCE_DIR}/arm-none-eabi-toolchain.cmake)

# 项目名称
project(CustomCtrl
        VERSION 1.0.0
        LANGUAGES C CXX ASM
        DESCRIPTION "STM32F407 Custom Control Project"
)

# 确保使用正确的处理器设置
if(NOT CMAKE_SYSTEM_PROCESSOR STREQUAL "cortex-m4")
    message(FATAL_ERROR "CMAKE_SYSTEM_PROCESSOR must be set to cortex-m4")
endif()

# 编译器标准
set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 11)

# 通用编译标志
set(COMMON_FLAGS "--target=arm-arm-none-eabi -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard")

# 设置编译器标志
set(CMAKE_C_FLAGS "${COMMON_FLAGS} -xc -std=c99 -fno-rtti -funsigned-char -fshort-enums -fshort-wchar")
set(CMAKE_CXX_FLAGS ${CMAKE_C_FLAGS})
set(CMAKE_ASM_FLAGS "${COMMON_FLAGS} -masm=auto")

# 链接器标志
set(CMAKE_EXE_LINKER_FLAGS
        "--cpu=Cortex-M4 \
    --strict \
    --scatter \"${CMAKE_SOURCE_DIR}/MDK-ARM/${PROJECT_NAME}/${PROJECT_NAME}.sct\" \
    --summary_stderr --info summarysizes \
    --info sizes --info totals --info unused --info veneers \
    --list \"${CMAKE_BINARY_DIR}/${PROJECT_NAME}.map\""
)

# 添加编译定义
add_compile_definitions(
        ARM_MATH_CM4
        ARM_MATH_MATRIX_CHECK
        ARM_MATH_ROUNDING
        USE_HAL_DRIVER
        STM32F407xx
)

# 添加头文件路径
include_directories(
        Core/Inc
        Drivers/STM32F4xx_HAL_Driver/Inc
        Drivers/STM32F4xx_HAL_Driver/Inc/Legacy
        Middlewares/Third_Party/FreeRTOS/Source/include
        Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2
        Middlewares/Third_Party/FreeRTOS/Source/portable/RVDS/ARM_CM4F
        Drivers/CMSIS/Device/ST/STM32F4xx/Include
        Drivers/CMSIS/Include
        Own/Inc
        "D:/Keil_541_pack/ARM/CMSIS/6.1.0/CMSIS/Core/Include"
        "D:/Keil_541_pack/Keil/STM32F4xx_DFP/2.17.1/Drivers/CMSIS/Device/ST/STM32F4xx/Include"
)

# 获取源文件
file(GLOB SOURCES
        "MDK-ARM/startup_stm32f407xx.s"
        "Core/Src/*.c"
        "Drivers/STM32F4xx_HAL_Driver/Src/*.c"
        "Middlewares/Third_Party/FreeRTOS/Source/*.c"
        "Middlewares/Third_Party/FreeRTOS/Source/portable/RVDS/ARM_CM4F/*.c"
        "Middlewares/Third_Party/FreeRTOS/Source/portable/MemMang/*.c"
        "Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2/*.c"
)

# 创建可执行文件
add_executable(${PROJECT_NAME} ${SOURCES})

# 设置输出文件扩展名
set_target_properties(${PROJECT_NAME} PROPERTIES
        SUFFIX ".axf"
)

# 生成hex和bin文件
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${TOOLCHAIN_PATH}/fromelf.exe --i32combined --output="${CMAKE_BINARY_DIR}/${PROJECT_NAME}.hex" "${CMAKE_BINARY_DIR}/${PROJECT_NAME}.axf"
        COMMAND ${TOOLCHAIN_PATH}/fromelf.exe --bin --output="${CMAKE_BINARY_DIR}/${PROJECT_NAME}.bin" "${CMAKE_BINARY_DIR}/${PROJECT_NAME}.axf"
        COMMENT "Building ${PROJECT_NAME}.hex and ${PROJECT_NAME}.bin"
)