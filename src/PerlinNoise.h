#ifndef PERLIN_NOISE_H
#define PERLIN_NOISE_H

#include <iostream>
#include <vector>
#include <Eigen/Dense>


class PerlinNoise {
    public:
    PerlinNoise(int n);  
        double noise(double x, double y);
        Eigen::Vector2d pseudoRandomGradient(int ix, int iy);
        void populateGradients();
        double fade(double t);
    private:
        int n;
        std::vector<std::vector<Eigen::Vector2d>> gradients;

};
#endif