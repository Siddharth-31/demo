#include <stdio.h>
#include <stdbool.h>

#define P 5 // Number of processes
#define R 3 // Number of resources

int main() {
    int i, j, k;

    // Available resources
    int available[R] = {3, 3, 2};

    // Maximum resource demand of each process
    int max[P][R] = {
        {7, 5, 3},
        {3, 2, 2},
        {9, 0, 2},
        {2, 2, 2},
        {4, 3, 3}
    };

    // Resources currently allocated to each process
    int alloc[P][R] = {
        {0, 1, 0},
        {2, 0, 0},
        {3, 0, 2},
        {2, 1, 1},
        {0, 0, 2}
    };

    int need[P][R];

    // Calculate the need matrix
    for (i = 0; i < P; i++) {
        for (j = 0; j < R; j++) {
            need[i][j] = max[i][j] - alloc[i][j];
        }
    }

    bool finish[P] = {0};
    int safeSequence[P];
    int work[R];

    // Initialize work = available
    for (i = 0; i < R; i++) {
        work[i] = available[i];
    }

    int count = 0;
    while (count < P) {
        bool found = false;

        for (i = 0; i < P; i++) {
            if (!finish[i]) {
                bool canProceed = true;
                for (j = 0; j < R; j++) {
                    if (need[i][j] > work[j]) {
                        canProceed = false;
                        break;
                    }
                }

                if (canProceed) {
                    for (k = 0; k < R; k++) {
                        work[k] += alloc[i][k];
                    }
                    safeSequence[count++] = i;
                    finish[i] = true;
                    found = true;
                }
            }
        }

        if (!found) {
            printf("\nSystem is not in a safe state (Deadlock possible).\n");
            return 1;
        }
    }

    printf("\nSystem is in a safe state.\nSafe sequence is: ");
    for (i = 0; i < P; i++) {
        printf("P%d ", safeSequence[i]);
    }
    printf("\n");

    return 0;
}
