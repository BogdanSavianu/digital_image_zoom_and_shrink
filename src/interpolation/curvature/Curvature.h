//
// Created by Bogdan Savianu on 04.05.2025.
//

#ifndef PROJECT_CURVATURE_H
#define PROJECT_CURVATURE_H

#include "../resizer/Resizer.h"

template<typename Pixel>
class Curvature : Resizer<Pixel> {
public:
    static Curvature<Pixel>& getInstance(){
        static Curvature<Pixel> instance;
        return instance;
    }

    Curvature(const Curvature&) = delete;
    Curvature& operator=(const Curvature&) = delete;

    Mat zoom(const Mat_<Pixel> &source, double scale_factor) override;
    Mat shrink(const Mat_<Pixel> &source, double scale_factor) override;

    Mat zoom(const Mat_<Pixel> &source, double scale_factor_x, double scale_factor_y) override;
    Mat shrink(const Mat_<Pixel> &source, double scale_factor_x, double scale_factor_y) override;

    Pixel new_color(const Mat_<Pixel> &source, float x, float y);
    
    float first_derivative_x(const Mat_<Pixel> &source, int i, int j, int channel);
    float first_derivative_y(const Mat_<Pixel> &source, int i, int j, int channel);
    
    float second_derivative_xx(const Mat_<Pixel> &source, int i, int j, int channel);
    float second_derivative_yy(const Mat_<Pixel> &source, int i, int j, int channel);
    float second_derivative_xy(const Mat_<Pixel> &source, int i, int j, int channel);
    
    inline float curvature_weight(float x);
    float second_derivative(const Mat_<Pixel> &source, int i, int j, int channel, bool is_x_direction);
    
private:
    Curvature() = default;
    
    static constexpr const float sigma = 2.5f;
    static constexpr const int kernel_size = 5;
    static constexpr const float epsilon = 1e-6f;
    static constexpr const float curvature_emphasis = 1.5f;

    int clamp(int value, int min_val, int max_val);
    float get_pixel_value(const Mat_<Pixel> &source, int i, int j, int channel);
};

#include "Curvature.ipp"

#endif //PROJECT_CURVATURE_H
