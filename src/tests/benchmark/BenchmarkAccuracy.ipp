//
// Created by Bogdan Savianu on 02.05.2025.
//

#include "BenchmarkAccuracy.h"
#include "../../interpolation/nearest_neighbor/NearestNeighbor.h"
#include "../../interpolation/bilinear/Bilinear.h"
#include "../../interpolation/bicubic/Bicubic.h"
#include "../../interpolation/curvature/Curvature.h"

template <typename Pixel>
double calculate_accuracy_pixel_by_pixel(const Mat_<Pixel> &result, const Mat_<Pixel> &opencv_result) {
    double total_diff = 0;
    double max_possible_diff = 0;
    
    for (int i = 0; i < result.rows; i++) {
        for (int j = 0; j < result.cols; j++) {
            if constexpr (std::is_same_v<Pixel, uchar>) {
                total_diff += std::abs(result(i, j) - opencv_result(i, j));
                max_possible_diff += 255;
            } else if constexpr (std::is_same_v<Pixel, Vec3b>) {
                Vec3b pix1 = result(i, j);
                Vec3b pix2 = opencv_result(i, j);
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
std::pair<double,double> calculate_accuracy_mse(const Mat_<Pixel> &result, const Mat_<Pixel> &opencv_result) {
    double total_diff = 0;
    double max_possible_diff = 0;
    double diff;

    for (int i = 0; i < result.rows; i++) {
        for (int j = 0; j < result.cols; j++) {
            if constexpr (std::is_same_v<Pixel, uchar>) {
                diff = result(i, j) - opencv_result(i, j);
                total_diff += diff * diff;
                max_possible_diff += 255 * 255;
            } else if constexpr (std::is_same_v<Pixel, Vec3b>) {
                Vec3b pix1 = result(i, j);
                Vec3b pix2 = opencv_result(i, j);
                for (int c = 0; c < 3; c++) {
                    diff = pix1[c] - pix2[c];
                    total_diff += diff * diff;
                    max_possible_diff += 255 * 255;
                }
            }
        }
    }

    return {1.0 - (total_diff / max_possible_diff), total_diff/(result.rows * result.cols * 3)};
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

    double nn_accuracy = calculate_accuracy_pixel_by_pixel<Pixel>(nn_result, opencv_nn);
    double bl_accuracy = calculate_accuracy_pixel_by_pixel<Pixel>(bl_result, opencv_bilinear);
    double bc_accuracy = calculate_accuracy_pixel_by_pixel<Pixel>(bc_result, opencv_bicubic);

    std::cout << "\n--- ACCURACY BENCHMARK (scale=" << scale_factor << ") ---\n";
    std::cout << "\n - Pixel By Pixel - \n";
    std::cout << "Nearest Neighbor: " << std::fixed << std::setprecision(6) << nn_accuracy * 100 << "%" << std::endl;
    std::cout << "Bilinear: " << std::fixed << std::setprecision(6) << bl_accuracy * 100 << "%" << std::endl;
    std::cout << "Bicubic: " << std::fixed << std::setprecision(6) << bc_accuracy * 100 << "%" << std::endl;
    std::cout << "Curvature interpolation is not part of OpenCV's interpolation options."<< std::endl;

    std::pair<double,double> nn_accuracy_mse = calculate_accuracy_mse<Pixel>(nn_result, opencv_nn);
    std::pair<double,double> bl_accuracy_mse = calculate_accuracy_mse<Pixel>(bl_result, opencv_bilinear);
    std::pair<double,double> bc_accuracy_mse = calculate_accuracy_mse<Pixel>(bc_result, opencv_bicubic);

    std::cout << "\n - Mean Squared Error - \n";
    std::cout << "Nearest Neighbor: " << std::fixed << std::setprecision(6) << nn_accuracy_mse.first * 100 << "%, " << "Actual value: " << nn_accuracy_mse.second << std::endl;
    std::cout << "Bilinear: " << std::fixed << std::setprecision(6) << bl_accuracy_mse.first * 100 << "%, " << "Actual value: " << bl_accuracy_mse.second << std::endl;
    std::cout << "Bicubic: " << std::fixed << std::setprecision(6) << bc_accuracy_mse.first * 100 << "%, " << "Actual value: " << bc_accuracy_mse.second << std::endl;
    std::cout << "Curvature interpolation is not part of OpenCV's interpolation options."<< std::endl;

    double max_value;
    if constexpr (std::is_same_v<Pixel,uchar>)
        max_value = 255*255;
    else max_value = 255*255*3;

    double nn_accuracy_psnr = 10 * log10(max_value/nn_accuracy_mse.second);
    double bl_accuracy_psnr = 10 * log10(max_value/bl_accuracy_mse.second);
    double bc_accuracy_psnr = 10 * log10(max_value/bc_accuracy_mse.second);

    std::cout << "\n - Peak Signal-to-Noise Ratio - \n";

    std::cout << "Nearest Neighbor: " << std::fixed << std::setprecision(6) << nn_accuracy_psnr << std::endl;
    std::cout << "Bilinear: " << std::fixed << std::setprecision(6) << bl_accuracy_psnr << std::endl;
    std::cout << "Bicubic: " << std::fixed << std::setprecision(6) << bc_accuracy_psnr << std::endl;
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

    double nn_accuracy = calculate_accuracy_pixel_by_pixel<Pixel>(nn_result, opencv_nn);
    double bl_accuracy = calculate_accuracy_pixel_by_pixel<Pixel>(bl_result, opencv_bilinear);
    double bc_accuracy = calculate_accuracy_pixel_by_pixel<Pixel>(bc_result, opencv_bicubic);

    std::cout << "\n--- ACCURACY BENCHMARK (scale_x=" << scale_factor_x << ", scale_y=" << scale_factor_y << ") ---\n";
    std::cout << "Nearest Neighbor: " << std::fixed << std::setprecision(6) << nn_accuracy * 100 << "%" << std::endl;
    std::cout << "Bilinear: " << std::fixed << std::setprecision(6) << bl_accuracy * 100 << "%" << std::endl;
    std::cout << "Bicubic: " << std::fixed << std::setprecision(6) << bc_accuracy * 100 << "%" << std::endl;
    std::cout << "Curvature interpolation is not part of OpenCV's interpolation options."<< std::endl;

    std::pair<double,double> nn_accuracy_mse = calculate_accuracy_mse<Pixel>(nn_result, opencv_nn);
    std::pair<double,double> bl_accuracy_mse = calculate_accuracy_mse<Pixel>(bl_result, opencv_bilinear);
    std::pair<double,double> bc_accuracy_mse = calculate_accuracy_mse<Pixel>(bc_result, opencv_bicubic);

    std::cout << "\n - Mean Squared Error - \n";
    std::cout << "Nearest Neighbor: " << std::fixed << std::setprecision(6) << nn_accuracy_mse.first * 100 << "%, " << "Actual value: " << nn_accuracy_mse.second << std::endl;
    std::cout << "Bilinear: " << std::fixed << std::setprecision(6) << bl_accuracy_mse.first * 100 << "%, " << "Actual value: " << bl_accuracy_mse.second << std::endl;
    std::cout << "Bicubic: " << std::fixed << std::setprecision(6) << bc_accuracy_mse.first * 100 << "%, " << "Actual value: " << bc_accuracy_mse.second << std::endl;
    std::cout << "Curvature interpolation is not part of OpenCV's interpolation options."<< std::endl;

    double max_value;
    if constexpr (std::is_same_v<Pixel,uchar>)
        max_value = 255;
    else max_value = 255*3;

    double nn_accuracy_psnr = 10 * log10(max_value/nn_accuracy_mse.second);
    double bl_accuracy_psnr = 10 * log10(max_value/bl_accuracy_mse.second);
    double bc_accuracy_psnr = 10 * log10(max_value/bc_accuracy_mse.second);

    std::cout << "\n - Peak Signal-to-Noise Ratio - \n";

    std::cout << "Nearest Neighbor: " << std::fixed << std::setprecision(6) << nn_accuracy_psnr << std::endl;
    std::cout << "Bilinear: " << std::fixed << std::setprecision(6) << bl_accuracy_psnr << std::endl;
    std::cout << "Bicubic: " << std::fixed << std::setprecision(6) << bc_accuracy_psnr << std::endl;
    std::cout << "Curvature interpolation is not part of OpenCV's interpolation options."<< std::endl;
} 