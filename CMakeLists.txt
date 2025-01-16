cmake_minimum_required(VERSION 3.10)

# 设置架构（放在 project 命令之前）
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR ARM)

# 项目名称
project(CustomCtrl C CXX ASM)
set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 11)

############################################################
# 1. 指定编译器和链接器
############################################################
# 设置工具链路径
set(TOOLCHAIN_PATH "D:/Keil_541/ARM/ARMCLANG/bin")

# 设置编译器
set(CMAKE_C_COMPILER "${TOOLCHAIN_PATH}/armclang.exe")
set(CMAKE_CXX_COMPILER "${TOOLCHAIN_PATH}/armclang.exe")
set(CMAKE_ASM_COMPILER "${TOOLCHAIN_PATH}/armclang.exe")
set(CMAKE_LINKER "${TOOLCHAIN_PATH}/armlink.exe")
set(CMAKE_C_COMPILER_WORKS TRUE)
set(CMAKE_CXX_COMPILER_WORKS TRUE)
set(CMAKE_ASM_COMPILER_WORKS TRUE)

# 检查工具是否存在
find_program(ARMCLANG_COMPILER armclang.exe PATHS ${TOOLCHAIN_PATH})
if(NOT ARMCLANG_COMPILER)
    message(FATAL_ERROR "armclang.exe not found in ${TOOLCHAIN_PATH}")
endif()

# 加载sct脚本
set(SECTIONS_SCRIPT_PATH ${CMAKE_HOME_DIRECTORY}/MDK-ARM/${PROJECT_NAME}/${PROJECT_NAME}.sct)
if(NOT EXISTS ${SECTIONS_SCRIPT_PATH})
    message(FATAL_ERROR "Scatter file not found: ${SECTIONS_SCRIPT_PATH}")
endif()

# 设置编译标志
set(COMMON_FLAGS "--target=arm-arm-none-eabi -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard")

# 设置编译器选项
set(CMAKE_C_FLAGS_INIT "${COMMON_FLAGS} -xc -std=c99 -fno-rtti -funsigned-char -fshort-enums -fshort-wchar -w")
set(CMAKE_CXX_FLAGS_INIT ${CMAKE_C_FLAGS_INIT})
set(CMAKE_ASM_FLAGS_INIT "${COMMON_FLAGS} -masm=auto -Wa,armasm,--diag_suppress=A1950W -c -gdwarf-4")

# 设置链接器选项
set(CMAKE_EXE_LINKER_FLAGS_INIT
        "--cpu=cortex-m4 \
    --strict \
    --scatter ${SECTIONS_SCRIPT_PATH} \
    --summary_stderr --info summarysizes \
    --info sizes --info totals --info unused --info veneers"
)

# 添加编译定义
add_compile_definitions(
        ARM_MATH_CM4
        ARM_MATH_MATRIX_CHECK
        ARM_MATH_ROUNDING
        USE_HAL_DRIVER
        STM32F407xx
)

# 添加编译选项
add_compile_options(
        -mfloat-abi=hard
        -mfpu=fpv4-sp-d16
)

# 添加链接选项
add_link_options(
        -mfloat-abi=hard
        -mfpu=fpv4-sp-d16
)

# 添加头文件路径
include_directories(
        ../Core/Inc
        ../Drivers/STM32F4xx_HAL_Driver/Inc
        ../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy
        ../Middlewares/Third_Party/FreeRTOS/Source/include
        ../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2
        ../Middlewares/Third_Party/FreeRTOS/Source/portable/RVDS/ARM_CM4F
        ../Drivers/CMSIS/Device/ST/STM32F4xx/Include
        ../Drivers/CMSIS/Include
        ../Own/Inc
        D:/Keil_541_pack/ARM/CMSIS/6.1.0/CMSIS/Core/Include
        D:/Keil_541_pack/Keil/STM32F4xx_DFP/2.17.1/Drivers/CMSIS/Device/ST/STM32F4xx/Include
)

# 获取源文件
file(GLOB SOURCES
        "MDK-ARM/startup_stm32f407xx.s"
        "Core/Src/*.c"
        "Drivers/STM32F4xx_HAL_Driver/Src/*.c"
        "Middlewares/Third_Party/FreeRTOS/Source/*.c"
        "Middlewares/Third_Party/FreeRTOS/Source/portable/RVDS/ARM_CM4F/*.c"
        "Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2/*.c"
)

# 创建可执行文件
add_executable(${PROJECT_NAME} ${SOURCES})

# 设置输出文件
set(HEX_FILE ${PROJECT_BINARY_DIR}/${PROJECT_NAME}.hex)
set(BIN_FILE ${PROJECT_BINARY_DIR}/${PROJECT_NAME}.bin)
set(ELF_FILE ${PROJECT_BINARY_DIR}/${PROJECT_NAME}.elf)

# 添加后期生成命令
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${TOOLCHAIN_PATH}/fromelf.exe --i32combined --output="${HEX_FILE}" "${ELF_FILE}"
        COMMAND ${TOOLCHAIN_PATH}/fromelf.exe --bin --output="${BIN_FILE}" "${ELF_FILE}"
        COMMENT "Building ${HEX_FILE} and ${BIN_FILE}"
)