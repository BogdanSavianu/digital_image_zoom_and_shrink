//
// Created by Bogdan Savianu on 05.04.2025.
//

#include <opencv2/opencv.hpp>

template<typename Pixel>
inline bool is_inside(Point p, const Mat_<Pixel> &source){
    return p.x >= 0 && p.y >= 0 && p.x < source.cols && p.y < source.rows;
}