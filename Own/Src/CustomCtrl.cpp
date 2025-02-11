#include "CustomCtrl.hpp"

namespace custom_ctrl_dep {
    float transform(float angle) {
        if (angle>180){
            angle -= 360;
        } else if (angle<-180){
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
custom_frame frame;
custom_frame rx_frame;

