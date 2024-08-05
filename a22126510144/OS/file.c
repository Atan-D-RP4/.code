// Experiment 11 - Contiguos File Allocation
#include <stdio.h>

int main(void) {

	int n = 0;
	int c = 0;
	int file[10];
	int len[10];

	printf("No.of Files to allocate: ");
	scanf("%d", &n);

	printf("Enter File no. to allocate: ");
	for (int i = 1; i <= n; i++) {
		scanf("%d", &file[i]);
	}

	printf("Enter File length: ");
	for (int i = 1; i <= n; i++) {
		scanf("%d", &len[i]);
	}

	printf("Allocated File data: \n");
	printf("File Name\tFile Length\tStart Block\n");
	int k = 1, count = 0, i = 1;
	while (i <= n) {
		int z = k + len[i];
		count += len[i];
		printf("%d\t\t%d\t\t%d\n", file[i], len[i], count - len[i] + 1);
		printf("\n");
		++i;
	}

	return 0;
}

/* ----------------- OUTPUT -----------------
 *
 *	No.of Files to allocate: 2
 *	Enter File no. to allocate: 1 2
 *	Enter File length: 4 10
 *	Allocated File data:
 *	File Name       File Length     Start Block
 *	1               4               1
 *
 *	2               10              5
 *
 */
