#include "CppTask.h"
#include "Detect.h"
extern "C" void DetectTask(void* argument) {
    while (1) {
        Detect::detectManager.JudgeLost();
        osDelay(10);
    }
}