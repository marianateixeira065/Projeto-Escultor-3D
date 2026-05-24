#ifndef SCULPTOR_H
#define SCULPTOR_H

#include "voxel.h"

class Sculptor 
{
private:
    Voxel ***v;       // Matriz 3D
    int nx, ny, nz;   // Dimensões
    float r, g, b, a; // Cor atual do desenho

public:
    // Construtor: responsável pela alocação dinâmica
    Sculptor(int _nx, int _ny, int _nz);
    
    // Destrutor: responsável por liberar a memória
    ~Sculptor();
    
    void writeOFF(const char* filename);
    void setColor(float r, float g, float b, float a);
    void putVoxel(int x, int y, int z);
    void cutVoxel(int x, int y, int z);

    // Ferramentas de criação de blocos em massa
    void putBox(int x0, int x1, int y0, int y1, int z0, int z1);
    void cutBox(int x0, int x1, int y0, int y1, int z0, int z1);

    // Ferramentas de criação de esferas
    void putSphere(int xcenter, int ycenter, int zcenter, int radius);
    void cutSphere(int xcenter, int ycenter, int zcenter, int radius);

    void putEllipsoid(int xcenter, int ycenter, int zcenter, int rx, int ry, int rz);
    void cutEllipsoid(int xcenter, int ycenter, int zcenter, int rx, int ry, int rz);

};

#endif // SCULPTOR_H