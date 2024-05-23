#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <chrono>
#include <iomanip> 

void sumar(std::vector<std::vector<int>>& resultado, const std::vector<std::vector<int>>& A, const std::vector<std::vector<int>>& B, int n) {
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            resultado[i][j] = A[i][j] + B[i][j];
}

void restar(std::vector<std::vector<int>>& resultado, const std::vector<std::vector<int>>& A, const std::vector<std::vector<int>>& B, int n) {
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            resultado[i][j] = A[i][j] - B[i][j];
}

void strassen(std::vector<std::vector<int>>& C, const std::vector<std::vector<int>>& A, const std::vector<std::vector<int>>& B, int n) {
    if (n == 1) {
        C[0][0] = A[0][0] * B[0][0];
    } else {
        int mitad = n / 2;
        std::vector<std::vector<int>> A11(mitad, std::vector<int>(mitad)),
        A12(mitad, std::vector<int>(mitad)), A21(mitad, std::vector<int>(mitad)), A22(mitad, std::vector<int>(mitad));
        std::vector<std::vector<int>> B11(mitad, std::vector<int>(mitad)), B12(mitad, std::vector<int>(mitad)), B21(mitad, std::vector<int>(mitad)), B22(mitad, std::vector<int>(mitad));
        std::vector<std::vector<int>> C11(mitad, std::vector<int>(mitad)), C12(mitad, std::vector<int>(mitad)), C21(mitad, std::vector<int>(mitad)), C22(mitad, std::vector<int>(mitad));
        std::vector<std::vector<int>> M(mitad, std::vector<int>(mitad)), N(mitad, std::vector<int>(mitad)), O(mitad, std::vector<int>(mitad)), P(mitad, std::vector<int>(mitad));
        std::vector<std::vector<int>> Q(mitad, std::vector<int>(mitad)), R(mitad, std::vector<int>(mitad)), S(mitad, std::vector<int>(mitad));
        std::vector<std::vector<int>> temp1(mitad, std::vector<int>(mitad)), temp2(mitad, std::vector<int>(mitad));

        for (int i = 0; i < mitad; ++i) {
            for (int j = 0; j < mitad; ++j) {
                A11[i][j] = A[i][j];
                A12[i][j] = A[i][j + mitad];
                A21[i][j] = A[i + mitad][j];
                A22[i][j] = A[i + mitad][j + mitad];
                B11[i][j] = B[i][j];
                B12[i][j] = B[i][j + mitad];
                B21[i][j] = B[i + mitad][j];
                B22[i][j] = B[i + mitad][j + mitad];
            }
        }

        sumar(temp1, A11, A22, mitad);
        sumar(temp2, B11, B22, mitad);
        strassen(M, temp1, temp2, mitad);
        sumar(temp1, A21, A22, mitad);
        strassen(N, temp1, B11, mitad);
        restar(temp1, B12, B22, mitad);
        strassen(O, A11, temp1, mitad);
        restar(temp1, B21, B11, mitad);
        strassen(P, A22, temp1, mitad);
        sumar(temp1, A11, A12, mitad);
        strassen(Q, temp1, B22, mitad);
        restar(temp1, A21, A11, mitad);
        sumar(temp2, B11, B12, mitad);
        strassen(R, temp1, temp2, mitad);
        restar(temp1, A12, A22, mitad);
        sumar(temp2, B21, B22, mitad);
        strassen(S, temp1, temp2, mitad);

        for (int i = 0; i < mitad; ++i) {
            for (int j = 0; j < mitad; ++j) {
                C11[i][j] = M[i][j] + P[i][j] - Q[i][j] + S[i][j];
                C12[i][j] = O[i][j] + Q[i][j];
                C21[i][j] = N[i][j] + P[i][j];
                C22[i][j] = M[i][j] - N[i][j] + O[i][j] + R[i][j];
            }
        }

        for (int i = 0; i < mitad; ++i) {
            for (int j = 0; j < mitad; ++j) {
                C[i][j] = C11[i][j];
                C[i][j + mitad] = C12[i][j];
                C[i + mitad][j] = C21[i][j];
                C[i + mitad][j + mitad] = C22[i][j];
            }
        }
    }
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <n>" << std::endl;
        return 1;
    }

    int n = std::atoi(argv[1]);
    if (n <= 0 || (n & (n - 1)) != 0) {
        std::cerr << "Ingrese un número que sea potencia de 2" << std::endl;
        return 1;
    }

    srand(time(nullptr));

    std::vector<std::vector<int>> matrizA(n, std::vector<int>(n)), matrizB(n, std::vector<int>(n)), matrizC(n, std::vector<int>(n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            matrizA[i][j] = rand() % 10;
            matrizB[i][j] = rand() % 10;
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

    auto start = std::chrono::high_resolution_clock::now();

    strassen(matrizC, matrizA, matrizB, n);
    
    auto end = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);

    
  

  
    std::cout << "Matriz multiplicada AxB : " << n << "x" << n << " Matriz C:" << std::endl;
    for (const auto& row : matrizC) {
        for (int num : row) {
            std::cout << num << " ";
        }
        std::cout << std::endl;
    }
    
     double milliseconds = duration.count() / 1000000.0;
std::cout << std::fixed << std::setprecision(3) << "El metodo Strassen tomó " << milliseconds << " milisegundos." << std::endl;
    return 0;
}
