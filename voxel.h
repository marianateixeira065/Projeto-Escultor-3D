#ifndef VOXEL_H
#define VOXEL_H

struct Voxel {
    float r, g, b; // Cores na faixa [0, 1]
    float a;       // Transparência na faixa [0, 1]
    bool show;     // Define se o bloco será incluído no modelo
};

#endif // VOXEL_H