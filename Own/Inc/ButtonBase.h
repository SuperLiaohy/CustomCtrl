//
// Created by Administrator on 25-1-17.
//

#ifndef CUSTOMCTRL_BUTTONBASE_H
#define CUSTOMCTRL_BUTTONBASE_H

// ButtonBase.h

#include "SuperGPIO.h"

enum class ButtonStatus {
    OnClick,
    OnLongPress,
    OnDown,
    OnUp,
    OnPressing,
    None,
};

class ButtonBase {
public:
    using Callback = void (*)(void);

    ButtonBase(uint16_t longPressTime = 2000) : longPressTime(longPressTime) {}

    virtual ~ButtonBase() = default;
    virtual GPIO_PinState GetState() = 0;
    Callback callback = nullptr;

    const uint16_t long_press_time;  //按下多久才算长按
    const uint16_t press_time; //按下多久才算单击一次

    uint16_t start_press_time = 0;    //上次按下的时间
    uint16_t end_press_time = 0;

    uint8_t lastState = 0; //1/0为按下/松开
    ButtonStatus status = ButtonStatus::None;
protected:
};

#endif //CUSTOMCTRL_BUTTONBASE_H
