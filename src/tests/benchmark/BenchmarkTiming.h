//
// Created by Bogdan Savianu on 02.05.2025.
//

#ifndef PROJECT_BENCHMARKTIMING_H
#define PROJECT_BENCHMARKTIMING_H

#include <opencv2/opencv.hpp>
#include <iostream>
#include <iomanip>
#include <chrono>

using namespace cv;

template <typename Pixel>
void benchmark_timing(const Mat_<Pixel> &source, double scale_factor);

template <typename Pixel>
void benchmark_timing_xy(const Mat_<Pixel> &source, double scale_factor_x, double scale_factor_y);

#include "BenchmarkTiming.ipp"

#endif //PROJECT_BENCHMARKTIMING_H 