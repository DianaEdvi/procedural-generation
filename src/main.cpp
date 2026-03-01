#include <igl/opengl/glfw/Viewer.h>

#include "Grid.h"
#include "PerlinNoise.h"

Grid grid;

int main(int argc, char *argv[])
{
  
  igl::opengl::glfw::Viewer viewer;

  Level lvl0(0.5, 2.0f);
  Level lvl1(0.05, 10.0f);
  Level lvl2(0.02, 40.0f);

  PerlinNoise level0(grid.n);
  PerlinNoise level1(grid.n);
  PerlinNoise level2(grid.n);

  for (int i = 0; i < grid.V.rows(); i++){
            double x0 = grid.V(i, 0) * lvl0.frequency;
            double z0 = grid.V(i, 2) * lvl0.frequency;
            double y0 = level0.noise(x0, z0);
            grid.V(i, 1) = y0 * lvl0.amplitude; 

            double x1 = grid.V(i, 0) * lvl1.frequency;
            double z1 = grid.V(i, 2) * lvl1.frequency;
            double y1 = level1.noise(x1, z1);
            grid.V(i, 1) += y1 * lvl1.amplitude; 

            double x2 = grid.V(i, 0) * lvl2.frequency;
            double z2 = grid.V(i, 2) * lvl2.frequency;
            double y2 = level2.noise(x2, z2);
            grid.V(i, 1) += y2 * lvl2.amplitude; 
  }
  
    viewer.callback_key_pressed = [&](igl::opengl::glfw::Viewer& v, unsigned int key, int modifiers) -> bool {
      // Check if the 'r' or 'R' key was pressed
      if (key == 'r' || key == 'R') {
          PerlinNoise level0(grid.n);
          PerlinNoise level1(grid.n);
          PerlinNoise level2(grid.n);
          for (int i = 0; i < grid.V.rows(); i++){
            double x0 = grid.V(i, 0) * lvl0.frequency;
            double z0 = grid.V(i, 2) * lvl0.frequency;
            double y0 = level0.noise(x0, z0);
            grid.V(i, 1) = y0 * lvl0.amplitude; 

            double x1 = grid.V(i, 0) * lvl1.frequency;
            double z1 = grid.V(i, 2) * lvl1.frequency;
            double y1 = level1.noise(x1, z1);
            grid.V(i, 1) += y1 * lvl1.amplitude; 

            double x2 = grid.V(i, 0) * lvl2.frequency;
            double z2 = grid.V(i, 2) * lvl2.frequency;
            double y2 = level2.noise(x2, z2);
            grid.V(i, 1) += y2 * lvl2.amplitude; 
        }
        v.data().clear();
        v.data().set_mesh(grid.V, grid.F);
        return true; // Tells libigl we handled this key press
      }
      return false;
    };
  

  // Plot the mesh
  viewer.data().set_mesh(grid.V, grid.F);
  viewer.data().set_face_based(true);
  viewer.launch();
}
