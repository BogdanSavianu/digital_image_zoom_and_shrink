#include "OperationNearestNeighbor.h"
#include "../../../interpolation/nearest_neighbor/NearestNeighbor.h"

template <typename Pixel>
Mat OperationNearestNeighbor<Pixel>::zoom(const Mat_<Pixel> &source, double scale_factor) {
    OperationsCounter::reset();
    
    OperationsCounter::add(3);
    int new_rows = (int)(source.rows * scale_factor);
    int new_cols = (int)(source.cols * scale_factor);
    Mat_<Pixel> result(new_rows, new_cols);
    
    for (int i = 0; i < new_rows; ++i) {
        OperationsCounter::increment();
        
        for (int j = 0; j < new_cols; ++j) {
            OperationsCounter::increment();
            
            OperationsCounter::add(4);
            int src_i = (int)(i / scale_factor);
            int src_j = (int)(j / scale_factor);
            result(i, j) = source(src_i, src_j);
        }
        
        OperationsCounter::increment();
    }
    
    OperationsCounter::increment();
    return result;
}

template <typename Pixel>
Mat OperationNearestNeighbor<Pixel>::zoom(const Mat_<Pixel> &source, double scale_factor_x, double scale_factor_y) {
    OperationsCounter::reset();
    
    OperationsCounter::add(3);
    int new_rows = (int)(source.rows * scale_factor_y);
    int new_cols = (int)(source.cols * scale_factor_x);
    Mat_<Pixel> result(new_rows, new_cols);
    
    for (int i = 0; i < new_rows; ++i) {
        OperationsCounter::increment();
        
        for (int j = 0; j < new_cols; ++j) {
            OperationsCounter::increment();
            
            OperationsCounter::add(4);
            int src_i = (int)(i / scale_factor_y);
            int src_j = (int)(j / scale_factor_x);
            result(i, j) = source(src_i, src_j);
        }
        
        OperationsCounter::increment();
    }
    
    OperationsCounter::increment();
    return result;
} 