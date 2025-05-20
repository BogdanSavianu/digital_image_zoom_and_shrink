//
// Created by Bogdan Savianu on 02.05.2025.
//

#ifndef PROJECT_BENCHMARKOPERATIONS_H
#define PROJECT_BENCHMARKOPERATIONS_H

#include <opencv2/opencv.hpp>
#include <iostream>
#include <iomanip>
#include <vector>
#include "utils/OperationsCounter.h"
#include "utils/OperationUtility.h"
#include "operations/OperationNearestNeighbor.h"
#include "operations/OperationBilinear.h"
#include "operations/OperationBicubic.h"
#include "operations/OperationCurvature.h"

using namespace cv;

template <typename Pixel>
void benchmark_operations(const Mat_<Pixel> &source, double scale_factor);

template <typename Pixel>
void benchmark_operations_xy(const Mat_<Pixel> &source, double scale_factor_x, double scale_factor_y);

static constexpr const unsigned int timeout = 120;

#include "BenchmarkOperations.ipp"

#endif //PROJECT_BENCHMARKOPERATIONS_H 