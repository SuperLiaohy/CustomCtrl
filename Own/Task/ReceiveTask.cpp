//
// Created by Administrator on 25-2-11.
//
#include "../Task/CppTask.h"
#include "Button.h"
#include "CustomCtrl.hpp"
#include "Crc.h"
#include "Interact.h"


extern "C" void ReceiveTask(void* argument) {
    interact.frame_rx.s.enable_map_back = 0;
    for (;;) {
        using namespace crc;
        vTaskSuspend((TaskHandle_t)OS_ReceiveTaskHandle);
        if (interact.frame_rx.s.enable_map_back) {
            interact.inverse_angle(custom_ctrl);
            osMutexAcquire(CANmutexHandle, portMAX_DELAY);
            custom_ctrl.back_map();
            osMutexRelease(CANmutexHandle);
//            interact.set_map_back_over(1);
        } else {
            osMutexAcquire(CANmutexHandle, portMAX_DELAY);
            custom_ctrl.unlock();
            osMutexRelease(CANmutexHandle);
        }
    }
}