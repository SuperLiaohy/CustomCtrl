#include "CanServos.hpp"

void CanServos::read() const {
    uint8_t data[8] = {0x01, 0, 0, 0, 0, 0, 0, 0};
    canPlus->send(id, data);
}
void CanServos::lock() const {
    uint8_t data[8] = {0x11, 0, 0, 0, 0, 0, 0, 1};
    canPlus->send(id, data);
}
void CanServos::unlock() const {
    uint8_t data[8] = {0x2f, 0, 0, 0, 0, 0, 0, 0};
    canPlus->send(id, data);
}
