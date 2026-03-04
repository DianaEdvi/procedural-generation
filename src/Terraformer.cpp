#include "Terraformer.h"

#include <igl/Hit.h>
#include <igl/ray_mesh_intersect.h>


bool Terraformer::applyBrush(const Eigen::Vector3f& ray_origin, const Eigen::Vector3f& ray_dir) {
    igl::Hit<double> hit;

    if (igl::ray_mesh_intersect(ray_origin.cast<double>(), ray_dir.cast<double>(), terrain.V, terrain.F, hit)) {
        
        float t_f = static_cast<float>(hit.t);
        Eigen::Vector3f hitPoint = ray_origin + t_f * ray_dir;
        
        // Get indices from face matrix
        int i0 = terrain.F(hit.id, 0);
        int i1 = terrain.F(hit.id, 1);
        int i2 = terrain.F(hit.id, 2);

        // Look up vertices
        Eigen::Vector3f v0 = terrain.V.row(i0).cast<float>();
        Eigen::Vector3f v1 = terrain.V.row(i1).cast<float>();
        Eigen::Vector3f v2 = terrain.V.row(i2).cast<float>();
        
        // Use static_cast for barycentric coordinates
        float u_f = static_cast<float>(hit.u);
        float v_f = static_cast<float>(hit.v);
        float w_f = 1.0f - u_f - v_f;
        
        // Calculate center
        Eigen::Vector3f brushCenter = (v0 * w_f) + (v1 * u_f) + (v2 * v_f);
        
        std::cout << "Brush center: " << brushCenter.transpose() << std::endl;
        return true;
    }
    return false;
}