//
// Created by Bogdan Savianu on 22.04.2025.
//

#include "Bicubic.h"

template<typename Pixel>
inline float Bicubic<Pixel>::cubic_weight(float x) {
    x = std::abs(x);
    return x < 1.0f
            ? (1.5f * x - 2.5f) * x * x + 1.0f
            : (x < 2.0f
                ? ((-0.5f * x + 2.5f) * x - 4.0f) * x + 2.0f
                : 0.0f);
}

template<typename Pixel>
inline float Bicubic<Pixel>::cubic_weight(Point p) {
    return cubic_weight((float)p.x) * cubic_weight((float)p.y);
}

template<>
inline uchar Bicubic<uchar>::new_color(uchar *neigh, float alpha, float beta) {
    float result = 0.0f;
    float weight_sum = 0.0f;
    
    for (int i = 0; i < 16; i++) {
        float weight = cubic_weight(Point(d16j[i]- alpha, d16i[i] - beta));
        result += weight * neigh[i];
        weight_sum += weight;
    }
    
    return (uchar)(result / weight_sum);
}

template<>
inline Vec3b Bicubic<Vec3b>::new_color(Vec3b *neigh, float alpha, float beta) {
    Vec3b result;
    float weight_sum = 0.0f;
    float r_sum = 0.0f;
    float g_sum = 0.0f;
    float b_sum = 0.0f;
    
    for (int i = 0; i < 16; i++) {
        float weight = cubic_weight(Point(d16j[i]- alpha, d16i[i] - beta));
        r_sum += weight * neigh[i][0];
        g_sum += weight * neigh[i][1];
        b_sum += weight * neigh[i][2];
        weight_sum += weight;
    }
    
    int r_val = (int)(r_sum / weight_sum);
    int g_val = (int)(g_sum / weight_sum);
    int b_val = (int)(b_sum / weight_sum);
    
    result[0] = (uchar)(std::min(255, std::max(0, r_val)));
    result[1] = (uchar)(std::min(255, std::max(0, g_val)));
    result[2] = (uchar)(std::min(255, std::max(0, b_val)));
    
    return result;
}

template<typename Pixel>
Mat Bicubic<Pixel>::zoom(const Mat_<Pixel> &source, double scale_factor) {
    int new_rows = (int)(source.rows * scale_factor);
    int new_cols = (int)(source.cols * scale_factor);
    Mat_<Pixel> result(new_rows, new_cols);

    Pixel neighbors[16];

    for (int i = 0; i < new_rows; ++i) {
        for (int j = 0; j < new_cols; ++j) {
            float src_i = i / scale_factor;
            float src_j = j / scale_factor;
            
            int i0 = (int)src_i;
            int j0 = (int)src_j;
            
            float alpha = src_i - i0;
            float beta = src_j - j0;
            
            for (int k = 0; k < 16; ++k) {
                int ni = i0 + d16i[k];
                int nj = j0 + d16j[k];
                
                ni = std::min(std::max(ni, 0), source.rows - 1);
                nj = std::min(std::max(nj, 0), source.cols - 1);
                neighbors[k] = source(ni, nj);
            }
            
            result(i, j) = new_color(neighbors, alpha, beta);
        }
    }
    
    return result;
}

template<typename Pixel>
Mat Bicubic<Pixel>::shrink(const Mat_<Pixel> &source, double scale_factor) {
    return zoom(source, scale_factor);
}

template<typename Pixel>
Mat Bicubic<Pixel>::zoom(const Mat_<Pixel> &source, double scale_factor_x, double scale_factor_y) {
    int new_rows = (int)(source.rows * scale_factor_y);
    int new_cols = (int)(source.cols * scale_factor_x);
    Mat_<Pixel> result(new_rows, new_cols);

    Pixel neighbors[16];

    for (int i = 0; i < new_rows; ++i) {
        for (int j = 0; j < new_cols; ++j) {
            float src_i = i / scale_factor_y;
            float src_j = j / scale_factor_x;
            
            int i0 = (int)src_i;
            int j0 = (int)src_j;
            
            float alpha = src_i - i0;
            float beta = src_j - j0;
            
            for (int k = 0; k < 16; ++k) {
                int ni = i0 + d16i[k];
                int nj = j0 + d16j[k];
                
                ni = std::min(std::max(ni, 0), source.rows - 1);
                nj = std::min(std::max(nj, 0), source.cols - 1);
                neighbors[k] = source(ni, nj);
            }
            
            result(i, j) = new_color(neighbors, alpha, beta);
        }
    }
    
    return result;
}

template<typename Pixel>
Mat Bicubic<Pixel>::shrink(const Mat_<Pixel> &source, double scale_factor_x, double scale_factor_y) {
    return zoom(source, scale_factor_x, scale_factor_y);
}