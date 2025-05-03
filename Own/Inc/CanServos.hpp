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

consteval float scale(float src, float head) {
    return head / src;
}
constexpr float scale(float src_data, float src, float head) {
    return src_data * head / src;
}

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

    uint16_t target;
    float angle;

    static void read_all(); //广播读取位置，只挂载一个舵机，这样可以获取舵机的ID

    void read() const; //读取位置

    void unlock() const; //解锁

    void lock() const; //锁定

    inline void read_idcard(); //读取ID卡

    inline void change_id(uint8_t new_id); //修改ID
    inline void read_id();
    inline void set_pos_speed(uint16_t pos, uint16_t speed); //设置速度
    void test(uint8_t cmd, int16_t pos, int16_t speed, uint8_t a, uint8_t b, uint8_t c ); //测试

    inline bool get_feedback(); //获取反馈

    static SuperCan* canPlus;

private:
    const std::array<uint8_t, 4> idcard;
};

inline void CanServos::read_all() {
    uint8_t data[8] = {0x01, 0, 0, 0, 0, 0, 0, 0};
    canPlus->send(0x00, data);
};


inline bool CanServos::get_feedback() {
    auto data = canPlus->read();
    if (canPlus->read_header()->StdId == id) {
        switch (data[0]) {
            case 0x02:
                angle = (data[1] | (data[2] << 8)) * scale(4096, 360);
                break;
            case 0x07:
                //                idcard[0] = data[1];
                //                idcard[1] = data[2];
                //                idcard[2] = data[3];
                //                idcard[3] = data[4];
                break;
        }
        return true;
    }
    return false;
}

void CanServos::change_id(uint8_t new_id) {
    uint8_t data[8] = {0x07, new_id, idcard[0], idcard[1], idcard[2], idcard[3], 0, 0};
    canPlus->send(id, data);
    id = new_id;
}
void CanServos::read_id() {
    id = canPlus->rx_header.StdId;
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