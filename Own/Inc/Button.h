//
// Created by Administrator on 25-1-17.
//

#ifndef CUSTOMCTRL_BUTTON_H
#define CUSTOMCTRL_BUTTON_H

#include "ButtonManager.h"


#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
}
#endif



// 简化后的 Button 类，移除了 mode 参数
template <GPIO_TypeDef *gpio, uint16_t pin>
class Button : public ButtonBase {
public:
    Button(uint16_t longPressTime = 1000) : ButtonBase(longPressTime) {
        ButtonManager::GetInstance().Register(this);
    }

    ~Button() {
        ButtonManager::GetInstance().Unregister(this);
    }

    inline void SetCallback(Callback callback);

    GPIO_PinState GetState() override {
        return io.Read();
    }


private:
    // 简化的 SuperGPIO 特化版本，专门用于输入模式
    SuperGPIO<gpio, INPUT, pin> io;



    static uint32_t get_time() {
        return HAL_GetTick();
    }
};

template <GPIO_TypeDef *gpio, uint16_t pin>
inline void Button<gpio, pin>::SetCallback(ButtonBase::Callback callback) {
    this->callback = callback;
}
#endif //CUSTOMCTRL_BUTTON_H
