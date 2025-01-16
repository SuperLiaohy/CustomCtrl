cmake_minimum_required(VERSION 3.10)

# 项目名称
project(MyProject C CXX ASM)

############################################################
# 1. 指定编译器和链接器，避免使用默认的 gcc
############################################################
# 设置编译器 C 的编译器
set(CMAKE_C_COMPILER armclang.exe)
set(CMAKE_C_COMPILER_WORKS TRUE)

# 即便用不到C++ 的编译器，还是要显示说明的,否则报错
set(CMAKE_CXX_COMPILER armclang.exe)
set(CMAKE_CXX_COMPILER_WORKS TRUE)

#设置 ASM 的编译器（不设置配合 -masm=auto 使用）
set(CMAKE_ASM_COMPILER armclang.exe)
#set(CMAKE_ASM_COMPILER armasm.exe)     # 指明 ASM 编译器，配合 第二种 CMAKE_ASM_FLAGS_INIT 方式使用
set(CMAKE_ASM_COMPILER_WORKS TRUE)

#设置链接器
set(CMAKE_C_LINK_EXECUTABLE armlink.exe)
set(CMAKE_ASM_LINK_EXECUTABLE armlink.exe)
set(CMAKE_CXX_LINK_EXECUTABLE armlink.exe)


# 设置 CFLAGS
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -xc -std=c99 --target=arm-arm-none-eabi -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard -c -fno-rtti -funsigned-char -fshort-enums -fshort-wchar -D__EVAL -gdwarf-4 -O3 -ffunction-sections -Wno-packed -Wno-missing-variable-declarations -Wno-missing-prototypes -Wno-missing-noreturn -Wno-sign-conversion -Wno-nonportable-include-path -Wno-reserved-id-macro -Wno-unused-macros -Wno-documentation-unknown-command -Wno-documentation -Wno-license-management -Wno-parentheses-equality -Wno-reserved-identifier -I ../Core/Inc -I ../Drivers/STM32F4xx_HAL_Driver/Inc -I ../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I ../Middlewares/Third_Party/FreeRTOS/Source/include -I ../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I ../Middlewares/Third_Party/FreeRTOS/Source/portable/RVDS/ARM_CM4F -I ../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I ../Drivers/CMSIS/Include -I ../Own/Inc -I./RTE/_CustomCtrl -ID:/Keil_541_pack/ARM/CMSIS/6.1.0/CMSIS/Core/Include -ID:/Keil_541_pack/Keil/STM32F4xx_DFP/2.17.1/Drivers/CMSIS/Device/ST/STM32F4xx/Include -D__UVISION_VERSION=541 -DSTM32F407xx -D_RTE_ -DUSE_HAL_DRIVER -DSTM32F407xx -o CustomCtrl/*.o -MMD")

# 设置 CXXFLAGS
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -xc -std=c99 --target=arm-arm-none-eabi -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard -c -fno-rtti -funsigned-char -fshort-enums -fshort-wchar -D__EVAL -gdwarf-4 -O3 -ffunction-sections -Wno-packed -Wno-missing-variable-declarations -Wno-missing-prototypes -Wno-missing-noreturn -Wno-sign-conversion -Wno-nonportable-include-path -Wno-reserved-id-macro -Wno-unused-macros -Wno-documentation-unknown-command -Wno-documentation -Wno-license-management -Wno-parentheses-equality -Wno-reserved-identifier -I ../Core/Inc -I ../Drivers/STM32F4xx_HAL_Driver/Inc -I ../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I ../Middlewares/Third_Party/FreeRTOS/Source/include -I ../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I ../Middlewares/Third_Party/FreeRTOS/Source/portable/RVDS/ARM_CM4F -I ../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I ../Drivers/CMSIS/Include -I ../Own/Inc -I./RTE/_CustomCtrl -ID:/Keil_541_pack/ARM/CMSIS/6.1.0/CMSIS/Core/Include -ID:/Keil_541_pack/Keil/STM32F4xx_DFP/2.17.1/Drivers/CMSIS/Device/ST/STM32F4xx/Include -D__UVISION_VERSION=541 -DSTM32F407xx -D_RTE_ -DUSE_HAL_DRIVER -DSTM32F407xx -o CustomCtrl/*.o -MMD")

# 设置 LDFLAGS
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --cpu=cortex-m4 --strict --scatter=usart/usart.sct --summary_stderr --info=summarysizes --map --xref --callgraph --symbols --info=sizes --info=totals --info=unused --info=veneers --list=usart.map")

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
        ./RTE/_CustomCtrl
        D:/Keil_541_pack/ARM/CMSIS/6.1.0/CMSIS/Core/Include
        D:/Keil_541_pack/Keil/STM32F4xx_DFP/2.17.1/Drivers/CMSIS/Device/ST/STM32F4xx/Include
)

# 添加库文件路径
link_directories(lib)

# 使用 file(GLOB ...) 命令来获取源文件
file(GLOB SOURCES
        "Core/Src/*.c"
        "Drivers/STM32F4xx_HAL_Driver/Src/*.c"
        "Middlewares/Third_Party/FreeRTOS/Source/*.c"
)

# 添加可执行文件
add_executable(MyExecutable ${SOURCES})

# 链接库文件
target_link_libraries(MyExecutable m)