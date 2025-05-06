#include <iostream>
#include <opencv2/opencv.hpp>
#include "src/tests/RunTests.h"

using namespace cv;

int main() {
    std::cout << "Select mode:" << std::endl;
    std::cout << "1. Run interpolation tests" << std::endl;
    std::cout << "2. Run accuracy benchmarks" << std::endl;
    std::cout << "3. Run operations count benchmarks" << std::endl;
    std::cout << "4. Run timing benchmarks" << std::endl;
    std::cout << "Enter choice (1-4): ";
    
    int choice;
    std::cin >> choice;
    
    switch (choice) {
        case 1:
            run_tests();
            break;
        case 2:
            run_benchmarks(BenchmarkType::ACCURACY);
            break;
        case 3:
            run_benchmarks(BenchmarkType::OPERATIONS);
            break;
        case 4:
            run_benchmarks(BenchmarkType::TIMING);
            break;
        default:
            std::cout << "Invalid choice. Exiting." << std::endl;
            break;
    }
    
    return 0;
}
