#include <igl/opengl/glfw/Viewer.h>
#include <vector>

#include "Terrain.h"
#include "PerlinNoise.h"

Terrain grid;

int main(int argc, char *argv[])
{
    igl::opengl::glfw::Viewer viewer;

    // Initialize noise generators for each terrain level
    std::vector<PerlinNoise> noiseLevels;
    for (const auto& level : grid.levels) {
        noiseLevels.emplace_back(grid.n);
    }

    // Generate initial terrain
    grid.generateTerrain(noiseLevels);

    viewer.callback_key_pressed = [&](igl::opengl::glfw::Viewer& v, unsigned int key, int modifiers) -> bool {
        // Regenerate terrain on 'r' or 'R' key press
        if (key == 'r' || key == 'R') {
            std::vector<PerlinNoise> newNoiseLevels;
            for (const auto& level : grid.levels) {
                newNoiseLevels.emplace_back(grid.n);
            }
            grid.generateTerrain(newNoiseLevels);
            
            v.data().clear();
            v.data().set_mesh(grid.V, grid.F);
            return true;
        }
        return false;
    };

    // Plot the mesh
    viewer.data().set_mesh(grid.V, grid.F);
    viewer.data().set_face_based(true);
    viewer.launch();
}
