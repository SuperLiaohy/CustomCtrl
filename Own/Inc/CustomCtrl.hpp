#ifndef __CUSTOM_CTRL_H
#define __CUSTOM_CTRL_H

#include "CanServos.hpp"
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
namespace custom_ctrl_dep {
    constexpr std::array<float, 6> offset = {173.671875, 85.2539062, 213.925781, 4.48242188, 0.263671875, 5.53710938};
    constexpr std::array<float, 6> min    = {-45, -55, -145, -180, -90, -180};
    constexpr std::array<float, 6> max    = {45, 55, 145, 180, 90, 180};
    constexpr std::array<float, 6> self_min    = {-45, -50, -120, -180, -90, -180};
    constexpr std::array<float, 6> self_max    = {45, 90, 120, 180, 90, 180};
    constexpr std::array<int8_t, 6> polarity = {1, 1, 1, 1, -1, -1};
    enum class Status {
        INIT,
        OPEN,
        STOP,
    };

} // namespace custom_ctrl_dep


template<uint8_t T>
class CustomCtrl {
public:
    CustomCtrl() : s(custom_ctrl_dep::Status::INIT) {}

    std::array<CanServos, T> servos;
    custom_ctrl_dep::Status s;

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
    void back_map();
    void get_feedback();

private:
};
template<uint8_t T>
void CustomCtrl<T>::back_map() {
    for (int i = 0; i < 3; ++i) {
        servos[i].set_pos_speed(servos[i].target, 100);;
        osDelay(1);
    }
    // for (auto & item: servos) {
        // item.set_pos_speed(item.target, 100);
        // osDelay(1);
    // }
}

template<uint8_t T>
void CustomCtrl<T>::read() {
    for (auto& item: servos) {
        item.read();
        osDelay(1);
    }
}

template<uint8_t T>
void CustomCtrl<T>::get_feedback() {
    for (auto& item: servos) {
        if (item.get_feedback()) {
            break;
        }
    }
}

template<uint8_t T>
void CustomCtrl<T>::lock() {
    for (auto& item: servos) {
                item.lock();
//        item.set_pos_speed(item.angle / 360.f * 4096, 50);
        osDelay(1);
    }
}
template<uint8_t T>
void CustomCtrl<T>::unlock() {
    for (auto& item: servos) {
        item.unlock();
        osDelay(1);
    }
}

extern CustomCtrl<6> custom_ctrl;

#endif
