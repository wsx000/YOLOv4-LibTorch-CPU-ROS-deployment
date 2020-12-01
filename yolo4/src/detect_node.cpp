#include "yolo.h"
#include "utils.h"
#include "ros/ros.h"
#include "std_msgs/String.h"
#include "yolo4/box.h"
#include "opencv2/opencv.hpp"
#include <opencv2/highgui.hpp>
#include <opencv2/videoio.hpp>
#include "vector"
#include "std_msgs/Float32MultiArray.h"


using namespace std;

int main(int argc, char **argv)
{

    // ros节点初始化
    ros::init(argc, argv, "detect");

    // 创建节点句柄
    ros::NodeHandle n;
    // 初始化YOLO
    const char* modulePath = "/home/wsx/code/YOLOv4/y4-libtorch-V1-20201120/model-traced.pt";
    YOLO yolo(modulePath);

    // 初始化摄像头
    cv::VideoCapture cap(0);
    if(!cap.isOpened())
    {
        ROS_ERROR_STREAM("failed to open video device\n");
        ros::shutdown();
    }
    else
    {
        //设置frame格式
        // cap.set(CV_CAP_PROP_FRAME_WIDTH,608); 
        // cap.set(CV_CAP_PROP_FRAME_HEIGHT,608); 
        // cap.set(CV_CAP_PROP_FOURCC,CV_FOURCC('M','J','P','G')); 
        // cap.set(CV_CAP_PROP_FPS, 25);
    }
    
    // 读取视频帧
    cv::Mat frame;

    // 创建一个Publisher，发布名为boxes的topic，消息类型为
    ros::Publisher boxes_pub = n.advertise<yolo4::box>("boxes", 3);

    // 设置循环的频率  25帧
    // ros::Rate loop_rate(25);

    while (ros::ok())
    {
        yolo4::box msg;
        // 读取摄像头
        cap >> frame;
        // cv::imshow("a", frame);
        // cv::waitKey(1);

        std::vector<vector<float>> out_boxes = yolo.detect_image(frame);
        // 1维目标消息数组
        std::vector<float> out;
        for(int i=0; i<out_boxes.size(); i++)
        {
            for(int j=0; j<6; j++)
            {
                out.emplace_back(out_boxes[i][j]);
            }
        }
        // 发布话题
        msg.boxes_num = out_boxes.size();
        msg.boxes = out;
        boxes_pub.publish(msg);
        // 画框框
        yolo.draw_rectangle(out_boxes, frame);
    }
    cap.release();
    cv::destroyAllWindows();
    
}




