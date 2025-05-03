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

class SuperGPIO {
public:
    SuperGPIO(GPIO_TypeDef *gpio, uint16_t pin)
        : gpio(gpio), pin(pin) {
    };

    ~SuperGPIO() = default;

    inline void WriteUp() {
        HAL_GPIO_WritePin(gpio, pin, GPIO_PIN_SET);
    };

    inline void WriteDown() {
        HAL_GPIO_WritePin(gpio, pin, GPIO_PIN_RESET);
    };

    void Write(int32_t value) {
        value ? WriteUp() : WriteDown();
    };

    void Toggle() {
        HAL_GPIO_TogglePin(gpio, pin);
    };

    GPIO_PinState Read() {
        return HAL_GPIO_ReadPin(gpio, pin);
    };

    friend void ::HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin);

protected:
    GPIO_TypeDef *gpio;
    uint16_t pin;
};

#endif //NONE_PRJ_SUPERGPIO_H
