//
// Created by Administrator on 25-1-23.
//
#include "../Task/CppTask.h"
#include "CustomCtrl.hpp"
#include "Button.h"
uint8_t tx_data[30];

struct frame_header
{
    uint8_t sof;
    uint16_t data_length;
    uint8_t seq;
    uint8_t crc8;
} __attribute__((packed));
struct trans_frame
{
    frame_header frame_head;
    uint16_t cmd_id;
    uint8_t data[30]{};
    uint16_t crc16;
} __attribute__((packed)) tx_frame;

extern "C" void TransmitTask(void* argument) {
    tx_frame.frame_head = {0xA5, 30, 0, 0};
    crc::append_crc8_check_sum(reinterpret_cast<uint8_t*>(&tx_frame.frame_head), sizeof(frame_header));
    tx_frame.cmd_id = 0x302;
    for (;;) {
        custom_ctrl.get_angle();
        memcpy(static_cast<uint8_t*>(tx_frame.data), &frame, sizeof(frame));
        crc::append_crc16_check_sum(reinterpret_cast<uint8_t*>(&tx_frame), sizeof(tx_frame));
        HAL_UART_Transmit_DMA(&huart6, reinterpret_cast<uint8_t*>(&tx_frame), sizeof(tx_frame));
        osDelay(33);
    }
}