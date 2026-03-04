#ifndef TERRAFORMER_H
#define TERRAFORMER_H

#include <Eigen/Dense>

#include "Terrain.h"

struct Brush {
    Brush(){}
    Brush(float rad, float str) : radius(rad), strength(str){} 
    float radius = 20.0f;
    float strength = 10.0f;
    Eigen::Vector3f center;
};

struct Terraformer {
    Terraformer(Terrain& terrain, Brush& brush) :terrain(terrain), brush(brush){}
    Brush& brush;
    Terrain& terrain;
    bool applyBrush(const Eigen::Vector3f& ray_origin, const Eigen::Vector3f& ray_dir);
    void deformTerrain();
};


#endif