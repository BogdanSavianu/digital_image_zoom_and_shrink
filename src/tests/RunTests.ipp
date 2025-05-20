//
// Created by Bogdan Savianu on 05.04.2025.
//
#include "RunTests.h"
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include "benchmark/BenchmarkAccuracy.h"
#include "benchmark/BenchmarkOperations.h"
#include "benchmark/BenchmarkTiming.h"

template <typename Pixel>
void test_nn_zoom(Mat_<Pixel> &source, const std::string &image_name){
    Mat result = NearestNeighbor<Pixel>::getInstance().zoom(source, 2.0);
    imshow(image_name + " zoomed 2x (Nearest Neighbor)", result);
}

template <typename Pixel>
void test_nn_shrink(Mat_<Pixel> &source, const std::string &image_name){
    Mat result = NearestNeighbor<Pixel>::getInstance().shrink(source, 0.5);
    imshow(image_name + " shrunk 0.5x (Nearest Neighbor)", result);
}

template <typename Pixel>
void test_nn_zoom_xy(Mat_<Pixel> &source, double scale_x, double scale_y, const std::string &image_name){
    Mat result = NearestNeighbor<Pixel>::getInstance().zoom(source, scale_x, scale_y);
    std::string window_name = image_name + " zoomed " + std::to_string(scale_x) + "x width, " +
                              std::to_string(scale_y) + "x height (Nearest Neighbor)";
    imshow(window_name, result);
}

template <typename Pixel>
void test_nn_shrink_xy(Mat_<Pixel> &source, double scale_x, double scale_y, const std::string &image_name){
    Mat result = NearestNeighbor<Pixel>::getInstance().shrink(source, scale_x, scale_y);
    std::string window_name = image_name + " shrunk " + std::to_string(scale_x) + "x width, " +
                              std::to_string(scale_y) + "x height (Nearest Neighbor)";
    imshow(window_name, result);
}

template <typename Pixel>
void test_bilinear_zoom(Mat_<Pixel> &source, const std::string &image_name){
    Mat result = Bilinear<Pixel>::getInstance().zoom(source, 2.0);
    imshow(image_name + " zoomed 2x (Bilinear)", result);
}

template <typename Pixel>
void test_bilinear_shrink(Mat_<Pixel> &source, const std::string &image_name){
    Mat result = Bilinear<Pixel>::getInstance().shrink(source, 0.5);
    imshow(image_name + " shrunk 0.5x (Bilinear)", result);
}

template <typename Pixel>
void test_bilinear_zoom_xy(Mat_<Pixel> &source, double scale_x, double scale_y, const std::string &image_name){
    Mat result = Bilinear<Pixel>::getInstance().zoom(source, scale_x, scale_y);
    std::string window_name = image_name + " zoomed " + std::to_string(scale_x) + "x width, " +
                              std::to_string(scale_y) + "x height (Bilinear)";
    imshow(window_name, result);
}

template <typename Pixel>
void test_bilinear_shrink_xy(Mat_<Pixel> &source, double scale_x, double scale_y, const std::string &image_name){
    Mat result = Bilinear<Pixel>::getInstance().shrink(source, scale_x, scale_y);
    std::string window_name = image_name + " shrunk " + std::to_string(scale_x) + "x width, " +
                              std::to_string(scale_y) + "x height (Bilinear)";
    imshow(window_name, result);
}

template <typename Pixel>
void test_bicubic_zoom(Mat_<Pixel> &source, const std::string &image_name){
    Mat result = Bicubic<Pixel>::getInstance().zoom(source, 2.0);
    imshow(image_name + " zoomed 2x (Bicubic)", result);
}

template <typename Pixel>
void test_bicubic_shrink(Mat_<Pixel> &source, const std::string &image_name){
    Mat result = Bicubic<Pixel>::getInstance().shrink(source, 0.5);
    imshow(image_name + " shrunk 0.5x (Bicubic)", result);
}

template <typename Pixel>
void test_bicubic_zoom_xy(Mat_<Pixel> &source, double scale_x, double scale_y, const std::string &image_name){
    Mat result = Bicubic<Pixel>::getInstance().zoom(source, scale_x, scale_y);
    std::string window_name = image_name + " zoomed " + std::to_string(scale_x) + "x width, " +
                             std::to_string(scale_y) + "x height (Bicubic)";
    imshow(window_name, result);
}

template <typename Pixel>
void test_bicubic_shrink_xy(Mat_<Pixel> &source, double scale_x, double scale_y, const std::string &image_name){
    Mat result = Bicubic<Pixel>::getInstance().shrink(source, scale_x, scale_y);
    std::string window_name = image_name + " shrunk " + std::to_string(scale_x) + "x width, " +
                             std::to_string(scale_y) + "x height (Bicubic)";
    imshow(window_name, result);
}

template <typename Pixel>
void test_curvature_zoom(Mat_<Pixel> &source, const std::string &image_name){
    Mat result = Curvature<Pixel>::getInstance().zoom(source, 2.0);
    imshow(image_name + " zoomed 2x (Curvature)", result);
}

template <typename Pixel>
void test_curvature_shrink(Mat_<Pixel> &source, const std::string &image_name){
    Mat result = Curvature<Pixel>::getInstance().shrink(source, 0.5);
    imshow(image_name + " shrunk 0.5x (Curvature)", result);
}

template <typename Pixel>
void test_curvature_zoom_xy(Mat_<Pixel> &source, double scale_x, double scale_y, const std::string &image_name){
    Mat result = Curvature<Pixel>::getInstance().zoom(source, scale_x, scale_y);
    std::string window_name = image_name + " zoomed " + std::to_string(scale_x) + "x width, " +
                             std::to_string(scale_y) + "x height (Curvature)";
    imshow(window_name, result);
}

template <typename Pixel>
void test_curvature_shrink_xy(Mat_<Pixel> &source, double scale_x, double scale_y, const std::string &image_name){
    Mat result = Curvature<Pixel>::getInstance().shrink(source, scale_x, scale_y);
    std::string window_name = image_name + " shrunk " + std::to_string(scale_x) + "x width, " +
                             std::to_string(scale_y) + "x height (Curvature)";
    imshow(window_name, result);
}

enum class InterpolationMethod {
    NEAREST_NEIGHBOR = 0,
    BILINEAR = 1,
    BICUBIC = 2,
    CURVATURE = 3
};

std::vector<bool> get_selected_methods_console() {
    std::vector<bool> selected_methods(4, false);
    
    std::cout << "Select interpolation methods to test:" << std::endl;
    std::cout << "1. Nearest Neighbor (y/n): ";
    char input;
    std::cin >> input;
    selected_methods[0] = (input == 'y' || input == 'Y');
    
    std::cout << "2. Bilinear (y/n): ";
    std::cin >> input;
    selected_methods[1] = (input == 'y' || input == 'Y');
    
    std::cout << "3. Bicubic (y/n): ";
    std::cin >> input;
    selected_methods[2] = (input == 'y' || input == 'Y');
    
    std::cout << "4. Curvature (y/n): ";
    std::cin >> input;
    selected_methods[3] = (input == 'y' || input == 'Y');
    
    return selected_methods;
}

int select_image_console() {
    std::cout << "Select image to test:" << std::endl;
    std::cout << "1. Apple Park (color)" << std::endl;
    std::cout << "2. Balloons (grayscale)" << std::endl;
    std::cout << "Enter choice (1-2): ";
    
    int choice;
    std::cin >> choice;
    return choice;
}

std::vector<double> get_custom_scales(const std::string &scale_type) {
    std::vector<double> scales;
    std::string input;
    
    std::cout << "Enter " << scale_type << " scales separated by spaces (e.g., 2.0 4.0 8.0): ";
    std::cin.ignore(); // clear buffer before reading so we have nothing leftover
    std::getline(std::cin, input);
    
    std::stringstream ss(input);
    double scale;
    while (ss >> scale) {
        scales.push_back(scale);
    }
    
    if (scales.empty()) {
        std::cout << "No valid scales entered. Using default scale of " 
                  << (scale_type == "zoom" ? "2.0" : "0.5") << std::endl;
        scales.push_back(scale_type == "zoom" ? 2.0 : 0.5);
    }
    
    return scales;
}

inline bool get_non_uniform_test_choice() {
    std::cout << "Do you want to test non-uniform scaling (different x and y scales)? (y/n): ";
    char choice;
    std::cin >> choice;
    return (choice == 'y' || choice == 'Y');
}

std::pair<double, double> get_non_uniform_scales(const std::string &scale_type) {
    double scale_x = 0.0, scale_y = 0.0;
    
    std::cout << "Enter " << scale_type << " scale for x dimension: ";
    std::cin >> scale_x;
    
    std::cout << "Enter " << scale_type << " scale for y dimension: ";
    std::cin >> scale_y;
    
    if (scale_x <= 0.0 || scale_y <= 0.0) {
        std::cout << "Invalid scales entered. Using default scales." << std::endl;
        if (scale_type == "zoom") {
            scale_x = 2.0;
            scale_y = 1.5;
        } else {
            scale_x = 0.5;
            scale_y = 0.75;
        }
    }
    
    return {scale_x, scale_y};
}

template <typename Pixel>
void run_tests_with_scales(Mat_<Pixel> &source, const std::string &image_name, 
                          const std::vector<bool> &selected_methods,
                          const std::vector<double> &zoom_scales,
                          const std::vector<double> &shrink_scales,
                          bool test_non_uniform,
                          std::pair<double, double> non_uniform_zoom,
                          std::pair<double, double> non_uniform_shrink) {
    
    imshow("Original " + image_name, source);

    // uniform - same x and y scales
    if (selected_methods[(int)(InterpolationMethod::NEAREST_NEIGHBOR)]) {
        for (double scale : zoom_scales) {
            Mat result = NearestNeighbor<Pixel>::getInstance().zoom(source, scale);
            imshow(image_name + " zoomed " + std::to_string(scale) + "x (Nearest Neighbor)", result);
        }
        
        for (double scale : shrink_scales) {
            Mat result = NearestNeighbor<Pixel>::getInstance().shrink(source, scale);
            imshow(image_name + " shrunk " + std::to_string(scale) + "x (Nearest Neighbor)", result);
        }
    }
    
    if (selected_methods[(int)(InterpolationMethod::BILINEAR)]) {
        for (double scale : zoom_scales) {
            Mat result = Bilinear<Pixel>::getInstance().zoom(source, scale);
            imshow(image_name + " zoomed " + std::to_string(scale) + "x (Bilinear)", result);
        }
        
        for (double scale : shrink_scales) {
            Mat result = Bilinear<Pixel>::getInstance().shrink(source, scale);
            imshow(image_name + " shrunk " + std::to_string(scale) + "x (Bilinear)", result);
        }
    }
    
    if (selected_methods[(int)(InterpolationMethod::BICUBIC)]) {
        for (double scale : zoom_scales) {
            Mat result = Bicubic<Pixel>::getInstance().zoom(source, scale);
            imshow(image_name + " zoomed " + std::to_string(scale) + "x (Bicubic)", result);
        }
        
        for (double scale : shrink_scales) {
            Mat result = Bicubic<Pixel>::getInstance().shrink(source, scale);
            imshow(image_name + " shrunk " + std::to_string(scale) + "x (Bicubic)", result);
        }
    }
    
    if (selected_methods[(int)(InterpolationMethod::CURVATURE)]) {
        for (double scale : zoom_scales) {
            Mat result = Curvature<Pixel>::getInstance().zoom(source, scale);
            imshow(image_name + " zoomed " + std::to_string(scale) + "x (Curvature)", result);
        }
        
        for (double scale : shrink_scales) {
            Mat result = Curvature<Pixel>::getInstance().shrink(source, scale);
            imshow(image_name + " shrunk " + std::to_string(scale) + "x (Curvature)", result);
        }
    }

    // non-uniform - different x and y scales
    if (test_non_uniform) {
        double zoom_scale_x = non_uniform_zoom.first;
        double zoom_scale_y = non_uniform_zoom.second;
        
        std::cout << "Testing non-uniform zoom with scales: " << zoom_scale_x << "x" << zoom_scale_y << std::endl;
        
        if (selected_methods[(int)(InterpolationMethod::NEAREST_NEIGHBOR)]) {
            test_nn_zoom_xy<Pixel>(source, zoom_scale_x, zoom_scale_y, image_name);
        }
        
        if (selected_methods[(int)(InterpolationMethod::BILINEAR)]) {
            test_bilinear_zoom_xy<Pixel>(source, zoom_scale_x, zoom_scale_y, image_name);
        }
        
        if (selected_methods[(int)(InterpolationMethod::BICUBIC)]) {
            test_bicubic_zoom_xy<Pixel>(source, zoom_scale_x, zoom_scale_y, image_name);
        }
        
        if (selected_methods[(int)(InterpolationMethod::CURVATURE)]) {
            test_curvature_zoom_xy<Pixel>(source, zoom_scale_x, zoom_scale_y, image_name);
        }
        
        double shrink_scale_x = non_uniform_shrink.first;
        double shrink_scale_y = non_uniform_shrink.second;
        
        std::cout << "Testing non-uniform shrink with scales: " << shrink_scale_x << "x" << shrink_scale_y << std::endl;
        
        if (selected_methods[(int)(InterpolationMethod::NEAREST_NEIGHBOR)]) {
            test_nn_shrink_xy<Pixel>(source, shrink_scale_x, shrink_scale_y, image_name);
        }
        
        if (selected_methods[(int)(InterpolationMethod::BILINEAR)]) {
            test_bilinear_shrink_xy<Pixel>(source, shrink_scale_x, shrink_scale_y, image_name);
        }
        
        if (selected_methods[(int)(InterpolationMethod::BICUBIC)]) {
            test_bicubic_shrink_xy<Pixel>(source, shrink_scale_x, shrink_scale_y, image_name);
        }
        
        if (selected_methods[(int)(InterpolationMethod::CURVATURE)]) {
            test_curvature_shrink_xy<Pixel>(source, shrink_scale_x, shrink_scale_y, image_name);
        }
    }
}

void run_tests() {
    int image_choice = select_image_console();
    std::vector<bool> selected_methods = get_selected_methods_console();
    
    std::cout << "For zoom, enter values > 1.0. For shrink, enter values between 0.0 and 1.0." << std::endl;
    
    std::vector<double> zoom_scales = get_custom_scales("zoom");
    std::vector<double> shrink_scales = get_custom_scales("shrink");
    
    bool test_non_uniform = get_non_uniform_test_choice();
    std::pair<double, double> non_uniform_zoom;
    std::pair<double, double> non_uniform_shrink;
    
    if (test_non_uniform) {
        std::cout << "Enter non-uniform scales for zooming:" << std::endl;
        non_uniform_zoom = get_non_uniform_scales("zoom");
        
        std::cout << "Enter non-uniform scales for shrinking:" << std::endl;
        non_uniform_shrink = get_non_uniform_scales("shrink");
    }
    
    if (image_choice == 1) {
        Mat source = imread("/Users/bogdansavianu/University/Year3/Sem2/Image_Processing/Project/images/ApplePark.bmp", IMREAD_COLOR);
        if (source.empty()) {
            std::cerr << "Could not read the image." << std::endl;
            return;
        }
        run_tests_with_scales<Vec3b>((Mat_<Vec3b>&)source, "Apple Park", 
                                     selected_methods, zoom_scales, shrink_scales,
                                     test_non_uniform, non_uniform_zoom, non_uniform_shrink);
    } else if (image_choice == 2) {
        Mat source = imread("/Users/bogdansavianu/University/Year3/Sem2/Image_Processing/Project/images/balloons.jpeg", IMREAD_GRAYSCALE);
        if (source.empty()) {
            std::cerr << "Could not read the image." << std::endl;
            return;
        }
        run_tests_with_scales<uchar>((Mat_<uchar>&)source, "Balloons", 
                                    selected_methods, zoom_scales, shrink_scales,
                                    test_non_uniform, non_uniform_zoom, non_uniform_shrink);
    } else {
        std::cerr << "Invalid image choice." << std::endl;
        return;
    }
    
    waitKey();
}

template<typename Pixel>
void run_benchmarks_for_image(const Mat_<Pixel> &source, BenchmarkType type) {
    std::cout << "Enter custom scales for benchmarking:" << std::endl;
    std::vector<double> scales = get_custom_scales("benchmark");
    
    bool test_non_uniform = get_non_uniform_test_choice();
    std::pair<double, double> non_uniform_scales;
    
    if (test_non_uniform) {
        std::cout << "Enter non-uniform scales for benchmarking:" << std::endl;
        non_uniform_scales = get_non_uniform_scales("benchmark");
    }
    
    std::cout << "Running benchmarks for the selected scales..." << std::endl;
    
    switch (type) {
        case BenchmarkType::ACCURACY:
            for (double scale : scales) {
                benchmark_accuracy<Pixel>(source, scale);
            }
            
            if (test_non_uniform) {
                benchmark_accuracy_xy<Pixel>(source, non_uniform_scales.first, non_uniform_scales.second);
            }
            break;
            
        case BenchmarkType::OPERATIONS:
            for (double scale : scales) {
                benchmark_operations<Pixel>(source, scale);
            }
            
            if (test_non_uniform) {
                benchmark_operations_xy<Pixel>(source, non_uniform_scales.first, non_uniform_scales.second);
            }
            break;
            
        case BenchmarkType::TIMING:
            for (double scale : scales) {
                benchmark_timing<Pixel>(source, scale);
            }
            
            if (test_non_uniform) {
                benchmark_timing_xy<Pixel>(source, non_uniform_scales.first, non_uniform_scales.second);
            }
            break;
    }
}

void run_benchmarks(BenchmarkType type) {
    int image_choice = select_image_console();
    
    if (image_choice == 1) {
        Mat source = imread("/Users/bogdansavianu/University/Year3/Sem2/Image_Processing/Project/images/ApplePark.bmp", IMREAD_COLOR);
        if (source.empty()) {
            std::cerr << "Could not read the image." << std::endl;
            return;
        }
        run_benchmarks_for_image<Vec3b>((Mat_<Vec3b>&)source, type);
    } else if (image_choice == 2) {
        Mat source = imread("/Users/bogdansavianu/University/Year3/Sem2/Image_Processing/Project/images/balloons.jpeg", IMREAD_GRAYSCALE);
        if (source.empty()) {
            std::cerr << "Could not read the image." << std::endl;
            return;
        }
        run_benchmarks_for_image<uchar>((Mat_<uchar>&)source, type);
    } else {
        std::cerr << "Invalid image choice." << std::endl;
        return;
    }
}

void run_corner_case_tests() {
    std::cout << "\n--- CORNER CASE TESTS ---" << std::endl;
    std::cout << "Select image for corner case tests:" << std::endl;
    std::cout << "1. Triangles (grayscale)" << std::endl;
    std::cout << "2. Lines (grayscale)" << std::endl;
    std::cout << "Enter choice (1-2): ";

    int image_choice;
    std::cin >> image_choice;

    std::string image_path;
    std::string image_name;

    if (image_choice == 1) {
        image_path = "/Users/bogdansavianu/University/Year3/Sem2/Image_Processing/Project/images/triangles.jpg";
        image_name = "Triangles";
    } else if (image_choice == 2) {
        image_path = "/Users/bogdansavianu/University/Year3/Sem2/Image_Processing/Project/images/lines.jpg";
        image_name = "Lines";
    } else {
        std::cerr << "Invalid image choice. Exiting corner case tests." << std::endl;
        return;
    }

    Mat source = imread(image_path, IMREAD_GRAYSCALE);
    if (source.empty()) {
        std::cerr << "Could not read the image: " << image_path << std::endl;
        return;
    }

    Mat_<uchar> source_mat_uchar = source;

    double scale_x, scale_y;
    std::cout << "Enter scale factor for X dimension: ";
    std::cin >> scale_x;
    std::cout << "Enter scale factor for Y dimension: ";
    std::cin >> scale_y;

    if (scale_x <= 0 || scale_y <= 0) {
        std::cerr << "Scale factors must be positive." << std::endl;
        return;
    }

    std::cout << "Running interpolations for " << image_name << " with scale_x=" << scale_x << ", scale_y=" << scale_y << std::endl;

    Mat nn_result = NearestNeighbor<uchar>::getInstance().zoom(source_mat_uchar, scale_x, scale_y);
    imshow(image_name + " NN (x" + std::to_string(scale_x) + ", y" + std::to_string(scale_y) + ")", nn_result);

    Mat bl_result = Bilinear<uchar>::getInstance().zoom(source_mat_uchar, scale_x, scale_y);
    imshow(image_name + " Bilinear (x" + std::to_string(scale_x) + ", y" + std::to_string(scale_y) + ")", bl_result);


    Mat bc_result = Bicubic<uchar>::getInstance().zoom(source_mat_uchar, scale_x, scale_y);
    imshow(image_name + " Bicubic (x" + std::to_string(scale_x) + ", y" + std::to_string(scale_y) + ")", bc_result);
    
    Mat cv_result = Curvature<uchar>::getInstance().zoom(source_mat_uchar, scale_x, scale_y);
    imshow(image_name + " Curvature (x" + std::to_string(scale_x) + ", y" + std::to_string(scale_y) + ")", cv_result);

    waitKey();
}