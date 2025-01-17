#ifndef __CAN_SERVOS_H
#define __CAN_SERVOS_H

#include "SuperCan.hpp"
#include "Detect.h"
#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
}
#endif

class CanServos {
public:
    CanServos(uint8_t id)
        : id(id), detect(500) {}
    CanServos() : id(0), detect(500) {};
    uint8_t id;

    Detect detect;

    float angle;

    static void read_all(); //广播读取位置，只挂载一个舵机，这样可以获取舵机的ID

    inline void get_feedback(); //获取反馈

    static SuperCan* canPlus;
private:
};

inline void CanServos::read_all() {
    uint8_t data[8] = {0x01, 0, 0, 0, 0, 0, 0, 0};
    canPlus->send(0x00, data);
};

inline void CanServos::get_feedback() {
    auto data = canPlus->read();
    if (data[0] == 0x02) {
        int16_t temp = (data[2] << 8) | data[1];
        angle        = temp * 360.f / 4096.f;
    }
}

#endif