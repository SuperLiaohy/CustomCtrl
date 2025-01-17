#include "../Task/Task.h"
#include "Button.h"
extern "C" void ButtonTask(void* argument) {
    for (;;) {
        ButtonManager::GetInstance().Update();
        osDelay(1000);
    }
}