#include "../Task/CppTask.h"
#include "CustomCtrl.hpp"

extern "C" void ServosTask(void* argument) {
    servos.unlock();
    for (;;) {
        servos.read_all();
        osDelay(1);

    }
}