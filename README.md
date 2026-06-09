# Projeto Escultor 3D - Parte 1

Este é um projeto desenvolvido em **C++** que funciona como uma ferramenta para a criação de esculturas tridimensionais baseadas em blocos (semelhante à lógica do Minecraft). O programa manipula uma matriz tridimensional digital onde cada bloco é chamado de **Voxel** (volume element).

A ferramenta permite desenhar e apagar estruturas geométricas na matriz e, ao final, exportar o resultado para um arquivo no formato **.OFF**, que pode ser aberto em softwares de visualização 3D.

Nesta primeira etapa, o projeto contém exemplos de modelagem geométrica processual, incluindo a criação de uma **Árvore com Paisagem** e uma **Espada**.

## 🛠️ Pré-requisitos

Para compilar e executar este projeto, você precisará ter instalado em sua máquina:
* Um compilador C++ (como o **GCC/MinGW** para Windows ou **Clang** para macOS/Linux).
* Um visualizador de arquivos 3D (recomendamos o software [MeshLab](https://www.meshlab.net/) ou o visualizador online [3D Viewer](https://3dviewer.net/)).

## ⚙️ Como Compilar o Projeto

1. Faça o clone deste repositório ou baixe os arquivos fonte (`.cpp` e `.h`).
2. Abra o terminal (ou prompt de comando) e navegue até a pasta onde os arquivos estão salvos.
3. Digite o seguinte comando para compilar o código, unindo o arquivo principal e a classe do escultor:

   ```bash
   g++ main.cpp sculptor.cpp -o cena
