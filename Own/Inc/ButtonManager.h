//
// Created by Administrator on 25-1-17.
//

#ifndef CUSTOMCTRL_BUTTONMANAGER_H
    #define CUSTOMCTRL_BUTTONMANAGER_H

    #include "ButtonBase.h"
    #include "CustomList.h"

class ButtonManager {
public:
    ButtonManager(const ButtonManager&)            = delete;
    ButtonManager& operator=(const ButtonManager&) = delete;

    inline static ButtonManager& GetInstance();

    inline void Register(ButtonBase* button);

    inline void Unregister(ButtonBase* button);
    inline void Update();

private:
    ButtonManager()  = default;
    ~ButtonManager() = default;

    CustomList<ButtonBase*> buttons;
};
inline ButtonManager& ButtonManager::GetInstance() {
    static ButtonManager instance;
    return instance;
}
inline void ButtonManager::Register(ButtonBase* button) {
    buttons.push_back(button);
}
inline void ButtonManager::Unregister(ButtonBase* button) {
    buttons.remove(button);
}
inline void ButtonManager::Update() {
    static uint32_t last_update;
    uint32_t present_time = HAL_GetTick();
    for (auto button: buttons) {
        uint8_t state = button->GetState();

        uint16_t last_press_time = last_update - button->start_press_time;
        uint16_t press_time = present_time - button->start_press_time;

        if (!button->lastState && state){
            button->start_press_time = present_time;
            button->status = ButtonStatus::OnDown;
        } else if (button->lastState && !state) {
            button->status = ButtonStatus::OnUp;
            button->end_press_time = present_time;
            uint16_t delay_time = press_time - button->start_press_time;

            if (delay_time > button->press_time && delay_time < button->long_press_time) {
                button->status = ButtonStatus::OnPressing;
            }

        } else if (button->lastState && state) {
            if (last_press_time <= button->long_press_time && press_time > button->long_press_time) {
                button->status = ButtonStatus::OnLongPress;
            }
        } else {
            button->status = ButtonStatus::None;
        }
        button->callback();
    }
    last_update = present_time;
}

#endif
//CUSTOMCTRL_BUTTONMANAGER_H
