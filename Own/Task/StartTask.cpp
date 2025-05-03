//
// Created by Administrator on 25-1-17.
//
#include "CppTask.h"
#include "SuperCan.hpp"
#include "CustomCtrl.hpp"
#include "Interact.h"

extern "C" void interact_start(void){
    interact.start();
};
void StartDefaultTask(void* argument) {
    canPlus1.filter_config(0);
    canPlus1.can_start();
    custom_ctrl.set(5,6,2,3,4,8);
    interact.start();
    vTaskDelete(NULL);
}