#include "../Task/CppTask.h"
#include "CanServos.hpp"
#include "CustomCtrl.hpp"

extern "C"
    void ServosTask(void* argument) {
    custom_ctrl.unlock();
    custom_ctrl.read();
    osDelay(1000);
    for (;;) {
        custom_ctrl.read();

//        custom_ctrl.lock();
//        servos.read_all();
//        servos.set_pos_speed(0, 150);
        osDelay(1);
    }
}