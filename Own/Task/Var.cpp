//
// Created by Administrator on 25-1-16.
//

#include "CustomCtrl.hpp"
#include "ButtonManager.h"

DetectManager Detect::detectManager;

SuperCan canPlus1(&hcan1, CAN_RX_FIFO0, CAN_IT_RX_FIFO0_MSG_PENDING);
SuperCan* CanServos::canPlus =  &canPlus1;
CustomCtrl<6> custom_ctrl(&huart1);


