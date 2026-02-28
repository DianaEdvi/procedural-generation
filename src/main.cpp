#include <igl/opengl/glfw/Viewer.h>

#include "Grid.h"

int main(int argc, char *argv[])
{
  
  Grid grid;
  // Plot the mesh
  igl::opengl::glfw::Viewer viewer;
  viewer.data().set_mesh(grid.V, grid.F);
  viewer.data().set_face_based(true);
  viewer.launch();
}
