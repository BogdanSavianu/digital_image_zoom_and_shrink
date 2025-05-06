//
// Created by Bogdan Savianu on 05.04.2025.
//

#ifndef PROJECT_BILINEAR_H
#define PROJECT_BILINEAR_H

#include "../resizer/Resizer.h"
#include "../utils/utils.h"

template <typename Pixel>
class Bilinear : Resizer<Pixel>{
public:
    static Bilinear<Pixel>& getInstance(){
        static Bilinear<Pixel> instance;
        return instance;
    }

    Bilinear(const Bilinear&) = delete;
    Bilinear& operator=(const Bilinear&) = delete;

    Mat zoom(const Mat_<Pixel> &source, double scale_factor) override;
    Mat shrink(const Mat_<Pixel> &source, double scale_factor) override;
    
    Mat zoom(const Mat_<Pixel> &source, double scale_factor_x, double scale_factor_y) override;
    Mat shrink(const Mat_<Pixel> &source, double scale_factor_x, double scale_factor_y) override;
    
    inline Pixel new_color(Pixel neigh[4], float alpha, float beta);

private:
    Bilinear() = default;

    static constexpr const int n4_di[4] = {0, 0, 1, 1};
    static constexpr const int n4_dj[4] = {0, 1, 0, 1};
};

#include "Bilinear.ipp"

#endif //PROJECT_BILINEAR_H
