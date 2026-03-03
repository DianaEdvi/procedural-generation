#include <igl/opengl/glfw/Viewer.h>
#include <vector>

#include "Grid.h"
#include "PerlinNoise.h"

// Terrain generation parameters
const std::vector<Level> TERRAIN_LEVELS = {
    Level(0.5f, 2.0f),
    Level(0.05f, 10.0f),
    Level(0.02f, 40.0f)
};

Grid grid;

// Generate terrain using multi-level Perlin noise
void generateTerrain(const std::vector<PerlinNoise>& noiseLevels) {
    for (int i = 0; i < grid.V.rows(); i++) {
        grid.V(i, 1) = 0.0; // Reset height
        
        for (size_t level = 0; level < noiseLevels.size(); level++) {
            double x = grid.V(i, 0) * TERRAIN_LEVELS[level].frequency;
            double z = grid.V(i, 2) * TERRAIN_LEVELS[level].frequency;
            double height = noiseLevels[level].noise(x, z);
            grid.V(i, 1) += height * TERRAIN_LEVELS[level].amplitude;
        }
    }
}

int main(int argc, char *argv[])
{
    igl::opengl::glfw::Viewer viewer;

    // Initialize noise generators for each terrain level
    std::vector<PerlinNoise> noiseLevels;
    for (const auto& level : TERRAIN_LEVELS) {
        noiseLevels.emplace_back(grid.n);
    }

    // Generate initial terrain
    generateTerrain(noiseLevels);

    viewer.callback_key_pressed = [&](igl::opengl::glfw::Viewer& v, unsigned int key, int modifiers) -> bool {
        // Regenerate terrain on 'r' or 'R' key press
        if (key == 'r' || key == 'R') {
            std::vector<PerlinNoise> newNoiseLevels;
            for (const auto& level : TERRAIN_LEVELS) {
                newNoiseLevels.emplace_back(grid.n);
            }
            generateTerrain(newNoiseLevels);
            
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
