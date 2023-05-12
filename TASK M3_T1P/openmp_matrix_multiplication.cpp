#include <iostream>
#include <fstream>
#include <random>
#include <chrono>
#include <mpi.h>
#include <omp.h>

using namespace std;
using namespace std::chrono;

const int N = 1000; // MATRIX SIZE

int main(int argc, char** argv)
{
    // MPI Initialization
    int rank, size;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // VARIABLE A & B INITIALISED
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(1, 10);

    int chunk_size = N / size;
    int start_row = rank * chunk_size;
    int end_row = (rank == size-1) ? N : start_row + chunk_size;

    int A[N][N], B[N][N], C[N][N];

    // Initialize A and B only in master process
    if (rank == 0) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                A[i][j] = dis(gen);
                B[i][j] = dis(gen);
            }
        }
    }

    // Broadcast matrix B to all processes
    MPI_Bcast(B, N*N, MPI_INT, 0, MPI_COMM_WORLD);

    // Scatter matrix A to all processes
    MPI_Scatter(A, chunk_size*N, MPI_INT, A[start_row], chunk_size*N, MPI_INT, 0, MPI_COMM_WORLD);

    // CALCULATION OF C
    auto start_time = high_resolution_clock::now(); // START TIME CALCULATION
    #pragma omp parallel for
    for (int i = start_row; i < end_row; i++)
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

    // Gather results from all processes to master process
    MPI_Gather(C[start_row], chunk_size*N, MPI_INT, C, chunk_size*N, MPI_INT, 0, MPI_COMM_WORLD);

    auto end_time = high_resolution_clock::now(); // END TIME CALCULATION

    if (rank == 0) {
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
    }

    // MPI Finalization
    MPI_Finalize();

    return 0;
}
