#ifndef VOXEL_H
#define VOXEL_H

/**
 * @brief Estrutura Voxel
 * * Representa um elemento volumétrico tridimensional (o equivalente 3D de um pixel).
 * Armazena a cor, a transparência e o estado de visibilidade do bloco.
 */
struct Voxel {
    float r; /**< @brief Intensidade da cor vermelha (0.0 a 1.0) */
    float g; /**< @brief Intensidade da cor verde (0.0 a 1.0) */
    float b; /**< @brief Intensidade da cor azul (0.0 a 1.0) */
    float a; /**< @brief Transparência (Canal Alfa) do bloco (0.0 a 1.0) */
    bool show; /**< @brief Define se o bloco será desenhado (true) ou apagado (false) */
};

#endif
