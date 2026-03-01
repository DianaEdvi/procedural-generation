#include "Grid.h"
#include "PerlinNoise.h"

Grid::Grid() : V((n + 1) * (n + 1), 3), F(n * n * 2, 3){
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
}

void Grid::generatePerlinNoise(float frequency, float amplitude){
        // Compute Perlin noise values for each vertex in the grid and update the y-coordinate
        PerlinNoise pn(n); // reuse one instance (cheaper and consistent)
        for (int i = 0; i < V.rows(); i++){
            double x = V(i, 0) * frequency;
            double z = V(i, 2) * frequency;
            double y = pn.noise(x, z);
            V(i, 1) = y * amplitude; // scale up the noise value for better visualization
        }
}
