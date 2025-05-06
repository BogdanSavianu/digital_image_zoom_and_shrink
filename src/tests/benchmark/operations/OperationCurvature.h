#ifndef PROJECT_OPERATIONCURVATURE_H
#define PROJECT_OPERATIONCURVATURE_H

#include <opencv2/opencv.hpp>
#include "../utils/OperationsCounter.h"
#include "../utils/OperationUtility.h"

using namespace cv;

template <typename Pixel>
class OperationCurvature {
public:
    static OperationCurvature<Pixel>& getInstance() {
        static OperationCurvature<Pixel> instance;
        return instance;
    }
    
    Mat zoom(const Mat_<Pixel> &source, double scale_factor);
    Mat zoom(const Mat_<Pixel> &source, double scale_factor_x, double scale_factor_y);
};

#include "OperationCurvature.ipp"

#endif //PROJECT_OPERATIONCURVATURE_H 