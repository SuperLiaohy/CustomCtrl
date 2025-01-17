//
// Created by Administrator on 25-1-17.
//

#ifndef CUSTOMCTRL_BUTTON_H
#define CUSTOMCTRL_BUTTON_H

#include "ButtonManager.h"
#include "Filter.h"
#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
}
#endif

// 简化后的 Button 类，移除了 mode 参数
template<uint32_t gpio, uint16_t pin, bool polarity>
class Button : public ButtonBase {
public:
    Button(uint16_t longPressTime = 2000, uint16_t press_time = 50, Callback callback = nullptr)
        : ButtonBase(longPressTime, press_time, callback), io(), filter(4) {
        ButtonManager::GetInstance().Register(this);
    }

    ~Button() {
        ButtonManager::GetInstance().Unregister(this);
    }

    inline void SetCallback(Callback callback);

    uint8_t GetState() override {
        return static_cast<uint8_t>((filter.update(polarity ? io.Read() : (io.Read() ? 0 : 1))));
    }

private:
    // 简化的 SuperGPIO 特化版本，专门用于输入模式
    SuperGPIO<gpio, INPUT, pin> io;
    Filter filter;
    static uint32_t get_time() {
        return HAL_GetTick();
    }
};

template<uint32_t gpio, uint16_t pin, bool polarity>
inline void Button<gpio, pin, polarity>::SetCallback(ButtonBase::Callback callback) {
    this->callback = callback;
}

void button_callback(ButtonStatus status);

#endif //CUSTOMCTRL_BUTTON_H
