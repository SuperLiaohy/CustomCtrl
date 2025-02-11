//
// Created by Administrator on 25-1-23.
//
#include "../Task/CppTask.h"
#include "Button.h"
#include "CustomCtrl.hpp"
#include "Interact.h"


extern "C" void TransmitTask(void* argument) {

    for (;;) {
        auto now = xTaskGetTickCount();
        interact.get_angle(custom_ctrl);
        interact.transmit();
        osDelayUntil(now + 33);
    }
}