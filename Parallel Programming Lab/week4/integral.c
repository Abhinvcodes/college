#include <mpi.h>
#include <stdio.h>

int main(int argc, char **argv)
{
    int rank, size;
    double dx, x, y, area, totalarea;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    dx = 1.0 / size;

    // Midpoint rule
    x = (rank + 0.5) * dx;

    y = 4.0 / (1.0 + x * x);

    area = y * dx;

    MPI_Reduce(&area, &totalarea, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        printf("Approximate value of PI = %.10f\n", totalarea);
    }

    MPI_Finalize();
    return 0;
}

