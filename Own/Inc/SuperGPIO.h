//
// Created by liaohy on 8/30/24.
//

#ifndef NONE_PRJ_SUPERGPIO_H
#define NONE_PRJ_SUPERGPIO_H

#include "concepts"

#ifdef __cplusplus
extern "C" {
#endif

#include "gpio.h"

#ifdef __cplusplus
}
#endif

enum pin_mode {
    INPUT = 0,
    OUTPUT,
    ALTERNATE,
    OPEN_DRAIN,
};


template <GPIO_TypeDef *gpio, pin_mode mode, uint16_t pin>
class SuperGPIO {
public:
    SuperGPIO() = default;
    ~SuperGPIO() = default;

    inline void WriteUp() requires (mode == OUTPUT || mode == OPEN_DRAIN);

    inline void WriteDown() requires (mode == OUTPUT || mode == OPEN_DRAIN);

    void Write(int32_t value) requires (mode == OUTPUT || mode == OPEN_DRAIN);

    void Toggle() requires (mode == OUTPUT || mode == OPEN_DRAIN);

    GPIO_PinState Read() requires (mode == INPUT);

    friend void::HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin);

};

template <GPIO_TypeDef *gpio, pin_mode mode, uint16_t pin>
inline void SuperGPIO<gpio, mode, pin>::WriteUp() requires (mode == OUTPUT || mode == OPEN_DRAIN) {
    HAL_GPIO_WritePin(gpio, pin, GPIO_PIN_SET);
}

template <GPIO_TypeDef *gpio, pin_mode mode, uint16_t pin>
inline void SuperGPIO<gpio, mode, pin>::WriteDown() requires (mode == OUTPUT || mode == OPEN_DRAIN) {
    HAL_GPIO_WritePin(gpio, pin, GPIO_PIN_RESET);
}

template <GPIO_TypeDef *gpio, pin_mode mode, uint16_t pin>
void SuperGPIO<gpio, mode, pin>::Write(int32_t value) requires (mode == OUTPUT || mode == OPEN_DRAIN) {
    value ? WriteUp() : WriteDown();
}

template <GPIO_TypeDef *gpio, pin_mode mode, uint16_t pin>
void SuperGPIO<gpio, mode, pin>::Toggle() requires (mode == OUTPUT || mode == OPEN_DRAIN) {
    HAL_GPIO_TogglePin(gpio, pin);
}

template <GPIO_TypeDef *gpio, pin_mode mode, uint16_t pin>
GPIO_PinState SuperGPIO<gpio, mode, pin>::Read() requires (mode == INPUT) {
    return HAL_GPIO_ReadPin(gpio, pin);
}

//inline void <>SuperGPIO::WriteUp() {
//    HAL_GPIO_WritePin(gpio, pin, GPIO_PIN_SET);
//}
//
//inline void SuperGPIO::WriteDown() {
//    HAL_GPIO_WritePin(gpio, pin, GPIO_PIN_RESET);
//}
//
//inline void SuperGPIO::Write(int32_t value) {
//    value ? WriteUp() : WriteDown();
//}
//
//inline void SuperGPIO::Toggle() {
//    HAL_GPIO_TogglePin(gpio, pin);
//}
//
//inline GPIO_PinState SuperGPIO::Read() {
//    return HAL_GPIO_ReadPin(gpio, pin);
//}
#endif //NONE_PRJ_SUPERGPIO_H
