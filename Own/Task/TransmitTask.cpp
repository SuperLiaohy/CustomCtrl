//
// Created by Administrator on 25-1-23.
//
#include "../Task/CppTask.h"
#include "Button.h"
#include "CustomCtrl.hpp"
#include "Interact.h"
#include "OwnQueue.h"
extern uint32_t num_p;
extern uint32_t num_v;
uint32_t c_p=0;
uint32_t c_v=0;
extern "C" void TransmitTask(void* argument) {

    for (;;) {
        interact.get_angle(custom_ctrl);
        interact.transmit();
        osDelay(33);
    }
}