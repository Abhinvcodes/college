#include <stdio.h>
#include <mpi.h>
#include <stdlib.h>

// Helper function to handle and print MPI errors
void handle_mpi_error(int err_code, const char *func_name) {
    if (err_code != MPI_SUCCESS) {
        char err_string[MPI_MAX_ERROR_STRING];
        int result_len;
        MPI_Error_string(err_code, err_string, &result_len);
        fprintf(stderr, "MPI Error in %s: %s\n", func_name, err_string);
        MPI_Abort(MPI_COMM_WORLD, err_code);
    }
}

int main(int argc, char **argv) {
    int rank, err;

    err = MPI_Init(&argc, &argv);
    if (err != MPI_SUCCESS) {
        fprintf(stderr, "Failed to initialize MPI\n");
        return err;
    }

    // Set error handler so the program doesn't just die on error
    MPI_Comm_set_errhandler(MPI_COMM_WORLD, MPI_ERRORS_RETURN);

    err = MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    handle_mpi_error(err, "MPI_Comm_rank");

    int fact = 1;
    for (int i = 2; i <= rank + 1; i++)
        fact *= rank;

    int factsum = 0;
    err = MPI_Reduce(&fact, &factsum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
    handle_mpi_error(err, "MPI_Reduce");

    if (rank == 0) {
        printf("Sum of all results = %d\n", factsum);
    }

    MPI_Finalize();
    return 0;
}
