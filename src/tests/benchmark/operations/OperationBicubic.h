#ifndef PROJECT_OPERATIONBICUBIC_H
#define PROJECT_OPERATIONBICUBIC_H

#include <opencv2/opencv.hpp>
#include "../utils/OperationsCounter.h"
#include "../utils/OperationUtility.h"

using namespace cv;

template <typename Pixel>
class OperationBicubic {
public:
    static OperationBicubic<Pixel>& getInstance() {
        static OperationBicubic<Pixel> instance;
        return instance;
    }
    
    Mat zoom(const Mat_<Pixel> &source, double scale_factor);
    Mat zoom(const Mat_<Pixel> &source, double scale_factor_x, double scale_factor_y);
    
};

#include "OperationBicubic.ipp"

#endif //PROJECT_OPERATIONBICUBIC_H 