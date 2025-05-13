#include "../Task/CppTask.h"
#include "CanServos.hpp"
#include "CustomCtrl.hpp"

uint16_t cmd = 5;
float speed  = 0;
float pos    = 200;
uint8_t a    = 0;
uint8_t b    = 0;
uint8_t c    = 0;
extern "C" void ServosTask(void* argument) {
    osMutexAcquire(CANmutexHandle, portMAX_DELAY);

    custom_ctrl.unlock();
    custom_ctrl.read();
    osMutexRelease(CANmutexHandle);

    osDelay(1000);
    for (;;) {
        osMutexAcquire(CANmutexHandle, portMAX_DELAY);
        custom_ctrl.read();
        osMutexRelease(CANmutexHandle);
        //        servos.read_all();
        //        servos.set_pos_speed(0, 150);
        osDelay(1);
    }
}