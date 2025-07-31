//
// Created by Administrator on 25-1-16.
//

#include "CustomCtrl.hpp"
#include "Button.h"
#include "Interact.h"
#include "OwnQueue.h"
//constexpr GPIO_TypeDef* saftey_gpio(const void *gpio) {
//    return reinterpret_cast<GPIO_TypeDef*>(gpio);
//}

DetectManager Detect::detectManager;

StaticQueue<uint8_t, 50> pump_queue;
StaticQueue<uint8_t, 50> valve_queue;
SuperCan canPlus1(&hcan1, CAN_RX_FIFO0, CAN_IT_RX_FIFO0_MSG_PENDING);
SuperCan* CanServos::canPlus =  &canPlus1;
CanServos servos(6);

CustomCtrl<6> custom_ctrl;
Interact<6> interact(&huart1);

static uint8_t an=0;
uint32_t num_p=0;
uint32_t num_v=0;
void button_pump_callback(ButtonStatus status){
    switch (status) {
        case ButtonStatus::OnPressing:
            interact.set_pump(an);
            an = 1 - an;
						++num_p;
            break; 
				case ButtonStatus::OnClick:
        case ButtonStatus::OnDown:
        case ButtonStatus::OnLongPress:
        case ButtonStatus::OnUp:
            break; 
        default:
            break;
    }
}
static uint8_t openc=1;
void button_valve_callback(ButtonStatus status){
    switch (status) {
        case ButtonStatus::OnPressing:
            interact.set_valve(openc);
            openc = 1 - openc;
            break;
        case ButtonStatus::OnClick:
        case ButtonStatus::OnDown:
        case ButtonStatus::OnLongPress:
        case ButtonStatus::OnUp:
            break; 
        default:
            break;
    }
}


Button button_pump(GPIOF, GPIO_PIN_0,5000,20, button_pump_callback);
Button button_valve(GPIOF, GPIO_PIN_1,5000,20, button_valve_callback);





