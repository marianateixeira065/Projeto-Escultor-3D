#include "sculptor.h"
#include <fstream> // Biblioteca para gravação de arquivos
#include <cmath>
#include <iostream>

// --- CONSTRUTOR: Alocação de Memória ---
Sculptor::Sculptor(int _nx, int _ny, int _nz) 
{
    nx = _nx;
    ny = _ny;
    nz = _nz;

    // 1. Aloca as "fatias" no eixo X (um array de ponteiros duplos)
    v = new Voxel**[nx];

    for (int i = 0; i < nx; i++) {
        // 2. Aloca as "linhas" no eixo Y para cada fatia X (um array de ponteiros)
        v[i] = new Voxel*[ny];

        for (int j = 0; j < ny; j++) {
            // 3. Aloca os blocos finais no eixo Z para cada linha Y
            v[i][j] = new Voxel[nz];

            // 4. Inicializar os voxels com valores padrão
            for (int k = 0; k < nz; k++) {
                v[i][j][k].r = 0.0;
                v[i][j][k].g = 0.0;
                v[i][j][k].b = 0.0;
                v[i][j][k].a = 0.0;
                v[i][j][k].show = false; // Começa apagado
            }
        }
    }
}

// --- DESTRUTOR: Liberação de Memória ---
Sculptor::~Sculptor() {
    // Para liberar a memória, fazemos o caminho inverso da alocação!
    for (int i = 0; i < nx; i++) {
        for (int j = 0; j < ny; j++) {
            // 1. Deleta os blocos do eixo Z
            delete[] v[i][j];
        }
        // 2. Deleta as linhas do eixo Y
        delete[] v[i];
    }
    // 3. Deleta as fatias do eixo X
    delete[] v;
}


//writeOFF

void Sculptor::writeOFF(const char* filename) {
    // 1. Abre o arquivo para gravação
    std::ofstream fout(filename);

    if (!fout.is_open()) {
        std::cout << "Erro ao abrir o arquivo " << filename << std::endl;
        return;
    }

    int activeVoxels = 0;

    // 2. Conta quantos voxels estão ativos para o cabeçalho
    for (int x = 0; x < nx; x++) {
        for (int y = 0; y < ny; y++) {
            for (int z = 0; z < nz; z++) {
                if (v[x][y][z].show) {
                    activeVoxels++;
                }
            }
        }
    }

    // 3. Escreve o cabeçalho do formato OFF [cite: 242, 441]
    fout << "OFF" << std::endl;
    // Vértices totais = ativos * 8, Faces totais = ativos * 6, Arestas = 0 [cite: 124, 125, 242]
    fout << activeVoxels * 8 << " " << activeVoxels * 6 << " 0" << std::endl; 

    // 4. Escreve as coordenadas espaciais de todos os vértices [cite: 126]
    for (int x = 0; x < nx; x++) {
        for (int y = 0; y < ny; y++) {
            for (int z = 0; z < nz; z++) {
                if (v[x][y][z].show) {
                    // Calcula os 8 vértices do cubo centrado em (x,y,z) [cite: 428, 432]
                    fout << x - 0.5 << " " << y + 0.5 << " " << z - 0.5 << std::endl; // P0
                    fout << x - 0.5 << " " << y - 0.5 << " " << z - 0.5 << std::endl; // P1
                    fout << x + 0.5 << " " << y - 0.5 << " " << z - 0.5 << std::endl; // P2
                    fout << x + 0.5 << " " << y + 0.5 << " " << z - 0.5 << std::endl; // P3
                    fout << x - 0.5 << " " << y + 0.5 << " " << z + 0.5 << std::endl; // P4
                    fout << x - 0.5 << " " << y - 0.5 << " " << z + 0.5 << std::endl; // P5
                    fout << x + 0.5 << " " << y - 0.5 << " " << z + 0.5 << std::endl; // P6
                    fout << x + 0.5 << " " << y + 0.5 << " " << z + 0.5 << std::endl; // P7
                }
            }
        }
    }

    // 5. Escreve as faces de cada cubo com suas respectivas cores [cite: 127]
    int currentVoxel = 0; // Usado para deslocar os índices dos vértices

    for (int x = 0; x < nx; x++) {
        for (int y = 0; y < ny; y++) {
            for (int z = 0; z < nz; z++) {
                if (v[x][y][z].show) {
                    // O offset garante que o segundo cubo ligue os vértices de 8 a 15, o terceiro de 16 a 23, etc. 
                    int offset = currentVoxel * 8;
                    
                    // Pegando as propriedades de cor do Voxel atual
                    float r = v[x][y][z].r;
                    float g = v[x][y][z].g;
                    float b = v[x][y][z].b;
                    float a = v[x][y][z].a;

                    // Escreve as 6 faces seguindo a regra da mão direita [cite: 437, 439]
                    // Formato: 4 vértices + índices + cores r g b a [cite: 128, 129, 130]
                    fout << "4 " << offset + 0 << " " << offset + 3 << " " << offset + 2 << " " << offset + 1 << " " << r << " " << g << " " << b << " " << a << std::endl; // Traseira
                    fout << "4 " << offset + 4 << " " << offset + 5 << " " << offset + 6 << " " << offset + 7 << " " << r << " " << g << " " << b << " " << a << std::endl; // Frontal
                    fout << "4 " << offset + 0 << " " << offset + 1 << " " << offset + 5 << " " << offset + 4 << " " << r << " " << g << " " << b << " " << a << std::endl; // Esquerda
                    fout << "4 " << offset + 0 << " " << offset + 4 << " " << offset + 7 << " " << offset + 3 << " " << r << " " << g << " " << b << " " << a << std::endl; // Superior
                    fout << "4 " << offset + 3 << " " << offset + 7 << " " << offset + 6 << " " << offset + 2 << " " << r << " " << g << " " << b << " " << a << std::endl; // Direita
                    fout << "4 " << offset + 1 << " " << offset + 2 << " " << offset + 6 << " " << offset + 5 << " " << r << " " << g << " " << b << " " << a << std::endl; // Inferior

                    currentVoxel++; // Passa para o offset do próximo cubo
                }
            }
        }
    }

    // 6. Fecha o arquivo
    fout.close();
    std::cout << "Arquivo " << filename << " salvo com sucesso!" << std::endl;
}


// Define a cor atual de desenho
void Sculptor::setColor(float r, float g, float b, float a) {
    this->r = r;
    this->g = g;
    this->b = b;
    this->a = a;
}

// Ativa o voxel na posição (x,y,z) e atribui ao mesmo a cor atual de desenho
void Sculptor::putVoxel(int x, int y, int z) {
    // Verificação de segurança: garante que não vamos tentar desenhar fora da matriz!
    if (x >= 0 && x < nx && y >= 0 && y < ny && z >= 0 && z < nz) {
        v[x][y][z].show = true;
        v[x][y][z].r = r;
        v[x][y][z].g = g;
        v[x][y][z].b = b;
        v[x][y][z].a = a;
    }
}

// Desativa o voxel na posição (x,y,z) (fazendo show = false)
void Sculptor::cutVoxel(int x, int y, int z) {
    // A mesma verificação de segurança para evitar acessar memória inválida
    if (x >= 0 && x < nx && y >= 0 && y < ny && z >= 0 && z < nz) {
        v[x][y][z].show = false; 
        
        // Dica: Não precisamos apagar ou resetar as cores (r, g, b, a). 
        // Como 'show' agora é falso, o nosso método writeOFF vai simplesmente 
        // pular esse bloco e ele não existirá no arquivo 3D!
    }
}

// Ativa todos os voxels no intervalo especificado e atribui a cor atual
void Sculptor::putBox(int x0, int x1, int y0, int y1, int z0, int z1) {
    for (int x = x0; x <= x1; x++) {
        for (int y = y0; y <= y1; y++) {
            for (int z = z0; z <= z1; z++) {
                putVoxel(x, y, z); 
            }
        }
    }
}

// Desativa todos os voxels no intervalo especificado
void Sculptor::cutBox(int x0, int x1, int y0, int y1, int z0, int z1) {
    for (int x = x0; x <= x1; x++) {
        for (int y = y0; y <= y1; y++) {
            for (int z = z0; z <= z1; z++) {
                cutVoxel(x, y, z); // Reaproveitamos a borracha já pronta!
            }
        }
    }
}

// Ativa todos os voxels que satisfazem à equação da esfera
void Sculptor::putSphere(int xcenter, int ycenter, int zcenter, int radius) {
    // Calculamos o raio ao quadrado uma única vez para otimizar o código
    double r2 = radius * radius;
    
    // Delimitamos um "cubo imaginário" ao redor do centro da esfera
    // para não precisarmos varrer a matriz inteira à toa.
    for (int x = xcenter - radius; x <= xcenter + radius; x++) {
        for (int y = ycenter - radius; y <= ycenter + radius; y++) {
            for (int z = zcenter - radius; z <= zcenter + radius; z++) {
                
                // Equação da esfera para o ponto atual
                double dist = ((x - xcenter) * (x - xcenter)) + 
                              ((y - ycenter) * (y - ycenter)) + 
                              ((z - zcenter) * (z - zcenter));
                
                // Se a distância ao quadrado for menor ou igual ao raio ao quadrado,
                // o ponto pertence à esfera!
                if (dist <= r2) {
                    putVoxel(x, y, z);
                }
            }
        }
    }
}

// Desativa todos os voxels que satisfazem à equação da esfera
void Sculptor::cutSphere(int xcenter, int ycenter, int zcenter, int radius) {
    double r2 = radius * radius;
    
    for (int x = xcenter - radius; x <= xcenter + radius; x++) {
        for (int y = ycenter - radius; y <= ycenter + radius; y++) {
            for (int z = zcenter - radius; z <= zcenter + radius; z++) {
                
                double dist = ((x - xcenter) * (x - xcenter)) + 
                              ((y - ycenter) * (y - ycenter)) + 
                              ((z - zcenter) * (z - zcenter));
                
                if (dist <= r2) {
                    cutVoxel(x, y, z);
                }
            }
        }
    }
}

// Ativa os voxels que satisfazem a equação da elipsoide
void Sculptor::putEllipsoid(int xcenter, int ycenter, int zcenter, int rx, int ry, int rz) {
    double dist;
    for (int x = xcenter - rx; x <= xcenter + rx; x++) {
        for (int y = ycenter - ry; y <= ycenter + ry; y++) {
            for (int z = zcenter - rz; z <= zcenter + rz; z++) {
                // Proteção contra divisão por zero caso algum raio seja 0
                if (rx != 0 && ry != 0 && rz != 0) {
                    dist = (pow(x - xcenter, 2) / pow(rx, 2)) + 
                           (pow(y - ycenter, 2) / pow(ry, 2)) + 
                           (pow(z - zcenter, 2) / pow(rz, 2));
                    
                    if (dist <= 1.0) {
                        putVoxel(x, y, z);
                    }
                }
            }
        }
    }
}

// Desativa os voxels que satisfazem a equação da elipsoide
void Sculptor::cutEllipsoid(int xcenter, int ycenter, int zcenter, int rx, int ry, int rz) {
    double dist;
    for (int x = xcenter - rx; x <= xcenter + rx; x++) {
        for (int y = ycenter - ry; y <= ycenter + ry; y++) {
            for (int z = zcenter - rz; z <= zcenter + rz; z++) {
                if (rx != 0 && ry != 0 && rz != 0) {
                    dist = (pow(x - xcenter, 2) / pow(rx, 2)) + 
                           (pow(y - ycenter, 2) / pow(ry, 2)) + 
                           (pow(z - zcenter, 2) / pow(rz, 2));
                    
                    if (dist <= 1.0) {
                        cutVoxel(x, y, z);
                    }
                }
            }
        }
    }
}