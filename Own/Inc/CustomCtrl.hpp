#ifndef __CUSTOM_CTRL_H
#define __CUSTOM_CTRL_H

#include "CanServos.hpp"
#include "Interact.h"
#include "SuperCan.hpp"
#include "SuperUart.h"

#include "array"

#ifdef __cplusplus
extern "C" {
#endif
#include "cmsis_os2.h"
#ifdef __cplusplus
}
#endif

enum Status {
    INIT,
    OPEN,
    STOP,
};

template<uint8_t T>
class CustomCtrl {
public:
    CustomCtrl(UART_HandleTypeDef* huart)
        : s(INIT)
        , uartPlus(huart, 80, 80) {
        //        for (int i = 0; i < T; i++) {
        //            servos[i].id = i;
        //        }
        memcpy(uartPlus.tx_buffer, &interact_dep::frame_send, sizeof(interact_dep::receive_data_t));
    }
    std::array<CanServos, T> servos;
    Status s;

    template<typename... Args>
    void set(Args... args) {
        static_assert(sizeof...(Args) <= T, "Number of arguments exceeds the size of the array");
        float load[] = {static_cast<float>(args)...};
        for (std::size_t i = 0; i < sizeof...(Args); ++i) {
            servos[i].id = load[i];
        }
    }

    void read();
    void lock();
    void unlock();
    void get_feedback();
    void transmit();

private:
    SuperUart uartPlus;
};
template<uint8_t T>
void CustomCtrl<T>::read() {
    for (auto & item: servos) {
        item.read();
        osDelay(1);
    }
}

template<uint8_t T>
void CustomCtrl<T>::get_feedback() {
    for (auto & item: servos) {
        if (item.get_feedback()){
            break;
        }
    }
}

template<uint8_t T>
void CustomCtrl<T>::transmit() {
    memcpy(static_cast<uint8_t *>(uartPlus.tx_buffer) + 7, &interact_dep::frame_send, sizeof(interact_dep::receive_data_t));
}

template<uint8_t T>
void CustomCtrl<T>::lock() {
    for (auto & item: servos) {
//        item.lock();
        item.set_pos_speed(item.angle/360.f*4096, 5);
        osDelay(1);
    }
}
template<uint8_t T>
void CustomCtrl<T>::unlock() {
    for (auto &item:servos) {
        item.unlock();
        osDelay(1);
    }
}

extern CustomCtrl<6> custom_ctrl;

#endif
