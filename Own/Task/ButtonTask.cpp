#include "../Task/CppTask.h"
#include "Button.h"

uint8_t f1;
uint8_t f0;
uint8_t p0;
uint8_t v0;
//extern Button<GPIOA_BASE, GPIO_PIN_0, false> button1;
extern Button button_pump;
extern Button button_valve;
extern "C" void ButtonTask(void* argument) {
    for (;;) {
        ButtonManager::GetInstance().Update();
        osDelay(3);
    }
}

