#include <mpi.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int is_vowel(char c) {
    c = tolower(c);
    return (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u');
}

int main(int argc, char** argv) {
    int rank, size;
    char full_string[100];
    int n; // string length

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0) {
        printf("Enter a string (length divisible by %d): ", size);
        scanf("%s", full_string);
        n = strlen(full_string);
    }

    // Broadcast string length to calculate chunk size
    MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);
    int chunk_size = n / size;
    char *local_str = (char*)malloc(sizeof(char) * chunk_size);

    // Distribute chunks of the string to all processes
    MPI_Scatter(full_string, chunk_size, MPI_CHAR, local_str, chunk_size, MPI_CHAR, 0, MPI_COMM_WORLD);

    // Count non-vowels in the local chunk
    int local_non_vowels = 0;
    for (int i = 0; i < chunk_size; i++) {
        if (isalpha(local_str[i]) && !is_vowel(local_str[i])) {
            local_non_vowels++;
        }
    }

    // Gather all local counts into an array in the root process
    int *all_counts = NULL;
    if (rank == 0) {
        all_counts = (int*)malloc(sizeof(int) * size);
    }

    MPI_Gather(&local_non_vowels, 1, MPI_INT, all_counts, 1, MPI_INT, 0, MPI_COMM_WORLD);

    // Root process displays results
    if (rank == 0) {
        int total_non_vowels = 0;
        printf("\n--- Results ---\n");
        for (int i = 0; i < size; i++) {
            printf("Process %d found %d non-vowels.\n", i, all_counts[i]);
            total_non_vowels += all_counts[i];
        }
        printf("Total number of non-vowels: %d\n", total_non_vowels);
        free(all_counts);
    }

    free(local_str);
    MPI_Finalize();
    return 0;
}
