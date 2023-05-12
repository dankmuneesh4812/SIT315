#include <iostream>
#include <fstream>
#include <random>
#include <chrono>
#include <omp.h>

using namespace std;
using namespace std::chrono;

const int N = 100; // size of matrices

int A[N][N], B[N][N], C[N][N];

int main()
{
    // initialize matrices A and B with random values
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(1, 10);

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            A[i][j] = dis(gen);
            B[i][j] = dis(gen);
        }
    }

    // calculate C = A x B
    auto start_time = high_resolution_clock::now(); // start timing

    #pragma omp parallel for
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            int sum = 0;
            for (int k = 0; k < N; k++)
            {
                sum += A[i][k] * B[k][j];
            }
            C[i][j] = sum;
        }
    }

    auto end_time = high_resolution_clock::now(); // end timing

    // write output to file
    ofstream fout("output.txt");
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            fout << C[i][j] << " ";
        }
        fout << endl;
    }

    // print execution time
    auto duration = duration_cast<milliseconds>(end_time - start_time);
    cout << "Execution time: " << duration.count() << " milliseconds." << endl;

    return 0;
}
