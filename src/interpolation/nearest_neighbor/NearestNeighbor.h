//
// Created by Bogdan Savianu on 05.04.2025.
//

#ifndef PROJECT_NEARESTNEIGHBOR_H
#define PROJECT_NEARESTNEIGHBOR_H

#include "../resizer/Resizer.h"

template<typename Pixel>
class NearestNeighbor : Resizer<Pixel> {
public:
    static NearestNeighbor<Pixel>& getInstance() {
        static NearestNeighbor<Pixel> instance;
        return instance;
    }
    
    NearestNeighbor(const NearestNeighbor&) = delete;
    NearestNeighbor& operator=(const NearestNeighbor&) = delete;
    
    Mat zoom(const Mat_<Pixel> &source, double scale_factor) override;
    Mat shrink(const Mat_<Pixel> &source, double scale_factor) override;
    
    Mat zoom(const Mat_<Pixel> &source, double scale_factor_x, double scale_factor_y) override;
    Mat shrink(const Mat_<Pixel> &source, double scale_factor_x, double scale_factor_y) override;

private:
    NearestNeighbor() = default;
};

#include "NearestNeighbor.ipp"

#endif //PROJECT_NEARESTNEIGHBOR_H
