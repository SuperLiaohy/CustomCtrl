//
// Created by Administrator on 25-1-23.
//

#ifndef CUSTOMCTRL_INTERACT_H
#define CUSTOMCTRL_INTERACT_H
#include "Crc.h"
#include "CustomCtrl.hpp"
#include "SuperUart.h"
#include "array"


#ifdef __cplusplus
extern "C" {
#endif

#include "cmsis_os2.h"
#include "cmsis_os.h"
extern osThreadId_t OS_ReceiveTaskHandle;

#ifdef __cplusplus
};
#endif
namespace interact_dep {
    constexpr uint32_t SOF = 0xA5;
    struct frame_header {
        uint8_t sof;
        uint16_t data_length;
        uint8_t seq;
        uint8_t crc8;
    } __attribute__((packed));

    struct tx_status {
        uint8_t map_back_over : 1;
        uint8_t lock : 1;
        uint8_t none : 6;
    } __attribute__((packed));

    template<uint8_t T>
    struct custom_tx_frame {
        tx_status s;
        std::array<int16_t, T> joint;
    } __attribute__((packed));

    struct rx_status {
        uint8_t enable_map_back : 1;
        uint8_t lock : 1;
        uint8_t none : 6;
    } __attribute__((packed));

    template<uint8_t T>
    struct custom_rx_frame {
        rx_status s;
        std::array<int16_t, T> joint;
    } __attribute__((packed));

    struct trans_frame {
        frame_header frame_head {};
        uint16_t cmd_id {};
        uint8_t data[30] {};
        uint16_t crc16 {};
    } __attribute__((packed));

    struct receive_frame {
        frame_header frame_head {};
        uint16_t cmd_id {};
        uint8_t data[30] {};
        uint16_t crc16 {};
    } __attribute__((packed));

    float transform(float angle);
    float inverse(float angle);
    float limit(float angle, float min, float max);
} // namespace interact_dep

template<uint8_t n>
class Interact {
public:
    explicit Interact(UART_HandleTypeDef* huart)
        : uartPlus(huart, 100, 100)
        , cmd_id(0) {
        tx_frame.frame_head = {0xA5, 30, 0, 0};
        crc::append_crc8_check_sum(reinterpret_cast<uint8_t*>(&tx_frame.frame_head), sizeof(interact_dep::frame_header));
        tx_frame.cmd_id = 0x302;
    }

    interact_dep::trans_frame tx_frame;

    interact_dep::custom_rx_frame<n> frame_rx;

    void set_map_back_over(uint8_t is_over) { frame_tx.s.map_back_over = is_over; };

    void get_angle(CustomCtrl<n>& ctrl);
    void inverse_angle(CustomCtrl<n>& ctrl);
    void transmit();
    void receive(uint8_t* data);
    void get_feedback();

    friend void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef* huart, uint16_t Size);

private:
    std::array<float, n> angle;
    std::array<float, n> target;
    interact_dep::custom_tx_frame<n> frame_tx;
    uint16_t cmd_id;
    SuperUart uartPlus;
};
template<uint8_t n>
void Interact<n>::transmit() {
    memcpy(reinterpret_cast<uint8_t*>(tx_frame.data), &frame_tx, sizeof(interact_dep::custom_tx_frame<n>));
    crc::append_crc16_check_sum(reinterpret_cast<uint8_t*>(&tx_frame), sizeof(tx_frame));
    uartPlus.write_dma(reinterpret_cast<uint8_t*>(&tx_frame), sizeof(tx_frame));
}

template<uint8_t n>
void Interact<n>::receive(uint8_t* data) {
    memcpy(&frame_rx, reinterpret_cast<uint8_t*>(data), sizeof(interact_dep::custom_rx_frame<n>));
}

template<uint8_t n>
void Interact<n>::get_angle(CustomCtrl<n>& ctrl) {
    for (int i = 0; i < n; ++i) {
        angle[i]          = custom_ctrl_dep::polarity[i] * interact_dep::limit(interact_dep::transform(ctrl.servos[i].angle - custom_ctrl_dep::offset[i]), custom_ctrl_dep::min[i], custom_ctrl_dep::max[i]);
        frame_tx.joint[i] = angle[i] * scale(360, 4096);
    }
}

template<uint8_t n>
void Interact<n>::inverse_angle(CustomCtrl<n>& ctrl) {
    for (int i = 0; i < n; ++i) {
        target[i]             = interact_dep::inverse(interact_dep::limit(custom_ctrl_dep::polarity[i] * frame_rx.joint[i], custom_ctrl_dep::self_min[i], custom_ctrl_dep::self_max[i]) * scale(4096, 360)) + custom_ctrl_dep::offset[i];
        ctrl.servos[i].target = target[i] * scale(360, 4096);
    }
}

template<uint8_t n>
void Interact<n>::get_feedback() {
    auto buff = uartPlus.rx_buffer;
    if (buff[0] == interact_dep::SOF && crc::verify_crc8_check_sum(buff, sizeof(interact_dep::frame_header))) {
        uint16_t len = (buff[2] << 8 | buff[1]);
        cmd_id       = buff[6] << 8 | buff[5];
        if (crc::verify_crc16_check_sum(buff, len + 9)) {
            switch (cmd_id) {
                case 0x302:
                    receive(&buff[7]);
//                    if (frame_rx.s.enable_map_back) {
//                        set_map_back_over(0);
//                    }
                    break;
                case 0x304:
                    break;
                case 0x306:
                    break;
                case 0x309:
                    break;
                default:
                    break;
            }
            xTaskResumeFromISR((TaskHandle_t)OS_ReceiveTaskHandle);
        }
    }
}

extern Interact<6> interact;

#endif //CUSTOMCTRL_INTERACT_H
