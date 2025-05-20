//
// Created by Bogdan Savianu on 02.05.2025.
//

#include "BenchmarkAccuracy.h"
#include "../../interpolation/nearest_neighbor/NearestNeighbor.h"
#include "../../interpolation/bilinear/Bilinear.h"
#include "../../interpolation/bicubic/Bicubic.h"
#include "../../interpolation/curvature/Curvature.h"

template <typename Pixel>
double calculate_accuracy(const Mat &result, const Mat &opencv_result) {
    double total_diff = 0;
    double max_possible_diff = 0;
    
    for (int i = 0; i < result.rows; i++) {
        for (int j = 0; j < result.cols; j++) {
            if constexpr (std::is_same_v<Pixel, uchar>) {
                total_diff += std::abs(result.at<uchar>(i, j) - opencv_result.at<uchar>(i, j));
                max_possible_diff += 255;
            } else if constexpr (std::is_same_v<Pixel, Vec3b>) {
                Vec3b pix1 = result.at<Vec3b>(i, j);
                Vec3b pix2 = opencv_result.at<Vec3b>(i, j);
                for (int c = 0; c < 3; c++) {
                    total_diff += std::abs(pix1[c] - pix2[c]);
                    max_possible_diff += 255;
                }
            }
        }
    }
    
    return 1.0 - (total_diff / max_possible_diff);
}

template <typename Pixel>
void benchmark_accuracy(const Mat_<Pixel> &source, double scale_factor) {
    Mat opencv_nn;
    Mat opencv_bilinear;
    Mat opencv_bicubic;
    resize(source, opencv_nn, Size(), scale_factor, scale_factor, INTER_NEAREST);
    resize(source, opencv_bilinear, Size(), scale_factor, scale_factor, INTER_LINEAR);
    resize(source, opencv_bicubic, Size(), scale_factor, scale_factor, INTER_CUBIC);

    Mat nn_result = NearestNeighbor<Pixel>::getInstance().zoom(source, scale_factor);
    Mat bl_result = Bilinear<Pixel>::getInstance().zoom(source, scale_factor);
    Mat bc_result = Bicubic<Pixel>::getInstance().zoom(source, scale_factor);

    double nn_accuracy = calculate_accuracy<Pixel>(nn_result, opencv_nn);
    double bl_accuracy = calculate_accuracy<Pixel>(bl_result, opencv_bilinear);
    double bc_accuracy = calculate_accuracy<Pixel>(bc_result, opencv_bicubic);

    std::cout << "\n--- ACCURACY BENCHMARK (scale=" << scale_factor << ") ---\n";
    std::cout << "Nearest Neighbor: " << std::fixed << std::setprecision(6) << nn_accuracy * 100 << "%" << std::endl;
    std::cout << "Bilinear: " << std::fixed << std::setprecision(6) << bl_accuracy * 100 << "%" << std::endl;
    std::cout << "Bicubic: " << std::fixed << std::setprecision(6) << bc_accuracy * 100 << "%" << std::endl;
    std::cout << "Curvature interpolation is not part of OpenCV's interpolation options."<< std::endl;
}

template <typename Pixel>
void benchmark_accuracy_xy(const Mat_<Pixel> &source, double scale_factor_x, double scale_factor_y) {
    Mat opencv_nn;
    Mat opencv_bilinear;
    Mat opencv_bicubic;
    resize(source, opencv_nn, Size(), scale_factor_x, scale_factor_y, INTER_NEAREST);
    resize(source, opencv_bilinear, Size(), scale_factor_x, scale_factor_y, INTER_LINEAR);
    resize(source, opencv_bicubic, Size(), scale_factor_x, scale_factor_y, INTER_CUBIC);

    Mat nn_result = NearestNeighbor<Pixel>::getInstance().zoom(source, scale_factor_x, scale_factor_y);
    Mat bl_result = Bilinear<Pixel>::getInstance().zoom(source, scale_factor_x, scale_factor_y);
    Mat bc_result = Bicubic<Pixel>::getInstance().zoom(source, scale_factor_x, scale_factor_y);

    double nn_accuracy = calculate_accuracy<Pixel>(nn_result, opencv_nn);
    double bl_accuracy = calculate_accuracy<Pixel>(bl_result, opencv_bilinear);
    double bc_accuracy = calculate_accuracy<Pixel>(bc_result, opencv_bicubic);

    std::cout << "\n--- ACCURACY BENCHMARK (scale_x=" << scale_factor_x << ", scale_y=" << scale_factor_y << ") ---\n";
    std::cout << "Nearest Neighbor: " << std::fixed << std::setprecision(6) << nn_accuracy * 100 << "%" << std::endl;
    std::cout << "Bilinear: " << std::fixed << std::setprecision(6) << bl_accuracy * 100 << "%" << std::endl;
    std::cout << "Bicubic: " << std::fixed << std::setprecision(6) << bc_accuracy * 100 << "%" << std::endl;
    std::cout << "Curvature interpolation is not part of OpenCV's interpolation options."<< std::endl;
} 