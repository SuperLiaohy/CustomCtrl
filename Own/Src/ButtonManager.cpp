//
// Created by Administrator on 25-1-17.
//

#include "ButtonManager.h"
void ButtonManager::Update() {
    static uint32_t last_update;
    uint32_t present_time = HAL_GetTick();
    for (auto button: buttons) {
        uint8_t state = button->GetState(); //获取当前电气状态 松开为0，按下为1

        uint16_t last_press_time = last_update - button->start_press_time;  //从开始按压到上一次更新的时间
        uint16_t press_time = present_time - button->start_press_time;  //从开始按压到现在的时间

        if (!button->lastState && state){   //上一次为松开，现在为按下，判断为开始按下 为OnDown
            button->start_press_time = present_time;
            button->status = ButtonStatus::OnDown;
            button->callback(button->status);

        } else if (button->lastState && !state) {   //上一次为按下，现在为松开，判断为松开 为OnUp
            button->end_press_time = present_time;
            button->status = ButtonStatus::OnUp;
            button->callback(button->status);

            uint16_t delay_time = press_time - button->start_press_time;
            if (delay_time > button->is_press_time && delay_time < button->is_long_press_time) {    //判断从按下到松开的时间是否在按压时间内，是的话为按压，要放在OnUp判断，这样可以避免长按的时候触发
                button->status = ButtonStatus::OnPressing;
                button->callback(button->status);
            }

        } else if (button->lastState && state) {    //上一次为按下，现在为按下
            if (last_press_time <= button->is_long_press_time && press_time > button->is_long_press_time) {   //如果上一次按压时间不满足长按，这次时间满足长按，为长按执行回调
                button->status = ButtonStatus::OnLongPress;
                button->callback(button->status);
            }

        } else {
            button->status = ButtonStatus::None;
            button->callback(button->status);
        }
        button->lastState = state;
    }
    last_update = present_time;
}