#include "sculptor.h"
#include <iostream>


int main() {
    
    Sculptor cena(80, 80, 80);

    // 2. O Chão de Grama (Cor: Verde Claro)
    cena.setColor(0.4, 0.8, 0.1, 1.0);
    cena.putBox(0, 79, 0, 0, 0, 79);

    // 3. O Lago (Cor: Azul Água)
    cena.setColor(0.1, 0.5, 0.9, 1.0);
    cena.putEllipsoid(52, 1, 60, 18, 1, 12); 
    cena.putEllipsoid(66, 1, 68, 8, 1, 10);  
    cena.putEllipsoid(40, 1, 52, 14, 1, 8);

    // 3. O Tronco da Árvore  (Cor: Marrom)
    cena.setColor(0.4, 0.2, 0.0, 1.0);
    // Para centralizar no 40, fazemos o tronco ir de 37 a 43 no eixo X e no eixo Z.
    // Começa no Y=1 (para ficar em cima da grama) e vai até Y=20.
    cena.putBox(24, 30, 1, 20, 24, 30);

    // 4. A Copa da Árvore Centralizada (Cor: Verde)
    cena.setColor(0.0, 0.6, 0.2, 1.0);
    // Colocamos o centro exato da elipsoide no X=40 e Z=40.
    // O Y=25 mantém a copa encaixada no topo do tronco.
    cena.putEllipsoid(27, 25, 27, 16, 12, 16);

    // 5. O Sol Gigante (Cor: Amarelo)
    cena.setColor(0.99, 0.99, 0.0, 1.0);
    // Movi o sol um bocadinho mais para cima (Y=60) e mais para o fundo (Z=10) 
    // para aproveitar a altura da sua nova matriz de 80 blocos!
    cena.putSphere(65, 60, 10, 12);

    // Nuvens 
    cena.setColor(0.99, 0.99, 0.99, 1.0); 
    cena.putEllipsoid(20, 50, 20, 7, 2, 8);
    cena.putEllipsoid(60, 65, 30, 7, 2, 8);
    cena.putEllipsoid(15, 55, 60, 7, 2, 8);
    cena.putEllipsoid(45, 48, 70, 7, 2, 8);
    cena.putEllipsoid(70, 60, 70, 7, 2, 8);
    cena.putEllipsoid(30, 70, 10, 7, 2, 8);

    // 3. Céu (Cor: Azul Celeste)
    cena.setColor(0.5, 0.8, 0.99, 1.0);
    
    // Parede do Fundo (Z = 0) - Fica atrás do sol e da árvore
    cena.putBox(0, 79, 1, 79, 0, 0);
    
    // Parede da Esquerda (X = 0) 
    cena.putBox(0, 0, 1, 79, 0, 79);
    // 6. Gravando a escultura final no formato OFF
    cena.writeOFF("arvore.off");

    std::cout << "Cena da arvore gerada com sucesso!" << std::endl;

    return 0;
}
