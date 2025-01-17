#include "../Task/CppTask.h"
#include "CustomCtrl.hpp"

extern "C" void ServosTask(void* argument) {
    servos.unlock();
    for (;;) {
        servos.read();
        osDelay(1);

    }
}