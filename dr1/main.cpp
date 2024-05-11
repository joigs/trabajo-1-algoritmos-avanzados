#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>


void celda(std::vector<std::vector<int>>& matrizC, const std::vector<std::vector<int>>& matrizA, const std::vector<std::vector<int>>& matrizB, int columna, int fila) {
    matrizC[fila][columna] = matrizA[fila][columna] * matrizB[fila][columna] + matrizA[fila][columna+1] * matrizB[fila+1][columna];
    matrizC[fila][columna+1] = matrizA[fila][columna] * matrizB[fila][columna+1] + matrizA[fila][columna+1] * matrizB[fila+1][columna+1];
    matrizC[fila+1][columna] = matrizA[fila+1][columna] * matrizB[fila][columna] + matrizA[fila+1][columna+1] * matrizB[fila+1][columna];
    matrizC[fila+1][columna+1] = matrizA[fila+1][columna] * matrizB[fila][columna+1] + matrizA[fila+1][columna+1] * matrizB[fila+1][columna+1];
}

void division (int n, std::vector<std::vector<int>>& matrizA, std::vector<std::vector<int>>& matrizB, std::vector<std::vector<int>>& matrizC, int columna, int fila) {
    if (n == 2) {
        celda(matrizC, matrizA, matrizB, columna, fila);
    } else {
        int mitad = n / 2;
        division(mitad, matrizA, matrizB, matrizC, columna, fila);
        division(mitad, matrizA, matrizB, matrizC, columna + mitad, fila);
        division(mitad, matrizA, matrizB, matrizC, columna, fila + mitad);
        division(mitad, matrizA, matrizB, matrizC, columna + mitad, fila + mitad);
    }
}



int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <n>" << std::endl;
        return 1;
    }

    int n = std::atoi(argv[1]);
    if (n <= 0) {
        std::cerr << "Ingrese un número positivo" << std::endl;
        return 1;
    }

    srand(time(nullptr));

    std::vector<std::vector<int>> matrizA(n, std::vector<int>(n));
    std::vector<std::vector<int>> matrizB(n, std::vector<int>(n));
    std::vector<std::vector<int>> matrizC(n, std::vector<int>(n));


    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            matrizA[i][j] =  rand() % 100;
            matrizB[i][j] =  rand() % 100;
        }
    }

    std::cout << "Matriz generada: " << n << "x" << n << " Matriz A :" << std::endl;
    for (const auto& row : matrizA) {
        for (int num : row) {
            std::cout << num << " ";
        }
        std::cout << std::endl;
    }

    std::cout << "Matriz generada: " << n << "x" << n << " Matriz B :" << std::endl;
    for (const auto& row : matrizB) {
        for (int num : row) {
            std::cout << num << " ";
        }
        std::cout << std::endl;
    }

    int columna = 0;
    int fila = 0;
    division(n, matrizA, matrizB, matrizC, columna, fila);



    std::cout << "Matriz multiplicada AxB : " << n << "x" << n << " Matriz C:" << std::endl;
    for (const auto& row : matrizC) {
        for (int num : row) {
            std::cout << num << " ";
        }
        std::cout << std::endl;
    }


    return 0;
}


