#include <mpi.h>
#include <stdio.h>
#include <time.h>

void print_time(double time) {
    printf("Time taken: %f seconds\n", time);
}

int main(int argc, char** argv) {
    int rank, size, i, sum = 0;
    int array[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int local_sum = 0;
    int* local_array;
    double start, end;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Split the array into equal parts for each process
    int local_size = 10 / size;
    local_array = (int*)malloc(local_size * sizeof(int));
    MPI_Scatter(array, local_size, MPI_INT, local_array, local_size, MPI_INT, 0, MPI_COMM_WORLD);

    // Compute the sum of local array on each process
    start = MPI_Wtime();
    for (i = 0; i < local_size; i++) {
        local_sum += local_array[i];
    }
    end = MPI_Wtime();

    // Reduce the sum of each process to get the total sum
    MPI_Reduce(&local_sum, &sum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    // Print the total sum from the root process
    if (rank == 0) {
        printf("The total sum is: %d\n", sum);
        print_time(end-start);
    }

    MPI_Finalize();
    return 0;
}
