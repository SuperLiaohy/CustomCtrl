#ifndef __CAN_SERVOS_H
#define __CAN_SERVOS_H

#include "Detect.h"
#include "SuperCan.hpp"

#include "array"
#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
}
#endif

class CanServos {
public:
    CanServos(uint8_t id, std::array<uint8_t, 4> id_card = {0, 0, 0, 0})
        : id(id)
        , detect(500)
        , idcard(id_card) {}
    CanServos()
        : id(0)
        , detect(500)
        , idcard({0, 0, 0, 0}) {};
    uint8_t id;

    Detect detect;

    float angle;

    static void read_all(); //广播读取位置，只挂载一个舵机，这样可以获取舵机的ID

    inline void read(); //读取位置

    inline void unlock(); //解锁

    inline void lock(); //锁定

    inline void read_idcard(); //读取ID卡

    inline void change_id(uint8_t new_id); //修改ID

    inline void set_pos_speed(uint16_t pos, uint16_t speed); //设置速度

    inline void get_feedback(); //获取反馈

    static SuperCan* canPlus;

private:
    const std::array<uint8_t, 4> idcard;
};

inline void CanServos::read_all() {
    uint8_t data[8] = {0x01, 0, 0, 0, 0, 0, 0, 0};
    canPlus->send(0x00, data);
};

inline void CanServos::read() {
    uint8_t data[8] = {0x01, 0, 0, 0, 0, 0, 0, 0};
    canPlus->send(id, data);
}

inline void CanServos::get_feedback() {
    auto data = canPlus->read();
    if (data[0] == 0x02) {
        int16_t temp = (data[2] << 8) | data[1];
        angle        = temp * 360.f / 4096.f;
    }
}
void CanServos::unlock() {
    uint8_t data[8] = {0x2f, 0, 0, 0, 0, 0, 0, 0};
    canPlus->send(id, data);
}
void CanServos::lock() {
    uint8_t data[8] = {0x11, 0, 0, 0, 0, 0, 0, 1};
    canPlus->send(id, data);
}
void CanServos::change_id(uint8_t new_id) {
    uint8_t data[8] = {0x07, new_id, idcard[0], idcard[1], idcard[2], idcard[3], 0, 0};
    canPlus->send(id, data);
    id = new_id;
}
void CanServos::read_idcard() {
    uint8_t data[8] = {0x07, 0, 0, 0, 0, 0, 0, 0};
    canPlus->send(id, data);
}
void CanServos::set_pos_speed(uint16_t pos, uint16_t speed) {
    uint8_t data[8] = {0x03,
                       static_cast<uint8_t>((pos & 0xff)), static_cast<uint8_t>((pos >> 8)),
                       static_cast<uint8_t>((speed & 0xff)), static_cast<uint8_t>((speed >> 8)),
                       0, 0, 0};
    canPlus->send(id, data);
}

extern CanServos servos;

#endif