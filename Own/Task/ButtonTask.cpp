#include "../Task/Task.h"

extern "C" void ButtonTask(void* argument) {
    for (;;) {
        osDelay(1000);
    }
}