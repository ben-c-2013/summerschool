#include <cstdio>
#include <vector>
#include <mpi.h>

int main(int argc, char *argv[])
{
    int rank, ntasks, nrecv;
    constexpr int arraysize = 100000;
    constexpr int msgsize = 10000;
    std::vector<int> message(arraysize);
    std::vector<int> receiveBuffer(arraysize);
    MPI_Status status;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &ntasks);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    // Initialize message and receive buffer
    for (int i = 0; i < arraysize; i++) {
        message[i] = rank;
        receiveBuffer[i] = -1;
    }

    // TODO: Implement sending and receiving as defined in the assignment
    // Send msgsize elements from the array "message", and receive into
    // "receiveBuffer"
    if (rank == 0) {
        MPI_Send(message.data(), msgsize, MPI_INT, 1, 0,  MPI_COMM_WORLD);
        //printf("Rank %i received %i elements, first %i\n", rank, nrecv, receiveBuffer[0]);
    } else if (rank == 1) {
        MPI_Recv(receiveBuffer.data(), msgsize, MPI_INT, 0, 0,  MPI_COMM_WORLD, &status);
        MPI_Get_count(&status, MPI_INT, &nrecv);
        printf("Rank %i received %i elements, first %i\n", rank, nrecv, receiveBuffer[0]);
    }

    if (rank == 1) {
        MPI_Send(message.data(), msgsize, MPI_INT, 0, 0,  MPI_COMM_WORLD);
        //printf("Rank %i received %i elements, first %i\n", rank, nrecv, receiveBuffer[0]);
    } else if (rank == 0) {
        MPI_Recv(receiveBuffer.data(), msgsize, MPI_INT, 1, 0,  MPI_COMM_WORLD, &status);
        MPI_Get_count(&status, MPI_INT, &nrecv);
        printf("Rank %i received %i elements, first %i\n", rank, nrecv, receiveBuffer[0]);
    }



    MPI_Finalize();
    return 0;
}
