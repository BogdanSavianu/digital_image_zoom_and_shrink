//
// Created by Bogdan Savianu on 02.05.2025.
//

#ifndef PROJECT_BENCHMARKACCURACY_H
#define PROJECT_BENCHMARKACCURACY_H

#include <opencv2/opencv.hpp>
#include <iostream>
#include <iomanip>

using namespace cv;

template <typename Pixel>
double calculate_accuracy_pixel_by_pixel(const Mat_<Pixel> &result, const Mat_<Pixel> &opencv_result);

template <typename Pixel>
double calculate_accuracy_mse(const Mat_<Pixel> &result, const Mat_<Pixel> &opencv_result);

template <typename Pixel>
void benchmark_accuracy(const Mat_<Pixel> &source, double scale_factor);

template <typename Pixel>
void benchmark_accuracy_xy(const Mat_<Pixel> &source, double scale_factor_x, double scale_factor_y);

#include "BenchmarkAccuracy.ipp"

#endif //PROJECT_BENCHMARKACCURACY_H 