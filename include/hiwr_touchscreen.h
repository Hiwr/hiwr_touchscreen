#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tslib.h"

#include "ros/ros.h"
#include "hyve_msg/TouchEvent.h"


class HiwrTouchscreen{

private:
    ros::NodeHandle nh_;

    hyve_msg::TouchEvent touchEvent_;
    ros::Publisher  touch_pub_;
public:
    HiwrTouchscreen(ros::NodeHandle &);
    void loop();

};
