#include "PerlinNoise.h"

#include <cmath>
#include <cstdlib>
#include <corecrt_math_defines.h>

PerlinNoise::PerlinNoise(int n) : n(n), gradients(n, std::vector<Eigen::Vector2d>(n)) {
    populateGradients();
}

// Take an integral coordinate and return a pseudo-random gradient vector from the pre-populated grid
Eigen::Vector2d PerlinNoise::pseudoRandomGradient(int ix, int iy) {
    int ixm = ((ix % n) + n) % n;
    int iym = ((iy % n) + n) % n;
    return gradients[ixm][iym];
}

double PerlinNoise::noise(double x, double y) {
    int x0 = static_cast<int>(std::floor(x));
    int x1i = x0 + 1;
    int y0 = static_cast<int>(std::floor(y));
    int y1i = y0 + 1;

    double posX = x - x0; // Relative x coordinate in the unit square
    double posY = y - y0; // Relative y coordinate in the unit square

    Eigen::Vector2d g00 = pseudoRandomGradient(x0, y0);
    Eigen::Vector2d g10 = pseudoRandomGradient(x1i, y0);
    Eigen::Vector2d g01 = pseudoRandomGradient(x0, y1i);
    Eigen::Vector2d g11 = pseudoRandomGradient(x1i, y1i);

    Eigen::Vector2d d00(posX, posY);
    Eigen::Vector2d d10(posX - 1.0, posY);
    Eigen::Vector2d d01(posX, posY - 1.0);
    Eigen::Vector2d d11(posX - 1.0, posY - 1.0);

    double n00 = g00.dot(d00);
    double n10 = g10.dot(d10);
    double n01 = g01.dot(d01);
    double n11 = g11.dot(d11);

    double u = fade(posX);
    double v = fade(posY);

    double ix1 = n00 + u * (n10 - n00);
    double ix2 = n01 + u * (n11 - n01);

    return ix1 + v * (ix2 - ix1);
}

// Pre-populate the gradient vectors for the grid points
void PerlinNoise::populateGradients() {
    srand(time(NULL)); // Seed the random number generator
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            double angle = (static_cast<double>(rand()) / RAND_MAX) * 2.0 * M_PI;
            Eigen::Vector2d gradient(std::cos(angle), std::sin(angle));
            gradients[i][j] = gradient;
        }
    }
}

// Fade function as defined by Ken Perlin.
double PerlinNoise::fade(double t) {
    return t * t * t * (t * (t * 6 - 15) + 10);
}



