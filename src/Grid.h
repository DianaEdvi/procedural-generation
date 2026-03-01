#ifndef GRID_H
#define GRID_H

#include <Eigen/Dense>

// Define a new Row-Major dynamic matrix type (Cache locality optimization for sparse solvers)
typedef Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> MatrixXdRow;

struct Grid {
    Grid();
    int n = 100;
    int width = 1;
    MatrixXdRow V;
    Eigen::MatrixXi F;
    void generatePerlinNoise(float frequency, float amplitude);
};

#endif