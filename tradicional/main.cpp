#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>

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

    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){

        int suma = 0;
            for (int k = 0; k < n; k++){
                suma += matrizA[i][k] * matrizB[k][j];
            }
        matrizC[i][j] = suma;

        }
    }



    std::cout << "Matriz multiplicada AxB : " << n << "x" << n << " Matriz C:" << std::endl;
    for (const auto& row : matrizC) {
        for (int num : row) {
            std::cout << num << " ";
        }
        std::cout << std::endl;
    }


    return 0;
}
