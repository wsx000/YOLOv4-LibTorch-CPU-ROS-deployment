#include <cv_bridge/cv_bridge.h>
#include <image_transport/image_transport.h>
#include <opencv2/highgui/highgui.hpp>
#include <ros/ros.h>
#include <sensor_msgs/image_encodings.h>
#include "yolo4/box.h"


// 回调函数
void callback(const yolo4::box::ConstPtr& msg)
{
    ROS_INFO("received obj info: [%d]", msg->boxes_num);
    for(int i=0; i<msg->boxes_num; i++)
    {
        for(int j=0;j<6;j++)
        {
            ROS_INFO("received obj coor info: [%f]", msg->boxes[i*6 + j]);
        }
        
    }
}


int main(int argc, char **argv)
{
    ros::init(argc, argv, "obj_sub_node");

    ros::NodeHandle nh;

    ros::Subscriber sub = nh.subscribe("boxes", 3, callback);
    // 新消息到达时会尽快调用回调函数处理，ros::spin在ros::ok()返回false时退出
    ros::spin();

    return 0;

}






