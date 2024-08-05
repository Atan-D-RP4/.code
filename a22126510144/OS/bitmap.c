// Experiment 12 - Bitmap Allocation
#include <stdio.h>

int main(void) {
	int a[32], n;

	for (size_t i = 1; i <= 32; i++) {
		a[i] = 1;
	}

	printf("No. of Blocks to allocate: ");
	scanf("%d", &n);

	printf("Which blocks need to be allocated: ");
	for (size_t i = 0; i < n; i++) {
		int x;
		scanf("%d", &x);
		a[x] = a[x] == 1 ? 0 : a[x];
	}
	printf("\n");

	printf("Allocated blocks are: \n");
	printf("Index\tAllocation\n");
	for (size_t i = 1; i <= 32; i++) {
		printf("%zu\t%d\n", i, a[i]);
	}

}

/* ----------------- OUTPUT -----------------
 *
 *	No. of Blocks to allocate: 9
 * 	Which blocks need to be allocated: 2 3 4 5 8 9 10 11 12
 *
 *	Allocated blocks are:
 *	Index   Allocation
 *	1       1
 *	2       0
 *	3       0
 *	4       0
 *	5       0
 *	6       1
 *	7       1
 *	8       0
 *	9       0
 *	10      0
 *	11      0
 *	12      0
 *	13      1
 *	14      1
 *	15      1
 *	16      1
 *	17      1
 *	18      1
 *	19      1
 *	20      1
 *	21      1
 *	22      1
 *	23      1
 *	24      1
 *	25      1
 *	26      1
 *	27      1
 *	28      1
 *	29      1
 *	30      1
 *	31      1
 *	32      1
 *
 */
