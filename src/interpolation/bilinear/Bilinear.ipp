//
// Created by Bogdan Savianu on 05.04.2025.
//

#include "Bilinear.h"

template<>
inline uchar Bilinear<uchar>::new_color(uchar neigh[4], float alpha, float beta){
    return (uchar)((1-alpha)*(1-beta)*neigh[0] + (1-alpha)*beta*neigh[1] + 
           alpha*(1-beta)*neigh[2] + alpha*beta*neigh[3]);
}

template<>
inline Vec3b Bilinear<Vec3b>::new_color(Vec3b neigh[4], float alpha, float beta){
    Vec3b result;
    for(int c = 0; c < 3; c++) {
        result[c] = (uchar)((1-alpha)*(1-beta)*neigh[0][c] + (1-alpha)*beta*neigh[1][c] + 
                           alpha*(1-beta)*neigh[2][c] + alpha*beta*neigh[3][c]);
    }
    return result;
}

template<typename Pixel>
Mat Bilinear<Pixel>::zoom(const Mat_<Pixel> &source, double scale_factor) {
    int new_rows = (int)(source.rows * scale_factor);
    int new_cols = (int)(source.cols * scale_factor);
    Mat_<Pixel> result(new_rows, new_cols);

    for(int i = 0; i < new_rows; ++i) {
        for (int j = 0; j < new_cols; ++j) {
            float src_i = i / scale_factor;
            float src_j = j / scale_factor;
            
            int i0 = (int)floor(src_i);
            int j0 = (int)floor(src_j);
            
            float alpha = src_i - i0;
            float beta = src_j - j0;
            
            Pixel neighbors[4];
            for (int k = 0; k < 4; ++k) {
                int ni = i0 + n4_di[k];
                int nj = j0 + n4_dj[k];
                
                if (is_inside(Point(nj, ni), source)) {
                    neighbors[k] = source(ni, nj);
                } else {
                    int valid_i = std::min(std::max(ni, 0), source.rows - 1);
                    int valid_j = std::min(std::max(nj, 0), source.cols - 1);
                    neighbors[k] = source(valid_i, valid_j);
                }
            }
            
            result(i, j) = new_color(neighbors, alpha, beta);
        }
    }
    
    return result;
}

template<typename Pixel>
Mat Bilinear<Pixel>::shrink(const Mat_<Pixel> &source, double scale_factor) {
    return zoom(source, scale_factor);
}

template<typename Pixel>
Mat Bilinear<Pixel>::zoom(const Mat_<Pixel> &source, double scale_factor_x, double scale_factor_y) {
    int new_rows = (int)(source.rows * scale_factor_y);
    int new_cols = (int)(source.cols * scale_factor_x);
    Mat_<Pixel> result(new_rows, new_cols);

    for(int i = 0; i < new_rows; ++i) {
        for (int j = 0; j < new_cols; ++j) {
            float src_i = i / scale_factor_y;
            float src_j = j / scale_factor_x;
            
            int i0 = (int)floor(src_i);
            int j0 = (int)floor(src_j);
            
            float alpha = src_i - i0;
            float beta = src_j - j0;
            
            Pixel neighbors[4];
            for (int k = 0; k < 4; ++k) {
                int ni = i0 + n4_di[k];
                int nj = j0 + n4_dj[k];
                
                if (is_inside(Point(nj, ni), source)) {
                    neighbors[k] = source(ni, nj);
                } else {
                    int valid_i = std::min(std::max(ni, 0), source.rows - 1);
                    int valid_j = std::min(std::max(nj, 0), source.cols - 1);
                    neighbors[k] = source(valid_i, valid_j);
                }
            }
            
            result(i, j) = new_color(neighbors, alpha, beta);
        }
    }
    
    return result;
}

template<typename Pixel>
Mat Bilinear<Pixel>::shrink(const Mat_<Pixel> &source, double scale_factor_x, double scale_factor_y) {
    return zoom(source, scale_factor_x, scale_factor_y);
}