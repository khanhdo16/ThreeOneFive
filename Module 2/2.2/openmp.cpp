#include <iostream>
#include <fstream>
#include <cstdlib>
#include <time.h>
#include <chrono>
#include <string>
#include <stdio.h>
#include <omp.h>

using namespace std::chrono;
using namespace std;

#define N 1000000

int unsorted[N];
int result[N];

 
void swapElm(int* a, int* b)
{
    int t = *a;
    *a = *b;
    *b = t;
}
 
int findMid (int arr[], int low, int high)
{
    int pivot = arr[high];
    int i = (low - 1);
    int j;

    #pragma omp parallel for private(j)
    for (j = low; j <= high - 1; j++)
    {
        if (arr[j] <= pivot)
        {
            i++;
            swapElm(&arr[i], &arr[j]);
        }
    }
    swapElm(&arr[i + 1], &arr[high]);
    return (i + 1);
}
 
void quickSort(int arr[], int low, int high)
{
    if (low < high)
    {
        int pi = findMid(arr, low, high);
 
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

void initArray(int unsorted[N], int result[N])
{
    srand(time(NULL));

    for(int i = 0; i < N; i++)
    {
        int temp = rand() % 100;
        unsorted[i] = temp;
        result[i] = temp;
    }
}

string arrayPrint(int array[N])
{   
    string print = "";
    for (int i = 0; i < N; i++) {
        print += to_string(array[i]) + " ";
        if(i > 0 && i % 100 == 0) {
            print += "\n";
        }
    }

    return print;
}

void resultTest() {
    ofstream output;
    output.open ("output.txt", ios::app);

    output << "Array: \n" << arrayPrint(unsorted) << "\n\n";
    output << "[Result] Array: \n" << arrayPrint(result) << "\n\n";

    output.close();
}

int main()
{
    cout << "Array size: " << N << "\n";
    initArray(unsorted, result);

    auto start = high_resolution_clock::now();

    quickSort(unsorted, 0, N - 1);

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);

    resultTest();

    cout << "Time taken by function: "
         << duration.count() << " microseconds" << endl;

    return 0;
}