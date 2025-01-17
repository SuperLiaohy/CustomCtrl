//
// Created by Administrator on 25-1-17.
//

#include "Button.h"

void button_callback(ButtonStatus status) {
    switch (status) {
        case ButtonStatus::OnClick:
            break;
        case ButtonStatus::OnLongPress:
            HAL_GPIO_TogglePin(GPIOH, GPIO_PIN_10);
            break;
        case ButtonStatus::OnDown:
            break;
        case ButtonStatus::OnUp:
            break;
        case ButtonStatus::OnPressing:
            HAL_GPIO_TogglePin(GPIOH, GPIO_PIN_11);
            break;
        default:
            break;
    }
}

