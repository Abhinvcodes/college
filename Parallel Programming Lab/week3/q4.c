#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv)
{
  MPI_Init(&argc, &argv);

  int rank, size;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  int L = 0; // string length
  char *S1 = NULL, *S2 = NULL;

  if (rank == 0)
  {
    char a[1024], b[1024];
    printf("Enter S1: ");
    fflush(stdout);
    scanf("%1023s", a);
    printf("Enter S2: ");
    fflush(stdout);
    scanf("%1023s", b);

    L = (int)strlen(a);
    if ((int)strlen(b) != L)
    {
      printf("Error: lengths differ\n");
      MPI_Abort(MPI_COMM_WORLD, 1);
    }
    if (L % size != 0)
    {
      printf("Error: length not divisible by N\n");
      MPI_Abort(MPI_COMM_WORLD, 1);
    }

    S1 = malloc(L + 1);
    S2 = malloc(L + 1);
    strcpy(S1, a);
    strcpy(S2, b);
  }

  MPI_Bcast(&L, 1, MPI_INT, 0, MPI_COMM_WORLD);

  int chunk = L / size;
  char *local1 = malloc(chunk);
  char *local2 = malloc(chunk);

  // Scatter chunks of both strings
  MPI_Scatter(S1, chunk, MPI_CHAR, local1, chunk, MPI_CHAR, 0, MPI_COMM_WORLD);
  MPI_Scatter(S2, chunk, MPI_CHAR, local2, chunk, MPI_CHAR, 0, MPI_COMM_WORLD);

  // Build local interleaved output (size = 2*chunk)
  char *localOut = malloc(2 * chunk);
  for (int i = 0; i < chunk; i++)
  {
    localOut[2 * i] = local1[i];
    localOut[2 * i + 1] = local2[i];
  }

  // Gather localOut blocks to root
  char *result = NULL;
  if (rank == 0)
    result = malloc(2 * L + 1);

  MPI_Gather(localOut, 2 * chunk, MPI_CHAR,
             result, 2 * chunk, MPI_CHAR, 0, MPI_COMM_WORLD);

  if (rank == 0)
  {
    result[2 * L] = '\0';
    printf("Resultant String: %s\n", result);
  }

  free(local1);
  free(local2);
  free(localOut);
  if (rank == 0)
  {
    free(S1);
    free(S2);
    free(result);
  }

  MPI_Finalize();
  return 0;
}
