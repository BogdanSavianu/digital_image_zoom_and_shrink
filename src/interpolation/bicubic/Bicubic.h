//
// Created by Bogdan Savianu on 22.04.2025.
//

#ifndef PROJECT_BICUBIC_H
#define PROJECT_BICUBIC_H

#include "../resizer/Resizer.h"

template<typename Pixel>
class Bicubic : Resizer<Pixel> {
public:
    static Bicubic<Pixel>& getInstance(){
        static Bicubic<Pixel> instance;
        return instance;
    }

    Bicubic(const Bicubic&) = delete;
    Bicubic& operator=(const Bicubic&) = delete;

    Mat zoom(const Mat_<Pixel> &source, double scale_factor) override;
    Mat shrink(const Mat_<Pixel> &source, double scale_factor) override;

    Mat zoom(const Mat_<Pixel> &source, double scale_factor_x, double scale_factor_y) override;
    Mat shrink(const Mat_<Pixel> &source, double scale_factor_x, double scale_factor_y) override;

    inline Pixel new_color(Pixel *neigh, float alpha, float beta);

    float cubic_weight(float x);
    float cubic_weight(Point p);
    
private:
    Bicubic() = default;

    static constexpr const int d16i[] = {-1,-1,-1,-1,0,0,0,0,1,1,1,1,2,2,2,2};
    static constexpr const int d16j[] = {-1,0,1,2,-1,0,1,2,-1,0,1,2,-1,0,1,2};
};

#include "Bicubic.ipp"

#endif //PROJECT_BICUBIC_H