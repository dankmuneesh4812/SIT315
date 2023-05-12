#include <iostream>
#include <fstream>
#include <random>
#include <chrono>

using namespace std;
using namespace std::chrono;

const int N = 500; // MATRIX SIZE

int main()
{
    // VARIABLE A & B INITIALISED
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(1, 10);

    int A[N][N], B[N][N], C[N][N];

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            A[i][j] = dis(gen);
            B[i][j] = dis(gen);
        }
    }

    // CALCULATION OF C
    auto start_time = high_resolution_clock::now(); 
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
    auto end_time = high_resolution_clock::now(); // END TIME CALCULATION

    // OUTPUT FILE GENERATED
    ofstream fout("output.txt");
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            fout << C[i][j] << " ";
        }
        fout << endl;
    }

    // CALCULATION OF EXECUTION TIME
    auto duration = duration_cast<milliseconds>(end_time - start_time);
    cout << "Execution time: " << duration.count() << " milliseconds." << endl;
    return 0;
}