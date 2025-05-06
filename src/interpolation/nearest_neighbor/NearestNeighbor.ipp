//
// Created by Bogdan Savianu on 05.04.2025.
//

#include "NearestNeighbor.h"

template<typename Pixel>
Mat NearestNeighbor<Pixel>::zoom(const Mat_<Pixel> &source, double scale_factor) {
    int new_rows = (int)(source.rows * scale_factor);
    int new_cols = (int)(source.cols * scale_factor);
    Mat_<Pixel> result(new_rows, new_cols);

    for (int i = 0; i < new_rows; ++i) {
        for (int j = 0; j < new_cols; ++j) {
            result.template at<Pixel>(i, j) = source(std::min((int)(i / scale_factor), source.rows - 1)
                    , std::min((int)(j / scale_factor), source.cols - 1));
        }
    }

    return result;
}

template<typename Pixel>
Mat NearestNeighbor<Pixel>::shrink(const Mat_<Pixel> &source, double scale_factor) {
    return zoom(source, scale_factor);
}

template<typename Pixel>
Mat NearestNeighbor<Pixel>::zoom(const Mat_<Pixel> &source, double scale_factor_x, double scale_factor_y) {
    int new_rows = (int)(source.rows * scale_factor_y);
    int new_cols = (int)(source.cols * scale_factor_x);
    Mat_<Pixel> result(new_rows, new_cols);

    for (int i = 0; i < new_rows; ++i) {
        for (int j = 0; j < new_cols; ++j) {
            result.template at<Pixel>(i, j) = source(std::min((int)(i / scale_factor_y), source.rows - 1)
                    , std::min((int)(j / scale_factor_x), source.cols - 1));
        }
    }

    return result;
}

template<typename Pixel>
Mat NearestNeighbor<Pixel>::shrink(const Mat_<Pixel> &source, double scale_factor_x, double scale_factor_y) {
    return zoom(source, scale_factor_x, scale_factor_y);
}