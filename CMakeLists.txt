cmake_minimum_required(VERSION 3.10)

# 项目名称
project(CustomCtrl C CXX ASM)
set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 11)

# 设置架构
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR ARM)

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
# CMAKE_C_LINK_EXECUTABLE 这种写法可能会有问题，建议改为：
set(CMAKE_LINKER armlink.exe)

# 加载sct脚本，内存布局
set(SECTIONS_SCRIPT_PATH ${CMAKE_HOME_DIRECTORY}/MDK-ARM/${PROJECT_NAME}/${PROJECT_NAME}.sct)

# 设置target的编译选项
set(C_TARGET_FLAG --target=arm-arm-none-eabi)
set(ASM_TARGET_FLAG --target=arm-arm-none-eabi)
set(LINKER_TARGET_FLAG --cpu=cortex-m4)

# 设置编译规则
set(COMPILE_RULE_FLAG "-mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard")


# 设置 C 编译器选项(这里就把MDK中的 C/C++ 分页里最下边一栏的属性贴进来)
# 参数 -w 表示忽略所有警告，不然要配具体忽略哪些警告，尽管贴过来也行，但是太乱
# 优化选项 -O 有 1~3   -Os 是平衡  -Oz 是最小体积
set(CMAKE_C_FLAGS_INIT "${C_TARGET_FLAG} ${COMPILE_RULE_FLAG} \
    -xc -std=c99
-fno-rtti -funsigned-char -fshort-enums -fshort-wchar -w")

# 设置 C++ 编译器选项
set(CMAKE_CXX_FLAGS_INIT ${CMAKE_C_FLAGS_INIT})

# 设置ASM编译器选项
# 注意： -masm=auto 选项是 MDK 的 link 分页里没有的参数，需要加上  -g 是debug 用的加不加都行
set(CMAKE_ASM_FLAGS_INIT "${ASM_TARGET_FLAG} ${COMPILE_RULE_FLAG} -masm=auto -Wa,armasm,--diag_suppress=A1950W -c -gdwarf-4")

# 设置连接器的选项
set(CMAKE_EXE_LINKER_FLAGS_INIT  " \
            ${LINKER_TARGET_FLAG} \
            --strict \
            --scatter ${SECTIONS_SCRIPT_PATH} \
            --summary_stderr --info summarysizes"
#             --map --load_addr_map_info --xref --callgraph --symbols
            "--info sizes --info totals --info unused --info veneers"
#            --list CustomCtrl.map
#            -o CustomCtrl/CustomCtrl.axf

)

#Uncomment for hardware floating point
add_compile_definitions(ARM_MATH_CM4;ARM_MATH_MATRIX_CHECK;ARM_MATH_ROUNDING)
add_compile_options(-mfloat-abi=hard -mfpu=fpv4-sp-d16)
add_link_options(-mfloat-abi=hard -mfpu=fpv4-sp-d16)

#Uncomment for software floating point
#add_compile_options(-mfloat-abi=soft)


add_definitions(-DUSE_HAL_DRIVER -DSTM32F407xx)
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
# 使用 file(GLOB ...) 命令来获取源文件
# FreeRTOS 相关源文件没有完全包含，建议添加：
file(GLOB SOURCES
        "MDK-ARM/startup_stm32f407xx.s"
        "Core/Src/*.c"
        "Drivers/STM32F4xx_HAL_Driver/Src/*.c"
        "Middlewares/Third_Party/FreeRTOS/Source/*.c"
        "Middlewares/Third_Party/FreeRTOS/Source/portable/RVDS/ARM_CM4F/*.c"  # 添加这行
        "Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2/*.c"           # 添加这行
)

add_executable(${PROJECT_NAME} ${SOURCES} ${LINKER_SCRIPT})

set(HEX_FILE ${PROJECT_BINARY_DIR}/${PROJECT_NAME}.hex)
set(BIN_FILE ${PROJECT_BINARY_DIR}/${PROJECT_NAME}.bin)
set(ELF_FILE ${PROJECT_BINARY_DIR}/${PROJECT_NAME}.elf)

# 使用 armclang 自带的 fromelf 工具，实现 elf 转 hex
set(ARMCC_fromelf fromelf.exe)
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        # 相当于fromelf.exe" --i32combined --output="xxx/testF4.hex" "xxx/testF4.elf"
        COMMAND ${ARMCC_fromelf} --i32combined --output="${HEX_FILE}" "${ELF_FILE}"
        COMMENT "Building ${HEX_FILE}"
)



