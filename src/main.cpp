#include <igl/opengl/glfw/Viewer.h>
#include <vector>

#include "Terrain.h"
#include "PerlinNoise.h"
#include "Terraformer.h"

Terrain terrain;

int main(int argc, char *argv[])
{
    igl::opengl::glfw::Viewer viewer;
    Brush brush;
    Terraformer terraformer(terrain, brush);

    // Initialize noise generators for each terrain level
    std::vector<PerlinNoise> noiseLevels;
    for (const auto& level : terrain.levels) {
        noiseLevels.emplace_back(terrain.n);
    }

    // Generate initial terrain
    terrain.generateTerrain(noiseLevels);

    viewer.callback_key_pressed = [&](igl::opengl::glfw::Viewer& v, unsigned int key, int modifiers) -> bool {
        // Regenerate terrain on 'r' or 'R' key press
        if (key == 'r' || key == 'R') {
            std::vector<PerlinNoise> newNoiseLevels;
            for (const auto& level : terrain.levels) {
                newNoiseLevels.emplace_back(terrain.n);
            }
            terrain.generateTerrain(newNoiseLevels);
            
            v.data().clear();
            v.data().set_mesh(terrain.V, terrain.F);
            return true;
        }
        return false;
    };

    bool brushEnabled = false; 

    viewer.callback_key_up = [&](igl::opengl::glfw::Viewer& viewer, unsigned char key, int modifier) -> bool 
    {    
      // Toggle brush mode
        if (key == 'X' || key == 'x') { 
            brushEnabled = !brushEnabled;
            std::cout << "Brush Mode: " << (brushEnabled ? "ON" : "OFF") << std::endl;
            
            return true;
        }
        return false;
    };

    viewer.callback_mouse_down = [&](igl::opengl::glfw::Viewer& v, int button, int mod) -> bool {
        if (brushEnabled){
          Eigen::Vector3d nearPlane; 
          Eigen::Vector3d farPlane; 
          float mouseY = viewer.core().viewport(3) - (float)viewer.current_mouse_y;

          // Get the NDC's of the near and far planes 
          igl::unproject(Eigen::Vector3d(v.current_mouse_x, mouseY, 0.0f), viewer.core().view, viewer.core().proj, viewer.core().viewport, nearPlane);
          igl::unproject(Eigen::Vector3d(v.current_mouse_x, mouseY, 1.0f), viewer.core().view, viewer.core().proj, viewer.core().viewport, farPlane);
          Eigen::Vector3d dir = farPlane - nearPlane;
          dir.normalize();
          
          terraformer.applyBrush(nearPlane.cast<float>(), dir.cast<float>());

          return true;
        }  

      return false;
    };

    // Plot the mesh
    viewer.data().set_mesh(terrain.V, terrain.F);
    viewer.data().set_face_based(true);
    viewer.launch();
}
