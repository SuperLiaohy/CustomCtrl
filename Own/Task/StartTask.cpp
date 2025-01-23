//
// Created by Administrator on 25-1-17.
//
#include "CppTask.h"
#include "SuperCan.hpp"
#include "CustomCtrl.hpp"

void StartDefaultTask(void* argument) {
    canPlus1.filter_config(0);
    canPlus1.can_start();
    custom_ctrl.set(5,6,2,3,4,8);
    vTaskDelete(NULL);
}