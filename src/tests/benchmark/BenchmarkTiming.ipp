//
// Created by Bogdan Savianu on 02.05.2025.
//

#include "BenchmarkTiming.h"
#include "../../interpolation/nearest_neighbor/NearestNeighbor.h"
#include "../../interpolation/bilinear/Bilinear.h"
#include "../../interpolation/bicubic/Bicubic.h"
#include "../../interpolation/curvature/Curvature.h"

template <typename Pixel>
void benchmark_timing(const Mat_<Pixel> &source, double scale_factor) {
    auto start = std::chrono::high_resolution_clock::now();
    NearestNeighbor<Pixel>::getInstance().zoom(source, scale_factor);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> nn_time = end - start;
    
    start = std::chrono::high_resolution_clock::now();
    Bilinear<Pixel>::getInstance().zoom(source, scale_factor);
    end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> bl_time = end - start;
    
    start = std::chrono::high_resolution_clock::now();
    Bicubic<Pixel>::getInstance().zoom(source, scale_factor);
    end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> bc_time = end - start;
    
    start = std::chrono::high_resolution_clock::now();
    Curvature<Pixel>::getInstance().zoom(source, scale_factor);
    end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> cv_time = end - start;
    
    std::cout << "\n--- TIMING BENCHMARK (scale=" << scale_factor << ") ---\n";
    std::cout << "Nearest Neighbor: " << nn_time.count() << " ms" << std::endl;
    std::cout << "Bilinear: " << bl_time.count() << " ms (" << std::fixed << std::setprecision(2) << bl_time/nn_time << "x NN)" << std::endl;
    std::cout << "Bicubic: " << bc_time.count() << " ms (" << std::fixed << std::setprecision(2) << bc_time/nn_time << "x NN)" << std::endl;
    std::cout << "Curvature: " << cv_time.count() << " ms (" << std::fixed << std::setprecision(2) << cv_time/nn_time << "x NN)" << std::endl;
}

template <typename Pixel>
void benchmark_timing_xy(const Mat_<Pixel> &source, double scale_factor_x, double scale_factor_y) {
    auto start = std::chrono::high_resolution_clock::now();
    NearestNeighbor<Pixel>::getInstance().zoom(source, scale_factor_x, scale_factor_y);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> nn_time = end - start;
    
    start = std::chrono::high_resolution_clock::now();
    Bilinear<Pixel>::getInstance().zoom(source, scale_factor_x, scale_factor_y);
    end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> bl_time = end - start;
    
    start = std::chrono::high_resolution_clock::now();
    Bicubic<Pixel>::getInstance().zoom(source, scale_factor_x, scale_factor_y);
    end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> bc_time = end - start;
    
    start = std::chrono::high_resolution_clock::now();
    Curvature<Pixel>::getInstance().zoom(source, scale_factor_x, scale_factor_y);
    end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> cv_time = end - start;
    
    std::cout << "\n--- TIMING BENCHMARK (scale_x=" << scale_factor_x << ", scale_y=" << scale_factor_y << ") ---\n";
    std::cout << "Nearest Neighbor: " << nn_time.count() << " ms" << std::endl;
    std::cout << "Bilinear: " << bl_time.count() << " ms (" << std::fixed << std::setprecision(2) << bl_time/nn_time << "x NN)" << std::endl;
    std::cout << "Bicubic: " << bc_time.count() << " ms (" << std::fixed << std::setprecision(2) << bc_time/nn_time << "x NN)" << std::endl;
    std::cout << "Curvature: " << cv_time.count() << " ms (" << std::fixed << std::setprecision(2) << cv_time/nn_time << "x NN)" << std::endl;
} 