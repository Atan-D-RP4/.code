// Experiment 9 - Virtual Memory
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define NFP 10

typedef struct Process {
	int pid;
	int pages;
	int page_table[NFP][2];
} Process;

int main() {
	size_t f, fsize, np, nfpp;

	printf("Enter total number of frames: ");
	scanf("%zu", &f);

	printf("Enter size of each frame: ");
	scanf("%zu", &fsize);

	printf("Memory size: %zu\n", fsize * f);

	printf("Enter number of processes: ");
	scanf("%zu", &np);

	printf("Enter number of frames per process: ");
	scanf("%zu", &nfpp);

	printf("Remaining frames: %d\n", (int) (f - np * nfpp));

	Process p[np];
	int frame_no = 0;

	for (size_t i = 0; i < np; ++i) {
		printf("Enter number of pages per process %zu: ", i + 1);
		scanf("%d", &p[i].pages); // Corrected index from np to i
		printf("Enter the pages to be allocated to process %zu\n", i + 1);
		for (size_t j = 0; j < nfpp; ++j) {
			scanf("%d", &p[i].page_table[j][0]);
			p[i].page_table[j][1] = frame_no++;
		}
	}

	for (size_t i = 0; i < np; ++i) {
		printf("Page table for process %zu\n", i + 1);
		printf("Page\tFrame\n");
		for (size_t j = 0; j < nfpp; ++j) {
			printf("%4d\t%5d\n", p[i].page_table[j][0], p[i].page_table[j][1]);
		}
		printf("\n");
	}

	int ch = 1; // To ensure loop runs initially

	while (ch == 1) {
		int pno, inst;
		int found = 0, frame = 0;

		printf("Enter process number: ");
		scanf("%d", &pno);
		printf("Enter instruction no. to be executed: ");
		scanf("%d", &inst);

		// Correct the page calculation
		int page = inst / f;
		page = (inst % f != 0) ? page + 1 : page;

		for (size_t i = 0; i < nfpp; ++i) {
			if (p[pno - 1].page_table[i][0] == page) {
				found = 1;
				frame = p[pno - 1].page_table[i][1];
				break;
			}
		}

		if (found == 1) {
			int loc = frame * f + (inst - 1) % f;
			printf("Instruction %d is in frame %d at location %d\n", inst, frame, loc + 1);
		} else {
			printf("Instruction %d is not found\n", inst);
			printf("Page fault\n");
		}

		printf("Do you want to continue? (1 for yes, 0 for no): ");
		sleep(1);
		scanf("%d", &ch); // Prompt user to continue or not
	}

	return 0;
}


/* ----------------- OUTPUT -----------------
 *
 *   Enter total number of frames: 10
 *   Enter size of each frame: 3
 *   Memory size: 30
 *   Enter number of processes: 3
 *   Enter number of frames per process: 3
 *   Remaining frames: 1
 *   Enter number of pages per process 1: 1
 *   Enter the pages to be allocated to process 1
 *   2 3 4
 *   Enter number of pages per process 2: 3
 *   Enter the pages to be allocated to process 2
 *   5 6 7
 *   Enter number of pages per process 3: 3
 *   Enter the pages to be allocated to process 3
 *   8 9 10
 *   Page table for process 1
 *   Page    Frame
 *   2        0
 *   3        1
 *   4        2
 *
 *   Page table for process 2
 *   Page    Frame
 *   5        3
 *   6        4
 *   7        5
 *
 *   Page table for process 3
 *   Page    Frame
 *   8        6
 *   9        7
 *   10        8
 *   Enter process number: 1
 *   Enter instruction no. to be executed: 4
 *   Instruction 4 is in frame 0 at location 1
 *   Do you want to continue? (1 for yes, 0 for no): 1
 *   Enter process number: 1
 *   Enter instruction no. to be executed: 6
 *   Instruction 6 is in frame 0 at location 3
 *
 * */
