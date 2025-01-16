//
// Created by liaohy on 9/5/24.
//

#include "SuperCan.hpp"

SuperCan::SuperCan(CAN_HandleTypeDef* hcan, uint32_t fifo,
                   uint32_t fifo_start) {
    this->hcan       = hcan;
    this->fifo       = fifo;
    this->fifo_start = fifo_start;
}

void SuperCan::filter_config(uint16_t filter_number, filter_mode filterMode,
                             uint32_t reg_1, uint32_t reg_2) {
    CAN_FilterTypeDef sFilterConfig;
    switch (filterMode) {
        case MASK_16:
            sFilterConfig.FilterMode  = CAN_FILTERMODE_IDMASK;
            sFilterConfig.FilterScale = CAN_FILTERSCALE_16BIT;
            break;
        case MASK_32:
            sFilterConfig.FilterMode  = CAN_FILTERMODE_IDMASK;
            sFilterConfig.FilterScale = CAN_FILTERSCALE_32BIT;
            break;
        case LIST_16:
            sFilterConfig.FilterMode  = CAN_FILTERMODE_IDLIST;
            sFilterConfig.FilterScale = CAN_FILTERSCALE_16BIT;
            break;
        case LIST_32:
            sFilterConfig.FilterMode  = CAN_FILTERMODE_IDLIST;
            sFilterConfig.FilterScale = CAN_FILTERSCALE_32BIT;
            break;
        default:
            break;
    }
    sFilterConfig.FilterIdHigh         = reg_1 >> 16;
    sFilterConfig.FilterIdLow          = reg_1 & 0x0000FFFF;
    sFilterConfig.FilterMaskIdHigh     = reg_2 >> 16;
    sFilterConfig.FilterMaskIdLow      = reg_2 & 0x0000FFFF;
    sFilterConfig.FilterFIFOAssignment = fifo;
    sFilterConfig.FilterActivation     = ENABLE;
    sFilterConfig.FilterBank           = filter_number;
    HAL_CAN_ConfigFilter(hcan, &sFilterConfig);
}

void SuperCan::can_start() {
    HAL_CAN_ActivateNotification(hcan, fifo_start);
    HAL_CAN_Start(hcan);
}

void SuperCan::send(uint32_t id, uint8_t* data) {
    tx_header.StdId = id;
    tx_header.IDE   = CAN_ID_STD;
    tx_header.DLC   = 8;
    tx_header.RTR   = CAN_RTR_DATA;
    if (HAL_CAN_AddTxMessage(hcan, &tx_header, data,
                             (uint32_t*)CAN_TX_MAILBOX0)) {
        if (HAL_CAN_AddTxMessage(hcan, &tx_header, data,
                                 (uint32_t*)CAN_TX_MAILBOX1)) {
            if (HAL_CAN_AddTxMessage(hcan, &tx_header, data,
                                     (uint32_t*)CAN_TX_MAILBOX2)) {
                return;
            }
        }
    }
}

SuperCan canPlus1(&hcan1, CAN_RX_FIFO0, CAN_IT_RX_FIFO0_MSG_PENDING);
//    __weak SuperCan canPlus2(&hcan2);

#ifdef __cplusplus
extern "C" {
#endif
#include "FreeRTOS.h"
#include "cmsis_os.h"
#ifdef __cplusplus
}
#endif

void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef* hcan) {
    static BaseType_t pxHigherPriorityTaskWoken = pdFALSE;
    if (hcan == canPlus1.hcan) {
    }
}
