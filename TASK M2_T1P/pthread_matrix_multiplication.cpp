#include <iostream>
#include <fstream>
#include <random>
#include <chrono>
#include <pthread.h>

using namespace std;
using namespace std::chrono;

const int N = 100; // MATRIX SIZE
const int M = 4; // NUMBER OF THREADS

int A[N][N], B[N][N], C[N][N];

struct thread_data {
    int id;
};

void* multiply(void* arg) {
    thread_data* data = (thread_data*) arg;
    int row_start = data->id * N / M;
    int row_end = (data->id + 1) * N / M;

    for (int i = row_start; i < row_end; i++) {
        for (int j = 0; j < N; j++) {
            int sum = 0;
            for (int k = 0; k < N; k++) {
                sum += A[i][k] * B[k][j];
            }
            C[i][j] = sum;
        }
    }
    pthread_exit(NULL);
}

int main()
{
    // VARIABLE A & B INITIALISED
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

    // CALCULATION OF C
    pthread_t threads[M];
    thread_data td[M];
    auto start_time = high_resolution_clock::now();

    for (int i = 0; i < M; i++) {
        td[i].id = i;
        pthread_create(&threads[i], NULL, multiply, (void*) &td[i]);
    }

    for (int i = 0; i < M; i++) {
        pthread_join(threads[i], NULL);
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
