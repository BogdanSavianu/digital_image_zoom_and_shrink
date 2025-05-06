#ifndef PROJECT_OPERATIONNEARESTNEIGHBOR_H
#define PROJECT_OPERATIONNEARESTNEIGHBOR_H

#include <opencv2/opencv.hpp>
#include "../utils/OperationsCounter.h"
#include "../utils/OperationUtility.h"

using namespace cv;

template <typename Pixel>
class OperationNearestNeighbor {
public:
    static OperationNearestNeighbor<Pixel>& getInstance() {
        static OperationNearestNeighbor<Pixel> instance;
        return instance;
    }
    
    Mat zoom(const Mat_<Pixel> &source, double scale_factor);
    Mat zoom(const Mat_<Pixel> &source, double scale_factor_x, double scale_factor_y);
};

#include "OperationNearestNeighbor.ipp"

#endif //PROJECT_OPERATIONNEARESTNEIGHBOR_H 