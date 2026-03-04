#ifndef TERRAFORMER_H
#define TERRAFORMER_H

#include <Eigen/Dense>

struct Brush {
    float radius = 1.0f;
    float strength = 0.5f;
};

struct Terraformer {
    Terraformer() {}
    Terraformer(float r, float s) : brush{r, s} {}
    Brush brush;
    bool applyBrush(const Eigen::Vector3f& ray_origin, const Eigen::Vector3f& ray_dir);
};


#endif