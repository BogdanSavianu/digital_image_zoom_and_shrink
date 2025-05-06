//
// Created by Bogdan Savianu on 02.05.2025.
//

#include "BenchmarkOperations.h"
#include <chrono>

template <typename Pixel>
void benchmark_operations(const Mat_<Pixel> &source, double scale_factor) {
    std::cout << "\nBenchmarking for scale factor: " << scale_factor << std::endl;
    
    auto nn_start = std::chrono::high_resolution_clock::now();
    auto nn_result = run_with_timeout([&]() {
        OperationNearestNeighbor<Pixel>::getInstance().zoom(source, scale_factor);
    }, timeout);
    auto nn_end = std::chrono::high_resolution_clock::now();
    
    auto bl_start = std::chrono::high_resolution_clock::now();
    auto bl_result = run_with_timeout([&]() {
        OperationBilinear<Pixel>::getInstance().zoom(source, scale_factor);
    }, timeout);
    auto bl_end = std::chrono::high_resolution_clock::now();
    
    auto bc_start = std::chrono::high_resolution_clock::now();
    auto bc_result = run_with_timeout([&]() {
        OperationBicubic<Pixel>::getInstance().zoom(source, scale_factor);
    }, timeout);
    auto bc_end = std::chrono::high_resolution_clock::now();
    
    auto cv_start = std::chrono::high_resolution_clock::now();
    auto cv_result = run_with_timeout([&]() {
        OperationCurvature<Pixel>::getInstance().zoom(source, scale_factor);
    }, timeout);
    auto cv_end = std::chrono::high_resolution_clock::now();
    
    auto nn_duration = std::chrono::duration_cast<std::chrono::milliseconds>(nn_end - nn_start).count();
    auto bl_duration = std::chrono::duration_cast<std::chrono::milliseconds>(bl_end - bl_start).count();
    auto bc_duration = std::chrono::duration_cast<std::chrono::milliseconds>(bc_end - bc_start).count();
    auto cv_duration = std::chrono::duration_cast<std::chrono::milliseconds>(cv_end - cv_start).count();
    
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "| Method               | Duration (ms)| Operations        | Status                  |" << std::endl;
    std::cout << "|----------------------|--------------|-------------------|-------------------------|" << std::endl;
    
    std::cout << "| Nearest Neighbor     | " << std::setw(12) << nn_duration << " | ";
    if (nn_result.first) {
        std::cout << std::setw(17) << nn_result.second << " | Completed               |" << std::endl;
    } else {
        std::cout << std::setw(17) << "N/A" << " | Timed out               |" << std::endl;
    }
    
    std::cout << "| Bilinear             | " << std::setw(12) << bl_duration << " | ";
    if (bl_result.first) {
        std::cout << std::setw(17) << bl_result.second << " | Completed               |" << std::endl;
    } else {
        std::cout << std::setw(17) << "N/A" << " | Timed out               |" << std::endl;
    }
    
    std::cout << "| Bicubic              | " << std::setw(12) << bc_duration << " | ";
    if (bc_result.first) {
        std::cout << std::setw(17) << bc_result.second << " | Completed               |" << std::endl;
    } else {
        std::cout << std::setw(17) << "N/A" << " | Timed out               |" << std::endl;
    }
    
    std::cout << "| Curvature            | " << std::setw(12) << cv_duration << " | ";
    if (cv_result.first) {
        std::cout << std::setw(17) << cv_result.second << " | Completed               |" << std::endl;
    } else {
        std::cout << std::setw(17) << "N/A" << " | Timed out               |" << std::endl;
    }
}

template <typename Pixel>
void benchmark_operations_xy(const Mat_<Pixel> &source, double scale_factor_x, double scale_factor_y) {
    std::cout << "\nBenchmarking for scale factors: " << scale_factor_x << " x " << scale_factor_y << std::endl;
    
    auto nn_start = std::chrono::high_resolution_clock::now();
    auto nn_result = run_with_timeout([&]() {
        OperationNearestNeighbor<Pixel>::getInstance().zoom(source, scale_factor_x, scale_factor_y);
    }, 30);
    auto nn_end = std::chrono::high_resolution_clock::now();
    
    auto bl_start = std::chrono::high_resolution_clock::now();
    auto bl_result = run_with_timeout([&]() {
        OperationBilinear<Pixel>::getInstance().zoom(source, scale_factor_x, scale_factor_y);
    }, 30);
    auto bl_end = std::chrono::high_resolution_clock::now();
    
    auto bc_start = std::chrono::high_resolution_clock::now();
    auto bc_result = run_with_timeout([&]() {
        OperationBicubic<Pixel>::getInstance().zoom(source, scale_factor_x, scale_factor_y);
    }, 30);
    auto bc_end = std::chrono::high_resolution_clock::now();
    
    auto cv_start = std::chrono::high_resolution_clock::now();
    auto cv_result = run_with_timeout([&]() {
        OperationCurvature<Pixel>::getInstance().zoom(source, scale_factor_x, scale_factor_y);
    }, 30);
    auto cv_end = std::chrono::high_resolution_clock::now();
    
    auto nn_duration = std::chrono::duration_cast<std::chrono::milliseconds>(nn_end - nn_start).count();
    auto bl_duration = std::chrono::duration_cast<std::chrono::milliseconds>(bl_end - bl_start).count();
    auto bc_duration = std::chrono::duration_cast<std::chrono::milliseconds>(bc_end - bc_start).count();
    auto cv_duration = std::chrono::duration_cast<std::chrono::milliseconds>(cv_end - cv_start).count();
    
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "| Method                | Duration (ms) | Operations        | Status                  |" << std::endl;
    std::cout << "|----------------------|--------------|-------------------|-------------------------|" << std::endl;
    
    std::cout << "| Nearest Neighbor     | " << std::setw(12) << nn_duration << " | ";
    if (nn_result.first) {
        std::cout << std::setw(17) << nn_result.second << " | Completed               |" << std::endl;
    } else {
        std::cout << std::setw(17) << "N/A" << " | Timed out               |" << std::endl;
    }
    
    std::cout << "| Bilinear             | " << std::setw(12) << bl_duration << " | ";
    if (bl_result.first) {
        std::cout << std::setw(17) << bl_result.second << " | Completed               |" << std::endl;
    } else {
        std::cout << std::setw(17) << "N/A" << " | Timed out               |" << std::endl;
    }
    
    std::cout << "| Bicubic              | " << std::setw(12) << bc_duration << " | ";
    if (bc_result.first) {
        std::cout << std::setw(17) << bc_result.second << " | Completed               |" << std::endl;
    } else {
        std::cout << std::setw(17) << "N/A" << " | Timed out               |" << std::endl;
    }
    
    std::cout << "| Curvature            | " << std::setw(12) << cv_duration << " | ";
    if (cv_result.first) {
        std::cout << std::setw(17) << cv_result.second << " | Completed               |" << std::endl;
    } else {
        std::cout << std::setw(17) << "N/A" << " | Timed out               |" << std::endl;
    }
} 