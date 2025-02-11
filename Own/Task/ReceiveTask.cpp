//
// Created by Administrator on 25-2-11.
//
#include "../Task/CppTask.h"
#include "Button.h"
#include "CustomCtrl.hpp"
#include "Crc.h"
#include "Interact.h"

extern "C" void ReceiveTask(void* argument) {

    for (;;) {
        using namespace crc;
        vTaskSuspend((TaskHandle_t)OS_ReceiveTaskHandle);
        if (interact.frame_rx.s.enable_map_back) {
            interact.inverse_angle(custom_ctrl);
            custom_ctrl.back_map();
//            interact.set_map_back_over(1);
        }
    }
}