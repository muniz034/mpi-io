// mpicc foo.c -o foo.out
// mpirun --oversubscribe --np 4 ./foo.out

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "mpi.h"

int main(int argc, char *argv[]) {
	int size, rank;

	MPI_File fh;
	MPI_Status s;
	MPI_Request r;
	MPI_Info info_used;

	MPI_Init(&argc, &argv);

	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	int unableToOpen = MPI_File_open(MPI_COMM_WORLD, "helloworld.txt", MPI_MODE_CREATE|MPI_MODE_WRONLY, MPI_INFO_NULL, &fh);
	
	if(unableToOpen) printf("[%d] Cannot open the file!\n", rank);

	char data[100];
	sprintf(data, "Hello World from %d\n", rank);

	int offset = (rank) * sizeof(char) * strlen(data);

	MPI_File_write_at(fh, offset, &data, strlen(data), MPI_CHAR, &s);

	MPI_File_close(&fh);

	MPI_Finalize();

	return 0;
}
