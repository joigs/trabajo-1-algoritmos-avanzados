#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <chrono>
#include <iomanip> 

using namespace std;

vector<vector<int>> MatrixMultiply(const vector<vector<int>>& A, const vector<vector<int>>& B) {
    int n = A.size();
    vector<vector<int>> C(n, vector<int>(n, 0));

    if (n == 1) {
        C[0][0] = A[0][0] * B[0][0];
    } else {
        int mid = n / 2;
        vector<vector<int>> A11(mid, vector<int>(mid)), A12(mid, vector<int>(mid)), 
                            A21(mid, vector<int>(mid)), A22(mid, vector<int>(mid));
        vector<vector<int>> B11(mid, vector<int>(mid)), B12(mid, vector<int>(mid)), 
                            B21(mid, vector<int>(mid)), B22(mid, vector<int>(mid));

        // Partitioning A and B into submatrices
        for (int i = 0; i < mid; i++) {
            for (int j = 0; j < mid; j++) {
                A11[i][j] = A[i][j];
                A12[i][j] = A[i][j + mid];
                A21[i][j] = A[i + mid][j];
                A22[i][j] = A[i + mid][j + mid];

                B11[i][j] = B[i][j];
                B12[i][j] = B[i][j + mid];
                B21[i][j] = B[i + mid][j];
                B22[i][j] = B[i + mid][j + mid];
            }
        }

        // Multiply and add submatrices
        vector<vector<int>> C11 = MatrixMultiply(A11, B11);
        vector<vector<int>> C12 = MatrixMultiply(A11, B12);
        vector<vector<int>> C21 = MatrixMultiply(A21, B11);
        vector<vector<int>> C22 = MatrixMultiply(A21, B12);

        // Correct combination logic
        for (int i = 0; i < mid; i++) {
            for (int j = 0; j < mid; j++) {
                C[i][j] = C11[i][j] + MatrixMultiply(A12, B21)[i][j];
                C[i][j + mid] = C12[i][j] + MatrixMultiply(A12, B22)[i][j];
                C[i + mid][j] = C21[i][j] + MatrixMultiply(A22, B21)[i][j];
                C[i + mid][j + mid] = C22[i][j] + MatrixMultiply(A22, B22)[i][j];
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

    int n = atoi(argv[1]);
    if (n <= 0) {
        cerr << "Ingrese un número positivo" << endl;
        return 1;
    }

    srand(time(nullptr));
    vector<vector<int>> A(n, vector<int>(n)), B(n, vector<int>(n));

    // Randomly fill A and B
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            A[i][j] = rand() % 10;
            B[i][j] = rand() % 10;
        }
    }


    
    // Printing Matrix A
    cout << "Matrix A:" << endl;
    for (const auto& row : A) {
        for (int num : row) {
            cout << num << " ";
        }
        cout << endl;
    }

    // Printing Matrix B
    cout << "Matrix B:" << endl;
    for (const auto& row : B) {
        for (int num : row) {
            cout << num << " ";
        }
        cout << endl;
    }
    
    auto start = chrono::high_resolution_clock::now();
    
    // Multiply matrices A and B using divide and conquer
    vector<vector<int>> C = MatrixMultiply(A, B);

    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::nanoseconds>(end - start);
    double milliseconds = duration.count() / 1000000.0; // Conversion from nanoseconds to milliseconds


    
    // Printing Matrix C
    cout << "Resulting Matrix C:" << endl;
    for (const auto& row : C) {
        for (int num : row) {
            cout << num << " ";
        }
        cout << endl;
    }



    
    cout << fixed << setprecision(3) << "Matrix multiplication took " << milliseconds << " milliseconds." << endl;

    return 0;
}
