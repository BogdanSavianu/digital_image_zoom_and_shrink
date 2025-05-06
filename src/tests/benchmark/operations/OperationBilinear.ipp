#include "OperationBilinear.h"
#include "../../../interpolation/bilinear/Bilinear.h"

template <typename Pixel>
Mat OperationBilinear<Pixel>::zoom(const Mat_<Pixel> &source, double scale_factor) {
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
            float src_i = i / scale_factor;
            float src_j = j / scale_factor;
            int i0 = (int)src_i;
            int j0 = (int)src_j;
            i0 = std::min(i0, source.rows - 2);
            j0 = std::min(j0, source.cols - 2);
            
            OperationsCounter::add(2);
            float di = src_i - i0;
            float dj = src_j - j0;
            
            if constexpr (std::is_same_v<Pixel, uchar>) {
                OperationsCounter::add(19);
                result(i, j) = (uchar)(
                    (1 - di) * (1 - dj) * source(i0, j0) +
                    di * (1 - dj) * source(i0 + 1, j0) +
                    (1 - di) * dj * source(i0, j0 + 1) +
                    di * dj * source(i0 + 1, j0 + 1)
                );
            } else if constexpr (std::is_same_v<Pixel, Vec3b>) {
                OperationsCounter::increment();
                for (int c = 0; c < 3; c++) {
                    OperationsCounter::increment();
                    
                    OperationsCounter::add(19);
                    result(i, j)[c] = (uchar)(
                        (1 - di) * (1 - dj) * source(i0, j0)[c] +
                        di * (1 - dj) * source(i0 + 1, j0)[c] +
                        (1 - di) * dj * source(i0, j0 + 1)[c] +
                        di * dj * source(i0 + 1, j0 + 1)[c]
                    );
                }
            }
        }
    }

    return result;
}

template <typename Pixel>
Mat OperationBilinear<Pixel>::zoom(const Mat_<Pixel> &source, double scale_factor_x, double scale_factor_y) {
    OperationsCounter::reset();
    
    OperationsCounter::add(2);
    int new_rows = (int)(source.rows * scale_factor_y);
    int new_cols = (int)(source.cols * scale_factor_x);
    Mat_<Pixel> result(new_rows, new_cols);
    
    for (int i = 0; i < new_rows; ++i) {
        OperationsCounter::increment();
        
        for (int j = 0; j < new_cols; ++j) {
            OperationsCounter::increment();
            
            OperationsCounter::add(10);
            float src_i = i / scale_factor_y;
            float src_j = j / scale_factor_x;
            int i0 = (int)src_i;
            int j0 = (int)src_j;
            i0 = std::min(i0, source.rows - 2);
            j0 = std::min(j0, source.cols - 2);
            
            OperationsCounter::add(2);
            float di = src_i - i0;
            float dj = src_j - j0;
            
            if constexpr (std::is_same_v<Pixel, uchar>) {
                OperationsCounter::add(19);
                result(i, j) = (uchar)(
                    (1 - di) * (1 - dj) * source(i0, j0) +
                    di * (1 - dj) * source(i0 + 1, j0) +
                    (1 - di) * dj * source(i0, j0 + 1) +
                    di * dj * source(i0 + 1, j0 + 1)
                );
            } else if constexpr (std::is_same_v<Pixel, Vec3b>) {
                OperationsCounter::increment();
                for (int c = 0; c < 3; c++) {
                    OperationsCounter::increment();
                    
                    OperationsCounter::add(19);
                    result(i, j)[c] = (uchar)(
                        (1 - di) * (1 - dj) * source(i0, j0)[c] +
                        di * (1 - dj) * source(i0 + 1, j0)[c] +
                        (1 - di) * dj * source(i0, j0 + 1)[c] +
                        di * dj * source(i0 + 1, j0 + 1)[c]
                    );
                }
            }
        }
    }

    return result;
} 