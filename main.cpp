#include "sculptor.h"
#include <iostream>


int main() {
    // 1. O seu espaço 3D gigante (80x80x80)
    Sculptor cena(80, 80, 80);

    // 2. O Chão de Grama (Cor: Verde Claro)
    // Desenhamos a grama primeiro para não sobrepor o tronco
    cena.setColor(0.4, 0.8, 0.1, 1.0);
    cena.putBox(0, 79, 0, 0, 0, 79);

    // 3. O Lago Orgânico Gigante e Diagonal (Cor: Azul Água)
    cena.setColor(0.1, 0.5, 0.9, 1.0);
    // Corpo principal do lago (bem largo no eixo X e Z)
    cena.putEllipsoid(52, 1, 60, 18, 1, 12); 
    // Curva esticando para o canto inferior esquerdo
    cena.putEllipsoid(66, 1, 68, 8, 1, 10);  
    // Curva esticando na diagonal em direção ao centro (para a 1 bloco da árvore!)
    cena.putEllipsoid(40, 1, 52, 14, 1, 8);

    // 3. O Tronco da Árvore Centralizado (Cor: Marrom)
    cena.setColor(0.4, 0.2, 0.0, 1.0);
    // Para centralizar no 40, fazemos o tronco ir de 37 a 43 no eixo X e no eixo Z.
    // Começa no Y=1 (para ficar em cima da grama) e vai até Y=20.
    cena.putBox(24, 30, 1, 20, 24, 30);

    // 4. A Copa da Árvore Centralizada (Cor: Verde)
    cena.setColor(0.0, 0.6, 0.2, 1.0);
    // Colocamos o centro exato da elipsoide no X=40 e Z=40.
    // O Y=25 mantém a copa encaixada no topo do tronco.
    cena.putEllipsoid(27, 25, 27, 16, 12, 16); // Aumentei um pouco os raios para ficar mais frondosa!

    // 5. O Sol Gigante (Cor: Amarelo)
    cena.setColor(0.99, 0.99, 0.0, 1.0);
    // Movi o sol um bocadinho mais para cima (Y=60) e mais para o fundo (Z=10) 
    // para aproveitar a altura da sua nova matriz de 80 blocos!
    cena.putSphere(65, 60, 10, 12);

    cena.setColor(0.99, 0.99, 0.99, 1.0); 
    for(int i = 0; i < 6; i++) {
        int x = rand() % 80;        
        int z = rand() % 80;        
        int y = 45 + (rand() % 30); 
        cena.putEllipsoid(x, y, z, 7, 2, 8); 
    }

    // 3. O Fundo do Céu estilo Diorama (Cor: Azul Celeste)
    // Usamos 0.99 no azul para garantir a leitura correta e alfa 1.0 (sólido)
    cena.setColor(0.5, 0.8, 0.99, 1.0);
    
    // Parede do Fundo (Z = 0) - Fica atrás do sol e da árvore
    cena.putBox(0, 79, 1, 79, 0, 0);
    
    // Parede da Esquerda (X = 0) - Cria um canto que dá noção de profundidade
    cena.putBox(0, 0, 1, 79, 0, 79);
    // 6. Gravando a escultura final no formato OFF
    cena.writeOFF("arvore.off");

    std::cout << "Cena da arvore centralizada gerada com sucesso!" << std::endl;

    return 0;
}