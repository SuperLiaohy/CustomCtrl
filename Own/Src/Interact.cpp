//
// Created by Administrator on 25-1-23.
//

#include "Interact.h"

namespace interact_dep {
    float transform(float angle) {
        if (angle>180){
            angle -= 360;
        } else if (angle<-180){
            angle += 360;
        }
        return angle;
    }
    float inverse(float angle) {
        if (angle<0){
            angle += 360;
        }
        return angle;
    }
    float limit(float angle,float min,float max) {
        if (angle > max) {
            return max;
        } else if (angle < min) {
            return min;
        } else {
            return angle;
        }
    };
}