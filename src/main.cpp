#include <igl/opengl/glfw/Viewer.h>

#include "Grid.h"
#include "PerlinNoise.h"

int main(int argc, char *argv[])
{
  
  igl::opengl::glfw::Viewer viewer;
  Grid grid;
  grid.generatePerlinNoise(0.15, 5.0);

  viewer.callback_key_pressed = [&](igl::opengl::glfw::Viewer& v, unsigned int key, int modifiers) -> bool {
        // Check if the 'r' or 'R' key was pressed
        if (key == 'r' || key == 'R') {    
            std::cout << "Regenerating terrain with new Perlin noise values..." << std::endl;
            grid.generatePerlinNoise(0.15, 5.0); // regenerate the terrain with new noise values
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
