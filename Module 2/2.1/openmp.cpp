#include <iostream>
#include <fstream>
#include <cstdlib>
#include <time.h>
#include <chrono>
#include <string> 
#include <omp.h>

using namespace std::chrono;
using namespace std;

#define N 1250

int matrixA[N][N];
int matrixB[N][N];
int matrixC[N][N];

int init = 0;


void matrixInit(int matrix[N][N])
{
    srand(init++);

    for(int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            matrix[i][j] = rand() % 100;
        }
    }
}

string matrixPrint(int matrix[N][N])
{   
    string print;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++)
            print += to_string(matrix[i][j]) + " ";
        print += "\n";
    }

    return print;
}

void resultTest() {
    ofstream output;
    output.open ("output.txt");

    output << "Matrix A: \n" << matrixPrint(matrixA) << "\n";
    output << "Matrix B: \n" << matrixPrint(matrixB) << "\n";
    output << "[Result] Matrix C: \n" << matrixPrint(matrixC);

    output.close();
}

int main()
{
    cout << "Matrix size: " << N << "\n";
    matrixInit(matrixA);
    matrixInit(matrixB);

    auto start = high_resolution_clock::now();
    
    int i, j, k;

    #pragma omp parallel for private(k)
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            for (k = 0; k < N; k++) {
                matrixC[i][j] = matrixA[i][k] * matrixB[k][j];
            }
        }
    }

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);

    resultTest();

    cout << "Time taken by function: "
         << duration.count() << " microseconds" << endl;

    return 0;
}