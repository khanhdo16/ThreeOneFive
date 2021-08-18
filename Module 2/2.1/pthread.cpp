#include <iostream>
#include <fstream>
#include <cstdlib>
#include <time.h>
#include <chrono>
#include <string>
#include <pthread.h>

using namespace std::chrono;
using namespace std;

#define N 1250
#define THREADS 8

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

void *matrixMultiply(void *threadid) {
    long id;

    id = (long)threadid;
    int i = id * N / THREADS;
    int size = (id + 1) * N / THREADS;

    for (i; i < size; i++) {
        for (int j = 0; j < N; j++) {
            matrixC[i][j] = 0;
            for (int k = 0; k < N; k++)
                matrixC[i][j] += matrixA[i][k] * matrixB[k][j];
        }
    }

    return NULL;
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

    pthread_t threads[THREADS];

    for(int i = 0; i < THREADS; i++) {
        int err = pthread_create(&threads[i], NULL, matrixMultiply, (void *)i);
      
        if (err) {
            cout << "Error:unable to create thread," << err << endl;
        }
    }

    for(int i = 0; i < THREADS; i++) {
        int err = pthread_join(threads[i], NULL);
        if (err) {
            cout << "Error:unable to join," << err << endl;
        }
    }

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);

    resultTest();

    cout << "Time taken by function: "
         << duration.count() << " microseconds" << endl;

    return 0;
}