#include <stdio.h>
#include <mpi.h>
#include <string.h>

int main(int argc, char **argv) {
    int rank, size;
    char word[100];
    char my_char;
    
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int N = size; // The problem states N processes for N length word

    if (rank == 0) {
        printf("Enter a word of length %d: ", N);
        fflush(stdout);
        scanf("%s", word);
    }

    // 1. Distribute one character to each process
    MPI_Scatter(word, 1, MPI_CHAR, &my_char, 1, MPI_CHAR, 0, MPI_COMM_WORLD);

    // 2. Each process creates a local buffer of length N (padding with 0)
    char local_buffer[N];
    memset(local_buffer, 0, N); // Clear buffer

    // Fill the buffer with 'rank + 1' occurrences of the character
    for (int i = 0; i <= rank; i++) {
        local_buffer[i] = my_char;
    }

    // 3. Gather all buffers back to root. 
    char gathered_matrix[size * N];
    MPI_Gather(local_buffer, N, MPI_CHAR, gathered_matrix, N, MPI_CHAR, 0, MPI_COMM_WORLD);

    // 4. Root displays the result
    if (rank == 0) {
        printf("Output: ");
        for (int i = 0; i < size * N; i++) {
            if (gathered_matrix[i] != 0) {
                printf("%c", gathered_matrix[i]);
            }
        }
        printf("\n");
    }

    MPI_Finalize();
    return 0;
}
