//
// Created by Administrator on 25-1-16.
//

#include "CustomCtrl.hpp"
#include "Button.h"

//constexpr GPIO_TypeDef* saftey_gpio(const void *gpio) {
//    return reinterpret_cast<GPIO_TypeDef*>(gpio);
//}

DetectManager Detect::detectManager;

SuperCan canPlus1(&hcan1, CAN_RX_FIFO0, CAN_IT_RX_FIFO0_MSG_PENDING);
SuperCan* CanServos::canPlus =  &canPlus1;
CanServos servos(6);

CustomCtrl<6> custom_ctrl(&huart1);

Button<GPIOA_BASE, GPIO_PIN_0, false> button1(5000,20, button_callback);

//Button<GPIOA_BASE, GPIO_PIN_0, false> button1(2000,20, button_callback);





