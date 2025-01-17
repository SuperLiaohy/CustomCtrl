#ifndef __CUSTOM_CTRL_H
#define __CUSTOM_CTRL_H

#include "CanServos.hpp"
#include "SuperCan.hpp"

#include "array"
#include "SuperUart.h"


#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
}
#endif

enum Status {
    INIT,
    OPEN,
    STOP,
};

template <uint8_t T>
class CustomCtrl {
public:
    CustomCtrl(UART_HandleTypeDef *huart) : s(INIT), uartPlus(huart, 60, 30) {
        for (int i = 0; i < T; i++) {
            servos[i].id = i;
        }
    }
    std::array<CanServos, T> servos;

    Status s;

private:
    SuperUart uartPlus;
};

extern CustomCtrl<6> custom_ctrl;

#endif
