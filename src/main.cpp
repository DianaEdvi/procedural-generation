#include <igl/opengl/glfw/Viewer.h>

#include "Grid.h"
#include "PerlinNoise.h"

int main(int argc, char *argv[])
{
  
  igl::opengl::glfw::Viewer viewer;
  Grid grid;
  float horizontalScale = 0.15; // how wide the hills are
  float verticalScale = 5.0; // how tall the hills are 

  // Compute Perlin noise values for each vertex in the grid and update the y-coordinate
  PerlinNoise pn(grid.n); // reuse one instance (cheaper and consistent)
  for (int i = 0; i < grid.V.rows(); i++){
    double x = grid.V(i, 0) * horizontalScale;
    double z = grid.V(i, 2) * horizontalScale;
    double y = pn.noise(x, z);
    grid.V(i, 1) = y * verticalScale; // scale up the noise value for better visualization
  }

  viewer.callback_key_pressed = [&](igl::opengl::glfw::Viewer& v, unsigned int key, int modifiers) -> bool {
        // Check if the 'r' or 'R' key was pressed
        if (key == 'r' || key == 'R') {    
          std::cout << "Regenerating terrain with new Perlin noise values..." << std::endl;
          PerlinNoise pn_new(grid.n); // Create a new PerlinNoise instance with different gradients
          for (int i = 0; i < grid.V.rows(); i++){
              double x = grid.V(i, 0) * horizontalScale;
              double z = grid.V(i, 2) * horizontalScale;
              double y = pn_new.noise(x, z);
              grid.V(i, 1) = y * verticalScale; // scale up the noise value for better visualization
          }

            viewer.data().clear();          
            viewer.data().set_mesh(grid.V, grid.F);
            return true; // Tells libigl we handled this key press
        }
        return false;
    };
  

  // Plot the mesh
  viewer.data().set_mesh(grid.V, grid.F);
  viewer.data().set_face_based(true);
  viewer.launch();
}
