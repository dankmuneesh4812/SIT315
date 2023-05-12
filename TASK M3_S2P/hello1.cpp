#include <mpi.h>
#include <stdio.h>
#include <string.h>

#define MSG_SIZE 13 // "Hello World!" plus null terminator

int main(int argc, char** argv) {
    int num_procs, rank;
    MPI_Status status;
    char message[MSG_SIZE];

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &num_procs);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (rank == 0) { // Master process
        for (int i = 1; i < num_procs; i++) {
            strcpy(message, "Hello World!");
            MPI_Send(message, MSG_SIZE, MPI_CHAR, i, 0, MPI_COMM_WORLD);
        }
    } else { // Worker processes
        MPI_Recv(message, MSG_SIZE, MPI_CHAR, 0, 0, MPI_COMM_WORLD, &status);
        printf("%s\n", message);
    }

    MPI_Finalize();
    return 0;
}
