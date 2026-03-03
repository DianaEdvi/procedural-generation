#ifndef TERRAIN_H
#define TERRAIN_H

#include <Eigen/Dense>
#include "PerlinNoise.h"

#include <vector>
#include <iostream>

// Define a new Row-Major dynamic matrix type (Cache locality optimization for sparse solvers)
typedef Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> MatrixXdRow;

struct Level {
    Level(float frequency, float amplitude) : frequency(frequency), amplitude(amplitude) {}
    float frequency;
    float amplitude;
};

struct Terrain {
    Terrain();
    int n = 100;
    int width = 1;
    MatrixXdRow V;
    Eigen::MatrixXi F;
    std::vector<Level> levels;

    void generateTerrain(const std::vector<PerlinNoise>& noiseLevels);

};


#endif