// Experiment 7 - Safety Algorithm

#include <stddef.h>
#include <stdio.h>
#include <stdbool.h>

int P, R;

// Function to calculate the need matrix
void calculateNeed(int need[P][R], int max[P][R], int allocation[P][R]) {
	for (int i = 0; i < P; i++) {
		for (int j = 0; j < R; j++) {
			need[i][j] = max[i][j] - allocation[i][j];
		}
	}
}

// Function to check if the system is in a safe state
bool isSafe(int processes[], int avail[], int max[][R], int alloc[][R]) {
	int need[P][R];
	calculateNeed(need, max, alloc);

	bool finish[P];
	int safeSeq[P];
	int work[R];
	for (int i = 0; i < R; work[i] = avail[i++]);

	int count = 0;
	while (count < P) {
		bool found = false;
		for (int p = 0; p < P; p++) {
			if (finish[p] == 0) {
				int j;
				for (j = 0; j < R; j++) {
					if (need[p][j] > work[j])
						break;
				}
				if (j == R) {
					for (int k = 0; k < R; k++) {
						work[k] += alloc[p][k];
					}
					safeSeq[count++] = p;
					finish[p] = 1;
					found = true;
				}
			}
		}
		if (found == false) {
			printf("The system is in an unsafe state.\n");
			return false;
		}
	}
	printf("The system is in a safe state.\nSafe sequence is: ");
	for (int i = 0; i < P; i++) {
		printf("%d ", safeSeq[i]);
	}
	printf("\n");

	// Deadlock detection
	for (int i = 0; i < P; i++) {
		if (finish[i] == 0) {
			printf("Process %d is in deadlock\n", i);
			break;
		}
	}

	printf("No deadlock\n");

	return true;
}

int main() {

	int res_n, proc_n;
	printf("Enter no. of processes: ");
	scanf("%d", &proc_n);

	printf("Enter resources: ");
	scanf("%d", &res_n);

	P = proc_n, R = res_n;
	int procs[proc_n];
	int avail[res_n];
	int need[proc_n][res_n];
	int max[proc_n][res_n];
	int alloc[proc_n][res_n];

	printf("Enter allocation matrix: \n");
	for (size_t i = 0; i < proc_n; i++)
		for (size_t j = 0; j < res_n; j++)
			scanf("%d", &alloc[i][j]);

	printf("enter max matrix:\n");
	for (size_t i = 0; i < proc_n; i++)
		for (size_t j = 0; j < res_n; j++)
			scanf("%d", &max[i][j]);

	printf("Enter available: ");
	for (size_t i = 0; i < res_n; i++)
		scanf("%d", &avail[i]);

	// Print Need Matrix
	calculateNeed(need, max, alloc);
	printf("Need matrix:\n");
	for (size_t i = 0; i < proc_n; i++) {
		for (size_t j = 0; j < res_n; j++) {
			printf("%d ", need[i][j]);
		}
		printf("\n");
	}

	isSafe(procs, avail, max, alloc);

	return 0;
}
/* --- OUTPUT ---
 * Enter no. of processes: 5
 * Enter resources: 4
 *
 * Enter allocation matrix:
 * 0 0 1 2
 * 2 0 0 0
 * 0 0 3 4
 * 2 3 5 4
 * 0 3 3 2
 *
 * Enter max matrix:
 * 0 0 1 2
 * 2 7 5 0
 * 6 6 5 5
 * 4 3 5 6
 * 0 6 5 2
 *
 * Enter available: 3 3 2 0
 *
 * Need matrix:
 * 0 0 0 0
 * 0 7 5 0
 * 6 6 2 1
 * 2 0 0 2
 * 0 3 2 0
 *
 * The system is in a safe state.
 * Safe sequence is: 0 3 4 1 2
 * No deadlock
 * */
