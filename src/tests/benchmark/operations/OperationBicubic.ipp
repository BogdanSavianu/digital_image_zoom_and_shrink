#include "OperationBicubic.h"
#include "../../../interpolation/bicubic/Bicubic.h"

template <typename Pixel>
Mat OperationBicubic<Pixel>::zoom(const Mat_<Pixel> &source, double scale_factor) {
    OperationsCounter::reset();
    
    OperationsCounter::add(3);
    int new_rows = (int)(source.rows * scale_factor);
    int new_cols = (int)(source.cols * scale_factor);
    Mat_<Pixel> result(new_rows, new_cols);

    static constexpr const int d16i[] = {-1,-1,-1,-1,0,0,0,0,1,1,1,1,2,2,2,2};
    static constexpr const int d16j[] = {-1,0,1,2,-1,0,1,2,-1,0,1,2,-1,0,1,2};

    Pixel neighbors[16];

    for (int i = 0; i < new_rows; ++i) {
        OperationsCounter::increment();
        
        for (int j = 0; j < new_cols; ++j) {
            OperationsCounter::increment();
            
            OperationsCounter::add(6);
            float src_i = i / scale_factor;
            float src_j = j / scale_factor;
            int i0 = (int)floor(src_i);
            int j0 = (int)floor(src_j);
            float alpha = src_i - i0;
            float beta = src_j - j0;
            
            OperationsCounter::add(65);
            
            for (int k = 0; k < 16; ++k) {
                int ni = i0 + d16i[k];
                int nj = j0 + d16j[k];
                
                ni = std::min(std::max(ni, 0), source.rows - 1);
                nj = std::min(std::max(nj, 0), source.cols - 1);
                neighbors[k] = source(ni, nj);
            }
            
            result(i, j) = Bicubic<Pixel>::getInstance().new_color(neighbors, alpha, beta);
        }
        OperationsCounter::increment();
    }
    OperationsCounter::increment();
    
    return result;
}

template <typename Pixel>
Mat OperationBicubic<Pixel>::zoom(const Mat_<Pixel> &source, double scale_factor_x, double scale_factor_y) {
    OperationsCounter::reset();
    
    OperationsCounter::add(3);
    int new_rows = (int)(source.rows * scale_factor_y);
    int new_cols = (int)(source.cols * scale_factor_x);
    Mat_<Pixel> result(new_rows, new_cols);

    static constexpr const int d16i[] = {-1,-1,-1,-1,0,0,0,0,1,1,1,1,2,2,2,2};
    static constexpr const int d16j[] = {-1,0,1,2,-1,0,1,2,-1,0,1,2,-1,0,1,2};

    Pixel neighbors[16];

    for (int i = 0; i < new_rows; ++i) {
        OperationsCounter::increment();
        
        for (int j = 0; j < new_cols; ++j) {
            OperationsCounter::increment();
            
            OperationsCounter::add(6);
            float src_i = i / scale_factor_y;
            float src_j = j / scale_factor_x;
            int i0 = (int)floor(src_i);
            int j0 = (int)floor(src_j);
            float alpha = src_i - i0;
            float beta = src_j - j0;
            
            OperationsCounter::add(65);

            for (int k = 0; k < 16; ++k) {
                int ni = i0 + d16i[k];
                int nj = j0 + d16j[k];
                
                ni = std::min(std::max(ni, 0), source.rows - 1);
                nj = std::min(std::max(nj, 0), source.cols - 1);
                neighbors[k] = source(ni, nj);
            }
            
            result(i, j) = Bicubic<Pixel>::getInstance().new_color(neighbors, alpha, beta);
        }
        OperationsCounter::increment();
    }
    OperationsCounter::increment();
    
    return result;
} 