//
// Created by Administrator on 25-1-17.
//
#include "CppTask.h"
#include "SuperCan.hpp"


void StartDefaultTask(void* argument) {
    canPlus1.filter_config(0);
    canPlus1.can_start();

    vTaskDelete(NULL);
}