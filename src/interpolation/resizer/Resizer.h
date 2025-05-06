//
// Created by Bogdan Savianu on 05.04.2025.
//

#ifndef PROJECT_RESIZER_H
#define PROJECT_RESIZER_H
#include <opencv2/opencv.hpp>

using namespace cv;

template<typename Pixel>
class Resizer {
public:
    virtual ~Resizer() = default;

    virtual Mat zoom(const Mat_<Pixel> &source, double scale_factor) = 0;
    virtual Mat shrink(const Mat_<Pixel> &source, double scale_factor) = 0;
    
    virtual Mat zoom(const Mat_<Pixel> &source, double scale_factor_x, double scale_factor_y) = 0;
    virtual Mat shrink(const Mat_<Pixel> &source, double scale_factor_x, double scale_factor_y) = 0;
};



#endif //PROJECT_RESIZER_H
