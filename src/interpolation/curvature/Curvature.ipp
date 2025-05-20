//
// Created by Bogdan Savianu on 04.05.2025.
//

#include "Curvature.h"

template<typename Pixel>
int Curvature<Pixel>::clamp(int value, int min_val, int max_val) {
    return std::min(std::max(value, min_val), max_val);
}

template<typename Pixel>
float Curvature<Pixel>::get_pixel_value(const Mat_<Pixel> &source, int i, int j, int channel) {
    i = clamp(i, 0, source.rows - 1);
    j = clamp(j, 0, source.cols - 1);
    
    if constexpr (std::is_same_v<Pixel, uchar>) {
        return (float)(source(i, j));
    } else {
        return (float)(source(i, j)[channel]);
    }
}

template<typename Pixel>
float Curvature<Pixel>::first_derivative_x(const Mat_<Pixel> &source, int i, int j, int channel) {
    float left = get_pixel_value(source, i, j - 1, channel);
    float right = get_pixel_value(source, i, j + 1, channel);
    return (right - left) / 2.0f;
}

template<typename Pixel>
float Curvature<Pixel>::first_derivative_y(const Mat_<Pixel> &source, int i, int j, int channel) {
    float top = get_pixel_value(source, i - 1, j, channel);
    float bottom = get_pixel_value(source, i + 1, j, channel);
    return (bottom - top) / 2.0f;
}

template<typename Pixel>
float Curvature<Pixel>::second_derivative_xx(const Mat_<Pixel> &source, int i, int j, int channel) {
    float left = get_pixel_value(source, i, j - 1, channel);
    float center = get_pixel_value(source, i, j, channel);
    float right = get_pixel_value(source, i, j + 1, channel);
    return left - 2.0f * center + right;
}

template<typename Pixel>
float Curvature<Pixel>::second_derivative_yy(const Mat_<Pixel> &source, int i, int j, int channel) {
    float top = get_pixel_value(source, i - 1, j, channel);
    float center = get_pixel_value(source, i, j, channel);
    float bottom = get_pixel_value(source, i + 1, j, channel);
    return top - 2.0f * center + bottom;
}

template<typename Pixel>
float Curvature<Pixel>::second_derivative_xy(const Mat_<Pixel> &source, int i, int j, int channel) {
    float top_left = get_pixel_value(source, i - 1, j - 1, channel);
    float top_right = get_pixel_value(source, i - 1, j + 1, channel);
    float bottom_left = get_pixel_value(source, i + 1, j - 1, channel);
    float bottom_right = get_pixel_value(source, i + 1, j + 1, channel);
    return (bottom_right - bottom_left - top_right + top_left) / 4.0f;
}

template<>
uchar Curvature<uchar>::new_color(const Mat_<uchar> &source, float x, float y) {
    int x0 = (int)(std::floor(x));
    int y0 = (int)(std::floor(y));
    
    x0 = clamp(x0, 0, source.cols - 1);
    y0 = clamp(y0, 0, source.rows - 1);
    
    float dx = x - x0;
    float dy = y - y0;
    
    float I_x0_y0 = get_pixel_value(source, y0, x0, 0);
    
    float dI_dx = first_derivative_x(source, y0, x0, 0);
    float dI_dy = first_derivative_y(source, y0, x0, 0);
    
    float d2I_dx2 = second_derivative_xx(source, y0, x0, 0);
    float d2I_dy2 = second_derivative_yy(source, y0, x0, 0);
    float d2I_dxy = second_derivative_xy(source, y0, x0, 0);
    
    float result = I_x0_y0 +
                  dI_dx * dx + 
                  dI_dy * dy + 
                  0.5f * (d2I_dx2 * dx * dx + 
                          2.0f * d2I_dxy * dx * dy + 
                          d2I_dy2 * dy * dy);
    
    return (uchar)(clamp((int)(std::round(result)), 0, 255));
}

template<>
Vec3b Curvature<Vec3b>::new_color(const Mat_<Vec3b> &source, float x, float y) {
    int x0 = (int)(std::floor(x));
    int y0 = (int)(std::floor(y));
    
    x0 = clamp(x0, 0, source.cols - 1);
    y0 = clamp(y0, 0, source.rows - 1);
    
    float dx = x - x0;
    float dy = y - y0;
    
    Vec3b result;
    
    for (int c = 0; c < 3; c++) {
        float I_x0_y0 = get_pixel_value(source, y0, x0, c);
        
        float dI_dx = first_derivative_x(source, y0, x0, c);
        float dI_dy = first_derivative_y(source, y0, x0, c);
        
        float d2I_dx2 = second_derivative_xx(source, y0, x0, c);
        float d2I_dy2 = second_derivative_yy(source, y0, x0, c);
        float d2I_dxy = second_derivative_xy(source, y0, x0, c);
        
        float channel_result = I_x0_y0 +
                              dI_dx * dx + 
                              dI_dy * dy + 
                              0.5f * (d2I_dx2 * dx * dx + 
                                     2.0f * d2I_dxy * dx * dy + 
                                     d2I_dy2 * dy * dy);
        
        result[c] = (uchar)(clamp((int)(std::round(channel_result)), 0, 255));
    }
    
    return result;
}

template<typename Pixel>
Mat Curvature<Pixel>::zoom(const Mat_<Pixel> &source, double scale_factor) {
    int new_rows = (int)(source.rows * scale_factor);
    int new_cols = (int)(source.cols * scale_factor);
    Mat_<Pixel> result(new_rows, new_cols);

    for (int i = 0; i < new_rows; ++i) {
        for (int j = 0; j < new_cols; ++j) {
            float src_y = i / scale_factor;
            float src_x = j / scale_factor;
            
            result(i, j) = new_color(source, src_x, src_y);
        }
    }
    
    return result;
}

template<typename Pixel>
Mat Curvature<Pixel>::shrink(const Mat_<Pixel> &source, double scale_factor) {
    return zoom(source, scale_factor);
}

template<typename Pixel>
Mat Curvature<Pixel>::zoom(const Mat_<Pixel> &source, double scale_factor_x, double scale_factor_y) {
    int new_rows = (int)(source.rows * scale_factor_y);
    int new_cols = (int)(source.cols * scale_factor_x);
    Mat_<Pixel> result(new_rows, new_cols);

    for (int i = 0; i < new_rows; ++i) {
        for (int j = 0; j < new_cols; ++j) {
            float src_y = i / scale_factor_y;
            float src_x = j / scale_factor_x;
            
            result(i, j) = new_color(source, src_x, src_y);
        }
    }
    
    return result;
}

template<typename Pixel>
Mat Curvature<Pixel>::shrink(const Mat_<Pixel> &source, double scale_factor_x, double scale_factor_y) {
    return zoom(source, scale_factor_x, scale_factor_y);
}
