//
// Created by liaohy on 9/5/24.
//

#ifndef NONE_PRJ_SUPERCAN_H
#define NONE_PRJ_SUPERCAN_H

#ifdef __cplusplus
extern "C" {
#endif

#include "can.h"
#include "stm32f4xx_hal.h"


#ifdef __cplusplus
}
#endif

enum filter_mode {
    MASK_16,
    MASK_32,
    LIST_16,
    LIST_32
};

class SuperCan {
public:
    SuperCan(CAN_HandleTypeDef* hcan, uint32_t fifo, uint32_t fifo_start);
    ~SuperCan() = default;

    void filter_config(uint16_t filter_number, filter_mode filterMode = MASK_32, uint32_t reg_1 = 0, uint32_t reg_2 = 0);

    void can_start();

    void write(const uint8_t* data) {
        for (int i = 0; i < 8; i++) {
            tx_data[i] = data[i];
        }
    }

    void write(int16_t data1, int16_t data2, int16_t data3, int16_t data4) {
        tx_data[0] = (data1 >> 8) & 0xff;
        tx_data[1] = (data1) & 0xff;
        tx_data[2] = (data2 >> 8) & 0xff;
        tx_data[3] = (data2) & 0xff;
        tx_data[4] = (data3 >> 8) & 0xff;
        tx_data[5] = (data3) & 0xff;
        tx_data[6] = (data4 >> 8) & 0xff;
        tx_data[7] = (data4) & 0xff;
    }

    void send(uint32_t id, uint8_t* data);

    void send(uint32_t id) {
        tx_header.StdId = id;
        tx_header.IDE   = CAN_ID_STD;
        tx_header.DLC   = 8;
        tx_header.RTR   = CAN_RTR_DATA;
        if (HAL_CAN_AddTxMessage(hcan, &tx_header, tx_data, (uint32_t*)CAN_TX_MAILBOX0)) {
            if (HAL_CAN_AddTxMessage(hcan, &tx_header, tx_data, (uint32_t*)CAN_TX_MAILBOX1)) {
                if (HAL_CAN_AddTxMessage(hcan, &tx_header, tx_data, (uint32_t*)CAN_TX_MAILBOX2)) {
                    return;
                }
            }
        }
    };

    void receive() {
        HAL_CAN_GetRxMessage(hcan, fifo, &rx_header, rx_data);
    }

    CAN_RxHeaderTypeDef* read_header() {
        return &rx_header;
    }

    uint8_t* read() {
        return rx_data;
    }

    friend void ::HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef* hcan);
    friend void ::HAL_CAN_RxFifo1MsgPendingCallback(CAN_HandleTypeDef* hcan);
    CAN_RxHeaderTypeDef rx_header;
private:
    uint32_t fifo;
    uint32_t fifo_start;

    CAN_HandleTypeDef* hcan;
    CAN_TxHeaderTypeDef tx_header;


    uint8_t tx_data[8];

    uint8_t rx_data[8];
};

extern SuperCan canPlus1;

#endif //NONE_PRJ_SUPERCAN_H
