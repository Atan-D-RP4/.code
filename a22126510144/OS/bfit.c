// Experiment 10.2 - Best Fit Algorithm
#include <stdio.h>
#include <stdbool.h>

int main(void) {

	int n, p, total = 0;

	printf("Enter the number of processes: ");
	scanf("%d", &p);

	int proc_size[p];

	printf("Memory Required by each process: ");
	for(size_t i = 0; i < p; ++i) {
		scanf("%d", &proc_size[i]);
	}

	printf("Enter the number of Memory Partitions: ");
	scanf("%d", &n);

	int block_size[n];
	printf("Memory Size of each partition: ");
	for(size_t i = 0; i < n; ++i) {
		scanf("%d", &block_size[i]);
		total += block_size[i];
	}

	printf("Best Fit:\n");

	int alloc[p], sum = 0, best_index = 0;
	bool external[n];

	for (size_t i = 0; i < p; ++i) {
		alloc[i] = -1;
	}

	for (size_t i = 0; i < n; ++i) {
		external[i] = false;
	}

	for (size_t i = 0; i < p; ++i) {
		best_index = -1;
		for (size_t j = 0; j < n; ++j) {
			if (!external[j] && block_size[j] >= proc_size[i]) {
				if (best_index == -1) {
					best_index = j;
				} else if (block_size[best_index] > block_size[j]) {
					best_index = j;
				}
			}

			if (best_index != -1) {
				alloc[i] = best_index;
				external[best_index] = true;
			}
		}
	}

	printf("Process No.\tProcess Size\tBlock Size\tInternal Fragmentation\n");
	for (size_t i = 0; i < p; ++i) {
		printf("%zu\t\t%d\t\t", i + 1, proc_size[i]);
		if (alloc[i] == -1) {
			printf("Not Allocated\n");
		} else {
			printf("%d\t\t%d\n", block_size[alloc[i]], block_size[alloc[i]] - proc_size[i]);
		}
	}

	printf("External Fragmentation: \n");
	for (size_t i = 0; i < n; ++i) {
		if (!external[i]) {
			sum += block_size[i];
			printf("Block: %zu\n", i);
		}
	}
	printf("Total External Fragmentation: %d\n", sum);


	return 0;
}

/* ----------------- OUTPUT -----------------
 *
 *	Enter the number of processes: 4
 *	Memory Required by each process:
 *	150 50 230 300
 *	Enter the number of Memory Partitions: 5
 *	Memory Size of each partition:
 *	50 100 200 300 400
 *	Best Fit:
 *	Process No.     Process Size    Block Size      Internal Fragmentation
 *	1               150             200             50
 *	2               50              50              0
 *	3               230             300             70
 *	4               300             400             100
 *	External Fragmentation: Block: 1
 *	Total External Fragmentation: 100
 *
 */
