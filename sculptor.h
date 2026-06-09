#ifndef SCULPTOR_H
#define SCULPTOR_H

#include "voxel.h"
#include <string>

/**
 * @brief A classe Sculptor monta uma matriz tridimensional de Voxels.
 * * Permite criar, manipular e exportar esculturas 3D baseadas em blocos (voxels)
 * para o formato .OFF, que pode ser lido por softwares de visualização 3D.
 */
class Sculptor {
private:
    Voxel ***v;       /**< @brief Matriz tridimensional dinâmica de Voxels */
    int nx, ny, nz;   /**< @brief Dimensões da matriz nos eixos X, Y e Z */
    float r, g, b, a; /**< @brief Cores (vermelho, verde, azul) e transparência (alfa) atuais do desenho */

public:
    /**
     * @brief Construtor da classe Sculptor.
     * * Aloca dinamicamente a matriz tridimensional com as dimensões especificadas.
     * * @param _nx Dimensão no eixo X.
     * @param _ny Dimensão no eixo Y.
     * @param _nz Dimensão no eixo Z.
     */
    Sculptor(int _nx, int _ny, int _nz);

    /**
     * @brief Destrutor da classe Sculptor.
     * * Liberta a memória alocada dinamicamente para a matriz tridimensional.
     */
    ~Sculptor();

    /**
     * @brief Define a cor e a transparência atuais para os próximos blocos a serem desenhados.
     * * @param r Intensidade da cor vermelha (0.0 a 1.0).
     * @param g Intensidade da cor verde (0.0 a 1.0).
     * @param b Intensidade da cor azul (0.0 a 1.0).
     * @param a Transparência / Canal Alfa (0.0 a 1.0).
     */
    void setColor(float r, float g, float b, float a);

    /**
     * @brief Ativa (desenha) um voxel na posição (x, y, z) com a cor atual.
     * * @param x Coordenada no eixo X.
     * @param y Coordenada no eixo Y.
     * @param z Coordenada no eixo Z.
     */
    void putVoxel(int x, int y, int z);

    /**
     * @brief Desativa (apaga) um voxel na posição (x, y, z).
     * * @param x Coordenada no eixo X.
     * @param y Coordenada no eixo Y.
     * @param z Coordenada no eixo Z.
     */
    void cutVoxel(int x, int y, int z);

    /**
     * @brief Ativa um bloco (paralelepípedo) maciço de voxels.
     * * @param x0 Coordenada inicial no eixo X.
     * @param x1 Coordenada final no eixo X.
     * @param y0 Coordenada inicial no eixo Y.
     * @param y1 Coordenada final no eixo Y.
     * @param z0 Coordenada inicial no eixo Z.
     * @param z1 Coordenada final no eixo Z.
     */
    void putBox(int x0, int x1, int y0, int y1, int z0, int z1);

    /**
     * @brief Desativa um bloco (paralelepípedo) maciço de voxels.
     * * @param x0 Coordenada inicial no eixo X.
     * @param x1 Coordenada final no eixo X.
     * @param y0 Coordenada inicial no eixo Y.
     * @param y1 Coordenada final no eixo Y.
     * @param z0 Coordenada inicial no eixo Z.
     * @param z1 Coordenada final no eixo Z.
     */
    void cutBox(int x0, int x1, int y0, int y1, int z0, int z1);

    /**
     * @brief Ativa uma esfera maciça de voxels.
     * * @param xcenter Coordenada X do centro da esfera.
     * @param ycenter Coordenada Y do centro da esfera.
     * @param zcenter Coordenada Z do centro da esfera.
     * @param radius Raio da esfera.
     */
    void putSphere(int xcenter, int ycenter, int zcenter, int radius);

    /**
     * @brief Desativa uma esfera maciça de voxels.
     * * @param xcenter Coordenada X do centro da esfera.
     * @param ycenter Coordenada Y do centro da esfera.
     * @param zcenter Coordenada Z do centro da esfera.
     * @param radius Raio da esfera.
     */
    void cutSphere(int xcenter, int ycenter, int zcenter, int radius);

    /**
     * @brief Ativa uma elipsoide maciça de voxels.
     * * @param xcenter Coordenada X do centro da elipsoide.
     * @param ycenter Coordenada Y do centro da elipsoide.
     * @param zcenter Coordenada Z do centro da elipsoide.
     * @param rx Raio no eixo X.
     * @param ry Raio no eixo Y.
     * @param rz Raio no eixo Z.
     */
    void putEllipsoid(int xcenter, int ycenter, int zcenter, int rx, int ry, int rz);

    /**
     * @brief Desativa uma elipsoide maciça de voxels.
     * * @param xcenter Coordenada X do centro da elipsoide.
     * @param ycenter Coordenada Y do centro da elipsoide.
     * @param zcenter Coordenada Z do centro da elipsoide.
     * @param rx Raio no eixo X.
     * @param ry Raio no eixo Y.
     * @param rz Raio no eixo Z.
     */
    void cutEllipsoid(int xcenter, int ycenter, int zcenter, int rx, int ry, int rz);

    /**
     * @brief Exporta a escultura tridimensional para um ficheiro no formato .OFF.
     * * @param filename Nome do ficheiro com a extensão .off a ser gerado.
     */
    void writeOFF(const char* filename);
};

#endif
