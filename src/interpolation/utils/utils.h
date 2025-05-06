//
// Created by Bogdan Savianu on 05.04.2025.
//

#ifndef PROJECT_UTILS_H
#define PROJECT_UTILS_H

#include <opencv2/opencv.hpp>

using namespace cv;

template<typename Pixel>
inline bool is_inside(Point p, const Mat_<Pixel> &source);

#endif //PROJECT_UTILS_H

#include "utils.ipp"