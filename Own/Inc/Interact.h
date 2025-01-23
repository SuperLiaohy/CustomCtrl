//
// Created by Administrator on 25-1-23.
//

#ifndef CUSTOMCTRL_INTERACT_H
#define CUSTOMCTRL_INTERACT_H
#include "SuperUart.h"
#include "CanServos.hpp"
#include "crc.h"
namespace interact_dep {
    typedef struct link_receive {
        int16_t angle;
        //        int16_t speed;
    } __attribute__((packed)) link_receive_t;

    typedef struct link_transmit {
        int16_t angle;
        //        int16_t speed;
    } __attribute__((packed)) link_transmit_t;

    enum INTERACTION {
        NONE,
        CUSTOM,
        REMOTE_CTRL_RESET,
    };

    struct receive_data_t {
        link_receive_t joint1;
        link_receive_t joint2;
        link_receive_t joint3;
        link_receive_t joint4;
        link_receive_t joint5;
        link_receive_t joint6;
    } __attribute__((packed));

    struct transmit_data_t {
        link_transmit_t joint1;
        link_transmit_t joint2;
        link_transmit_t joint3;
        link_transmit_t joint4;
        link_transmit_t joint5;
        link_transmit_t joint6;
    } __attribute__((packed));

    constexpr uint8_t SOF = 0xA5; // 帧头

    struct frame_header
    {
        uint8_t sof;
        uint16_t data_length;
        uint8_t seq;
        uint8_t crc8;
    } __attribute__((packed));


    constexpr struct {
        frame_header frame_head_send;
        uint16_t cmd_id;
    } __attribute__((packed)) frame_send = {
        .frame_head_send = {
            .sof = SOF,
            .data_length = 30,
            .seq = 0,
            .crc8 = 125,
        },
        .cmd_id = 0x0302,
    };
}

//class Interact {
//public:
//    Interact(UART_HandleTypeDef *huart) : uartPlus(huart, 100, 100) {
//              memcpy(uartPlus.tx_buffer, &interact_dep::frame_send, sizeof(interact_dep::receive_data_t));
//    }
//    SuperUart uartPlus;
//
//    void transmit(CanServos);
//};

#endif //CUSTOMCTRL_INTERACT_H
