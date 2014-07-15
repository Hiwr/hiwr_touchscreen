/*********************************************************************
*
*
* Copyright 2014 Worldline
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
* 
*     http://www.apache.org/licenses/LICENSE-2.0
* 
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
* 
***********************************************************************/

#include "hiwr_touchscreen.h"

using namespace std;

HiwrTouchscreen::HiwrTouchscreen(ros::NodeHandle & n):
    nh_(n)
{}

void HiwrTouchscreen::loop(){
    ROS_INFO("hiwr_touchscreen started");

    touch_pub_ = nh_.advertise<hyve_msg::TouchEvent>("hiwr_touchscreen/touch_event", 1);

    struct tsdev *ts;

    ts = ts_open("/dev/input/event0",0);
    if (!ts) {
        ts = ts_open("/dev/input/event1",0);
    }
    if (!ts) {
        ts = ts_open("/dev/input/event2",0);
    }
    if (!ts) {
        ROS_INFO("ts_open");
        perror("ts_open");
        exit(1);
    }

    if (ts_config(ts)) {
        ROS_INFO("ts_config");
        perror("ts_config");
        exit(1);
    }


    ROS_DEBUG("will begin Loop");
    while(ros::ok()) {
        ROS_DEBUG("Looping");
        struct ts_sample samp;
        int ret;

        ROS_DEBUG("before ts_read");
        ret = ts_read(ts, &samp, 1);
        ROS_DEBUG("after ts_read");

        if (ret < 0) {
            ROS_INFO("ts_read");
            perror("ts_read");
            exit(1);
        }

        if (ret != 1) {
            ROS_INFO("ts_read != 1");
            continue;
        }

        touchEvent_.x = samp.x;
        touchEvent_.y = samp.y;
        touchEvent_.pressed = (samp.pressure>0)? true : false;

        //if(touchEvent.pressed && (touchEvent.x<100 || touchEvent.x>700 || touchEvent.y<50 || touchEvent.y>400))
        //    touchEvent.pressed = false;

        touch_pub_.publish(touchEvent_);

        ROS_INFO("x: %6d y: %6d pressed:%s\n", samp.x, samp.y, ((samp.pressure>0)?"True" : "False"));
    }
}


int main(int argc, char **argv)
{
    ros::init(argc, argv, "hiwr_touchscreen");
    ros::NodeHandle n;
    HiwrTouchscreen node(n);
    node.loop();
}
