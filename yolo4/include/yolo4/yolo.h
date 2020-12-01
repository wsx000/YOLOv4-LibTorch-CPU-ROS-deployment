#ifndef _YOLO_H_
#define _YOLO_H_


#include "opencv2/opencv.hpp"
#include "torch/script.h"
//#include "torch/nn.h"
#include "vector"
#include <ATen/core/TensorBody.h>
#include <opencv2/core/mat.hpp>
#include "utils.h"

using namespace std;

class YOLO  
{
public:
    // 模型
    torch::jit::script::Module module;
    // 先验框
    float all_anchors[3][3][2] = {{{142, 110}, {192, 243}, {459, 401}},
                              {{36,   75}, {76,   55}, {72,  146}},
                              {{12,   16}, {19,   36}, {40,   28}}};
    // 图片大小
    float model_image_size[2] = {608, 608};
    // 类别
    vector<string> class_names = {"urchin", "trepang"};
    // 构造函数
    YOLO(const char* modelPath);
    // 目标检测
    vector<vector<float>> detect_image(cv::Mat image);
    // 根据检测结果画框
    void draw_rectangle(vector<vector<float>> output, cv::Mat img);

};




#endif

