#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <chrono>
#include <iomanip>

using namespace std;

vector<vector<int>> Divide(const vector<vector<int>>& A, const vector<vector<int>>& B) {
    int n = A.size();
    vector<vector<int>> C(n, vector<int>(n, 0));

    if (n == 1) {
        C[0][0] = A[0][0] * B[0][0];
    } else {
        int mitad = n / 2;
        vector<vector<int>> A11(mitad, vector<int>(mitad)), A12(mitad, vector<int>(mitad)),
                            A21(mitad, vector<int>(mitad)), A22(mitad, vector<int>(mitad));
        vector<vector<int>> B11(mitad, vector<int>(mitad)), B12(mitad, vector<int>(mitad)),
                            B21(mitad, vector<int>(mitad)), B22(mitad, vector<int>(mitad));

        for (int i = 0; i < mitad; i++) {
            for (int j = 0; j < mitad; j++) {
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

        vector<vector<int>> C11 = Divide(A11, B11);
        vector<vector<int>> C12 = Divide(A11, B12);
        vector<vector<int>> C21 = Divide(A21, B11);
        vector<vector<int>> C22 = Divide(A21, B12);

        vector<vector<int>> temp1 = Divide(A12, B21);
        vector<vector<int>> temp2 = Divide(A12, B22);
        vector<vector<int>> temp3 = Divide(A22, B21);
        vector<vector<int>> temp4 = Divide(A22, B22);

        for (int i = 0; i < mitad; i++) {
            for (int j = 0; j < mitad; j++) {
                C[i][j] = C11[i][j] + temp1[i][j];
                C[i][j + mitad] = C12[i][j] + temp2[i][j];
                C[i + mitad][j] = C21[i][j] + temp3[i][j];
                C[i + mitad][j + mitad] = C22[i][j] + temp4[i][j];
            }
        }
    }

    return C;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " <n>" << endl;
        return 1;
    }

    int n = std::atoi(argv[1]);
    if (n <= 0 || (n & (n - 1)) != 0) {
        std::cerr << "Ingrese un número que sea potencia de 2" << std::endl;
        return 1;
    }

    srand(time(nullptr));
    vector<vector<int>> matrizA(n, vector<int>(n)), matrizB(n, vector<int>(n));

    // Randomly fill A and B
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            matrizA[i][j] = rand() % 10;
            matrizB[i][j] = rand() % 10;
        }
    }

    cout << "Matriz A:" << endl;
    for (const auto& row : matrizA) {
        for (int num : row) {
            cout << num << " ";
        }
        cout << endl;
    }

    cout << "Matriz B:" << endl;
    for (const auto& row : matrizB) {
        for (int num : row) {
            cout << num << " ";
        }
        cout << endl;
    }

    auto start = chrono::high_resolution_clock::now();

    vector<vector<int>> matrizC = Divide(matrizA, matrizB);

    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::nanoseconds>(end - start);
    double milliseconds = duration.count() / 1000000.0;


    std::cout << "Matriz multiplicada AxB : " << n << "x" << n << " Matriz C:" << std::endl;
    for (const auto& row : matrizC) {
        for (int num : row) {
            std::cout << num << " ";
        }
        std::cout << std::endl;
    }


    std::cout << std::fixed << std::setprecision(3) << "El metodo divide y conquista tomó " << milliseconds << " milisegundos." << std::endl;

    return 0;
}
