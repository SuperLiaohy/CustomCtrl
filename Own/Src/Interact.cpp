//
// Created by Administrator on 25-1-23.
//

#include "Interact.h"

namespace interact_dep {

    float transform(float angle) {
        if (angle > 180) {
            angle -= 360;
        } else if (angle < -180) {
            angle += 360;
        }
        return angle;
    }

    float inverse(float angle, float offset) {
        if (offset < 180) {
            if (-180 <= angle && angle < -offset) { angle += 360; }
        } else {
            if (360 - offset < angle && angle <= 180) { angle -= 360; }
        }
        return angle+offset;
    }

    float limit(float angle, float min, float max) {
        if (angle > max) {
            return max;
        } else if (angle < min) {
            return min;
        } else {
            return angle;
        }
    };
} // namespace interact_dep