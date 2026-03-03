#ifndef PERLIN_NOISE_H
#define PERLIN_NOISE_H

#include <iostream>
#include <vector>
#include <Eigen/Dense>


class PerlinNoise {
    public:
        PerlinNoise(int n);  
        double noise(double x, double y) const;
        Eigen::Vector2d pseudoRandomGradient(int ix, int iy) const;
        void populateGradients();
        double fade(double t) const;
        PerlinNoise operator+(const PerlinNoise& P);
    private:
        int n;
        std::vector<std::vector<Eigen::Vector2d>> gradients;

};
#endif