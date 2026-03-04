#include "Terraformer.h"

#include <igl/Hit.h>
#include <igl/ray_mesh_intersect.h>


bool Terraformer::applyBrush(const Eigen::Vector3f& ray_origin, const Eigen::Vector3f& ray_dir) {
    igl::Hit<double> hit;

    if (igl::ray_mesh_intersect(ray_origin, ray_dir, terrain.V, terrain.F, hit)) {
        Eigen::Vector3f hitPoint = ray_origin + hit.t * ray_dir;
        std::cout << "Hit point: " << hitPoint.transpose() << std::endl;
        // TODO: apply brush influence using 'brush.radius' and 'hitPoint'
        return true;
    }
    return false;
}
