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
    void Update();

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

#endif
//CUSTOMCTRL_BUTTONMANAGER_H
