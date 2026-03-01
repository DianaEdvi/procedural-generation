#include <igl/opengl/glfw/Viewer.h>

#include "Grid.h"
#include "PerlinNoise.h"

int main(int argc, char *argv[])
{
  
  Grid grid;

    // Compute Perlin noise values for each vertex in the grid and update the y-coordinate
    PerlinNoise pn(grid.n); // reuse one instance (cheaper and consistent)
    const double scale = 0.15; // scale down coordinates so they're fractional
    for (int i = 0; i < grid.V.rows(); i++){
      double x = grid.V(i, 0) * scale;
      double z = grid.V(i, 2) * scale;
      double y = pn.noise(x, z);
      grid.V(i, 1) = y * 5.0; // scale up the noise value for better visualization
    }

  // Plot the mesh
  igl::opengl::glfw::Viewer viewer;
  viewer.data().set_mesh(grid.V, grid.F);
  viewer.data().set_face_based(true);
  viewer.launch();
}
