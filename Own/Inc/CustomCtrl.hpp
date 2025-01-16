#ifndef __CUSTOM_CTRL_H
#define __CUSTOM_CTRL_H

#include "CanServos.hpp"
#include "SuperCan.hpp"

#include "array"

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
}
#endif

enum Status{
	INIT,
	OPEN,
	STOP,
};

class CustomCtrl {
public:
    CustomCtrl(SuperCan* canPlus)
        : servos{CanServos(canPlus, 1), CanServos(canPlus, 2), CanServos(canPlus, 3), CanServos(canPlus, 4), CanServos(canPlus, 5), CanServos(canPlus, 6)} {}
    std::array<CanServos, 6> servos;
		Status s;

};

#endif