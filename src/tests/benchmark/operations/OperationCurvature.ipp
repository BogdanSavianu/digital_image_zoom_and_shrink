#include "OperationCurvature.h"
#include "../../../interpolation/curvature/Curvature.h"

template <typename Pixel>
Mat OperationCurvature<Pixel>::zoom(const Mat_<Pixel> &source, double scale_factor) {
    OperationsCounter::reset();
    
    OperationsCounter::add(3);
    int new_rows = (int)(source.rows * scale_factor);
    int new_cols = (int)(source.cols * scale_factor);
    Mat_<Pixel> result(new_rows, new_cols);
    for (int i = 0; i < new_rows; ++i) {
        OperationsCounter::increment();
        
        for (int j = 0; j < new_cols; ++j) {
            OperationsCounter::increment();
            
            OperationsCounter::add(6);
            float src_y = i / scale_factor;
            float src_x = j / scale_factor;
            
            if constexpr (std::is_same_v<Pixel, uchar>){
                OperationsCounter::add(86);
            } else {
                OperationsCounter::add(86 * 3);
            }
            result(i, j) = Curvature<Pixel>::getInstance().new_color(source, src_x, src_y);
        }
    }

    return result;
}

template <typename Pixel>
Mat OperationCurvature<Pixel>::zoom(const Mat_<Pixel> &source, double scale_factor_x, double scale_factor_y) {
    OperationsCounter::reset();

    OperationsCounter::add(3);
    int new_rows = (int)(source.rows * scale_factor_y);
    int new_cols = (int)(source.cols * scale_factor_x);
    Mat_<Pixel> result(new_rows, new_cols);

    for (int i = 0; i < new_rows; ++i) {
        OperationsCounter::increment();
        
        for (int j = 0; j < new_cols; ++j) {
            OperationsCounter::increment();
            
            OperationsCounter::add(6);
            float src_y = i / scale_factor_y;
            float src_x = j / scale_factor_x;

            if constexpr (std::is_same_v<Pixel, uchar>){
                OperationsCounter::add(86);
            } else {
                OperationsCounter::add(86 * 3);
            }
            result(i, j) = Curvature<Pixel>::getInstance().new_color(source, src_x, src_y);
        }
    }

    return result;
} 