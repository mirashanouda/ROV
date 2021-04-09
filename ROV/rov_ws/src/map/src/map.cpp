#include <ros/ros.h>
#include <sensor_msgs/Joy.h>
#include <std_msgs/String.h>
#include "std_msgs/Float64.h"
#include <std_msgs/Bool.h>
#include <stdio.h>
#include <string.h>
#include <cstring>
#include <sstream>
#include <stdlib.h>
#include <string>

#define motorA motor_def_D
#define motorB motor_def_A
#define motorC motor_def_E
#define motorD motor_def_B
#define motorE motor_def_C
#define motorF motor_def_F

class mapper
{
public:
    mapper();
    void publish();

private:
    void joyCallback(const sensor_msgs::Joy::ConstPtr &joy);

    ros::NodeHandle nh;
    ros::Publisher rovpub;
    ros::Subscriber joysub;
};

mapper::mapper()
{
    rovpub = nh.advertise<std_msgs::String>("motor_values", 1000);

    joysub = nh.subscribe<sensor_msgs::Joy>("joy", 1000, &mapper::joyCallback, this);
}

int motorA = 1500, motorB = 1500, motorC = 1500, motorD = 1500, motorE = 1500, motorF = 1500;
std_msgs::String msg; //this one will be delivered to the serial node

std::stringstream ss;

void x_move(const sensor_msgs::Joy::ConstPtr &x)
{
    motorA = 1500 + x->axes[0] * 300;
    motorB = 1500 + x->axes[0] * -300;
    motorC = 1500 + x->axes[0] * 300;
    motorD = 1500 + x->axes[0] * -300;
}

void y_move(const sensor_msgs::Joy::ConstPtr &y)
{
    motorA = 1500 + y->axes[1] * 300;
    motorB = 1500 + y->axes[1] * 300;
    motorC = 1500 + y->axes[1] * 300;
    motorD = 1500 + y->axes[1] * 300;
}

void z_move(const sensor_msgs::Joy::ConstPtr &z)
{
    motorE = 1500 + z->axes[2] * 300;
    motorF = 1500 + z->axes[2] * 300;
}

void concatenate_values()
{
    ss << "A" << motor_def_A << "B" << motor_def_B << "C" << motor_def_C << "D" << motor_def_D << "E" << motor_def_E;
    //"F" << buffer << "G" << arm_button << piston_button << led_button << ph << "X" << l_buffer << "Y" << r_buffer << "K";
    msg.data = ss.str();
}

void mapper::joyCallback(const sensor_msgs::Joy::ConstPtr &joy)
{
    if (joy->axes[0] != 0)
    {
        x_move(joy);

        ROS_INFO_STREAM("right-left");
    }
    else if (joy->axes[1] != 0)
    {
        y_move(joy);
        ROS_INFO_STREAM("forward-backward");
    }
    else if (joy->axes[2] != 0)
    {
        z_move(joy);
        ROS_INFO_STREAM("up-down");
    }
    else
    {
        motorA = 1500;
        motorB = 1500;
        motorC = 1500;
        motorD = 1500;
        motorE = 1500;
        motorF = 1500;
    }

    concatenate_values();
    rovpub.publish(msg);
}

void chatterCallback(const std_msgs::String::ConstPtr &msg)
{
    ROS_INFO("I heassrd: [%s]", msg->data.c_str());
}

int main(int argc, char** argv)
{
    ros::init(argc, argv, "map_motors");

    ROS_INFO_STREAM("Executing main");
    mapper map_main;

    ros::NodeHandle nh("~");

    ros::spin();
    return 0;
}