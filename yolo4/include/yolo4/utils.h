//
// Created by wsx on 2020/11/6.
//

#ifndef Y4_LIBTORCH_UTILS_H
#define Y4_LIBTORCH_UTILS_H

#include <ATen/core/TensorBody.h>
#include <iostream>
#include <opencv2/core/mat.hpp>
#include <tuple>
#include <torch/script.h>
#include <torch/optim.h>
#include <vector>

using namespace std;


class DecodeBox
{
public:

    float anchors[3][2];
    int num_anchors = 0;
    int num_classes = 0;
    int bbox_attrs = 0;
    float image_size[2];

    // 初始化构造函数
    DecodeBox(float t_anchors[][2], float t_image_size[], int t_num_anchors=3, int t_num_classes=2);
    // 
    at::Tensor find_obj(torch::Tensor input);

};

// 调整图片大小
cv::Mat letterbox_image(cv::Mat image, float size[]);

// 非极大抑制NMS
vector<at::Tensor> yolo_nms(at::Tensor output, int num_classes, float conf_thres=0.5, float nms_thres=0.4);

// 去除灰条 恢复出原始的图片大小，并标定bbox的位置
at::Tensor yolo_correct_boxes(at::Tensor box_ymin, at::Tensor box_xmin, at::Tensor box_ymax, at::Tensor box_xmax, at::Tensor model_image_size, at::Tensor src_image_size);





#endif //Y4_LIBTORCH_UTILS_H
