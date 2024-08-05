// Experiment 8 - Paging Algorithms
#include <limits.h>
#include <stdio.h>
#include <string.h>

// 1 2 1 3 7 4 5 6 3 1 2 4 6 3 1
int printTable(int pages[], int n, int capacity, char *policy) {
	int pageFaults = 0;
	int pageFrames[capacity];
	int pageFutureRef[capacity];
	int lruCounter[capacity];
	int fifoIndex = 0;

	// Initialize all page frames as -1
	for (int i = 0; i < capacity; i++) {
		pageFrames[i] = -1;
	}

	// Initialize lruCounter for LRU algorithm
	for (int i = 0; i < capacity; i++) {
		lruCounter[i] = -1;
	}

	printf("\nPage Replacement Policy: %s\n", policy);
	printf("Reference String | Page Frames  | Page Faults\n");
	printf("-----------------|--------------|------------\n");

	// Fill the pageFutureRef array for OPT algorithm
	if (!strcmp(policy, "OPT")) {
		for (int i = 0; i < capacity; i++) {
			pageFutureRef[i] = INT_MAX;
			for (int j = i + 1; j < n; j++) {
				if (pages[j] == pages[i]) {
					pageFutureRef[i] = j;
					break;
				}
			}
		}
	}

	// Iterate through the reference string
	for (int i = 0; i < n; i++) {
		int pageIndex = -1;
		int farthestRef = INT_MIN;
		int lruIndex = INT_MAX;

		// Check if the page is already present in the page frames
		int presentFlag = 0;
		for (int j = 0; j < capacity; j++) {
			if (pageFrames[j] == pages[i]) {
				presentFlag = 1;
				if (!strcmp(policy, "LRU")) {
					lruCounter[j] = i;
				}
				break;
			}
		}

		// If not present, find the page to be replaced
		if (!presentFlag) {
			pageFaults++;
			if (!strcmp(policy, "FIFO")) {
				pageIndex = fifoIndex;
				fifoIndex = (fifoIndex + 1) % capacity;
			} else if (!strcmp(policy, "LRU")) {
				for (int j = 0; j < capacity; j++) {
					if (lruCounter[j] < lruIndex) {
						lruIndex = lruCounter[j];
						pageIndex = j;
					}
				}
			} else if (!strcmp(policy, "OPT")) {
				for (int j = 0; j < capacity; j++) {
					int futureRef = INT_MAX;
					for (int k = i + 1; k < n; k++) {
						if (pages[k] == pageFrames[j]) {
							futureRef = k;
							break;
						}
					}
					if (futureRef > farthestRef) { // Find the farthest reference
						farthestRef = futureRef;
						pageIndex = j;
					}
				}
			}
			pageFrames[pageIndex] = pages[i];
			if (!strcmp(policy, "LRU")) {
				lruCounter[pageIndex] = i;
			}
		}

		// Print the current state
		printf("%16d | ", pages[i]);
		for (int j = 0; j < capacity; j++) {
			printf("%2d ", pageFrames[j]);
		}
		printf("\t| %2d\n", pageFaults);
	}

	printf("Total page faults: %d\n\n", pageFaults);
	return pageFaults;
}

int main() {

	int len, capacity;
	printf("Enter Reference String Length: ");
	scanf("%d", &len);
	int pages[len];

	printf("Enter Reference String: ");
	for (int i = 0; i < len; i++) {
		scanf("%d", &pages[i]);
	}

	printf("Capacity of Page Frames: ");
	scanf("%d", &capacity);

	int pf_fifo = printTable(pages, len, capacity, "FIFO");
	int pf_lru = printTable(pages, len, capacity, "LRU");
	int pf_opt = printTable(pages, len, capacity, "OPT");

	printf("Page faults for FIFO: %d\n", pf_fifo);
	printf("Page faults for LRU: %d\n", pf_lru);
	printf("Page faults for OPT: %d\n", pf_opt);

	printf("Least number of page faults is given by: ");

	if (pf_fifo < pf_lru && pf_fifo < pf_opt) {
		printf("FIFO\n");
	} else if (pf_lru < pf_fifo && pf_lru < pf_opt) {
		printf("LRU\n");
	} else {
		printf("OPT\n");
	}

	return 0;
}

/* ----------------- OUTPUT -----------------
 * Enter Reference String Length: 15
 * Enter Reference String: 1 2 1 3 7 4 5 6 3 1 2 4 6 3 1
 * Capacity of Page Frames: 3
 *
 * Page Replacement Policy: FIFO
 * Reference String | Page Frames  | Page Faults
 * -----------------|--------------|------------
 *                1 |  1 -1 -1     |  1
 *                2 |  1  2 -1     |  2
 *                1 |  1  2 -1     |  2
 *                3 |  1  2  3     |  3
 *                7 |  7  2  3     |  4
 *                4 |  7  4  3     |  5
 *                5 |  7  4  5     |  6
 *                6 |  6  4  5     |  7
 *                3 |  6  3  5     |  8
 *                1 |  6  3  1     |  9
 *                2 |  2  3  1     | 10
 *                4 |  2  4  1     | 11
 *                6 |  2  4  6     | 12
 *                3 |  3  4  6     | 13
 *                1 |  3  1  6     | 14
 * Total page faults: 14
 *
 *
 * Page Replacement Policy: LRU
 * Reference String | Page Frames  | Page Faults
 * -----------------|--------------|------------
 *                1 |  1 -1 -1     |  1
 *                2 |  1  2 -1     |  2
 *                1 |  1  2 -1     |  2
 *                3 |  1  2  3     |  3
 *                7 |  1  7  3     |  4
 *                4 |  4  7  3     |  5
 *                5 |  4  7  5     |  6
 *                6 |  4  6  5     |  7
 *                3 |  3  6  5     |  8
 *                1 |  3  6  1     |  9
 *                2 |  3  2  1     | 10
 *                4 |  4  2  1     | 11
 *                6 |  4  2  6     | 12
 *                3 |  4  3  6     | 13
 *                1 |  1  3  6     | 14
 * Total page faults: 14
 *
 *
 * Page Replacement Policy: OPT
 * Reference String | Page Frames  | Page Faults
 * -----------------|--------------|------------
 *                1 |  1 -1 -1     |  1
 *                2 |  1  2 -1     |  2
 *                1 |  1  2 -1     |  2
 *                3 |  1  2  3     |  3
 *                7 |  1  7  3     |  4
 *                4 |  1  4  3     |  5
 *                5 |  1  5  3     |  6
 *                6 |  1  6  3     |  7
 *                3 |  1  6  3     |  7
 *                1 |  1  6  3     |  7
 *                2 |  2  6  3     |  8
 *                4 |  4  6  3     |  9
 *                6 |  4  6  3     |  9
 *                3 |  4  6  3     |  9
 *                1 |  1  6  3     | 10
 * Total page faults: 10
 *
 * Page faults for FIFO: 14
 * Page faults for LRU: 14
 * Page faults for OPT: 10
 * Least number of page faults is given by: OPT
 */
