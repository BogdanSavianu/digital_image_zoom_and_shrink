//
// Created by Bogdan Savianu on 05.04.2025.
//

#ifndef PROJECT_RUNTESTS_H
#define PROJECT_RUNTESTS_H

#include <opencv2/opencv.hpp>
#include "../interpolation/nearest_neighbor/NearestNeighbor.h"
#include "../interpolation/bilinear/Bilinear.h"
#include "../interpolation/bicubic/Bicubic.h"
#include "../interpolation/curvature/Curvature.h"
#include "benchmark/BenchmarkAccuracy.h"
#include "benchmark/BenchmarkOperations.h"
#include "benchmark/BenchmarkTiming.h"

using namespace cv;

template <typename Pixel>
void test_nn_zoom(Mat_<Pixel> &source, const std::string &image_name);

template <typename Pixel>
void test_nn_shrink(Mat_<Pixel> &source, const std::string &image_name);

template <typename Pixel>
void test_nn_zoom_xy(Mat_<Pixel> &source, double scale_x, double scale_y, const std::string &image_name);

template <typename Pixel>
void test_nn_shrink_xy(Mat_<Pixel> &source, double scale_x, double scale_y, const std::string &image_name);

template <typename Pixel>
void test_bilinear_zoom(Mat_<Pixel> &source, const std::string &image_name);

template <typename Pixel>
void test_bilinear_shrink(Mat_<Pixel> &source, const std::string &image_name);

template <typename Pixel>
void test_bilinear_zoom_xy(Mat_<Pixel> &source, double scale_x, double scale_y, const std::string &image_name);

template <typename Pixel>
void test_bilinear_shrink_xy(Mat_<Pixel> &source, double scale_x, double scale_y, const std::string &image_name);

template <typename Pixel>
void test_bicubic_zoom(Mat_<Pixel> &source, const std::string &image_name);

template <typename Pixel>
void test_bicubic_shrink(Mat_<Pixel> &source, const std::string &image_name);

template <typename Pixel>
void test_bicubic_zoom_xy(Mat_<Pixel> &source, double scale_x, double scale_y, const std::string &image_name);

template <typename Pixel>
void test_bicubic_shrink_xy(Mat_<Pixel> &source, double scale_x, double scale_y, const std::string &image_name);

template <typename Pixel>
void test_curvature_zoom(Mat_<Pixel> &source, const std::string &image_name);

template <typename Pixel>
void test_curvature_shrink(Mat_<Pixel> &source, const std::string &image_name);

template <typename Pixel>
void test_curvature_zoom_xy(Mat_<Pixel> &source, double scale_x, double scale_y, const std::string &image_name);

template <typename Pixel>
void test_curvature_shrink_xy(Mat_<Pixel> &source, double scale_x, double scale_y, const std::string &image_name);

enum class BenchmarkType {
    ACCURACY,
    OPERATIONS,
    TIMING
};

template <typename Pixel>
void benchmark_accuracy(const Mat_<Pixel> &source, double scale_factor);

template <typename Pixel>
void benchmark_accuracy_xy(const Mat_<Pixel> &source, double scale_factor_x, double scale_factor_y);

template <typename Pixel>
void benchmark_operations(const Mat_<Pixel> &source, double scale_factor);

template <typename Pixel>
void benchmark_operations_xy(const Mat_<Pixel> &source, double scale_factor_x, double scale_factor_y);

template <typename Pixel>
void benchmark_timing(const Mat_<Pixel> &source, double scale_factor);

template <typename Pixel>
void benchmark_timing_xy(const Mat_<Pixel> &source, double scale_factor_x, double scale_factor_y);

int select_image_console();

std::vector<double> get_custom_scales(const std::string &scale_type);

bool get_non_uniform_test_choice();

std::pair<double, double> get_non_uniform_scales(const std::string &scale_type);

template <typename Pixel>
void run_tests_with_scales(Mat_<Pixel> &source, const std::string &image_name, 
                          const std::vector<bool> &selected_methods,
                          const std::vector<double> &zoom_scales,
                          const std::vector<double> &shrink_scales,
                          bool test_non_uniform = false,
                          std::pair<double, double> non_uniform_zoom = {2.0, 1.5},
                          std::pair<double, double> non_uniform_shrink = {0.5, 0.75});

template<typename Pixel>
void run_benchmarks_for_image(const Mat_<Pixel> &source, BenchmarkType type);

void run_benchmarks(BenchmarkType type);

void run_tests();

#include "RunTests.ipp"

#endif //PROJECT_RUNTESTS_H
