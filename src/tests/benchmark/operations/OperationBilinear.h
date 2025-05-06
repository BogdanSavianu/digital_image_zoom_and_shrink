#ifndef PROJECT_OPERATIONBILINEAR_H
#define PROJECT_OPERATIONBILINEAR_H

#include <opencv2/opencv.hpp>
#include "../utils/OperationsCounter.h"
#include "../utils/OperationUtility.h"

using namespace cv;

template <typename Pixel>
class OperationBilinear {
public:
    static OperationBilinear<Pixel>& getInstance() {
        static OperationBilinear<Pixel> instance;
        return instance;
    }
    
    Mat zoom(const Mat_<Pixel> &source, double scale_factor);
    Mat zoom(const Mat_<Pixel> &source, double scale_factor_x, double scale_factor_y);
};

#include "OperationBilinear.ipp"

#endif //PROJECT_OPERATIONBILINEAR_H 