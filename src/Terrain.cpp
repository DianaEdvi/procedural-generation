#include "Terrain.h"
#include "PerlinNoise.h"

Terrain::Terrain() : V((n + 1) * (n + 1), 3), F(n * n * 2, 3){
    for (int i = 0; i < n + 1; i++){
        for (int j = 0; j < n + 1; j++){
            Eigen::Vector3d vertex(i * width, 0.0, j * width);
            V.row(i * (n + 1) + j) = vertex;
        }
    }

    int currentFace = 0;
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            // Triangle 1 
            int p1 = i * (n + 1) + j;
            int p2 = i * (n + 1) + j + 1;
            int p3 = i * (n + 1) + j + n + 1;

            Eigen::Vector3i face1(p1, p2, p3);
            F.row(currentFace) = face1;
            
            // Triangle 2 
            int q1 = i * (n + 1) + j + n + 1;
            int q2 = i * (n + 1) + j + 1;
            int q3 = i * (n + 1) + j + n + 2;
            Eigen::Vector3i face2(q1, q2, q3);
            F.row(currentFace + 1) = face2;
            currentFace += 2;
        }
    }

    // Terrain generation parameters
    levels = {
    Level(0.5f, 2.0f),
    Level(0.05f, 10.0f),
    Level(0.02f, 40.0f)
    };
}

// Generate terrain using multi-level Perlin noise
void Terrain::generateTerrain(const std::vector<PerlinNoise>& noiseLevels) {
    for (int i = 0; i < V.rows(); i++) {
        V(i, 1) = 0.0; // Reset height
        
        for (size_t level = 0; level < noiseLevels.size(); level++) {
            double x = V(i, 0) * levels[level].frequency;
            double z = V(i, 2) * levels[level].frequency;
            double height = noiseLevels[level].noise(x, z);
            V(i, 1) += height * levels[level].amplitude;
        }
    }
}
