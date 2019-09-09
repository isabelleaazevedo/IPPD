#include <stdio.h>
#include <mpi.h>

const int PING_PONG_LIMIT = 5;

int main (void){
  MPI_Init(NULL, NULL);

  int processes;
  int rank;
  MPI_Comm_size(MPI_COMM_WORLD, &processes);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  int ping_pong_count = 0;
  int partner_rank = (rank + 1) % 2;

  while(ping_pong_count < PING_PONG_LIMIT){
    if(rank == ping_pong_count % 2){
      ping_pong_count++;
      MPI_Send(&ping_pong_count, 1, MPI_INT, partner_rank, 0, MPI_COMM_WORLD);
      printf("%d sent ping_pong_count %d to %d\n", rank, ping_pong_count, partner_rank);
    } else{
      MPI_Recv(&ping_pong_count, 1, MPI_INT, partner_rank, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
      printf("%d received ping_pong_count %d from %d\n", rank, ping_pong_count, partner_rank);
    }
  }

  MPI_Finalize();
}
