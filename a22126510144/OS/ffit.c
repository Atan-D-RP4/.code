// Experiment 10.1 - First Fit Algorithm
#include <stdio.h>

int main(void)
{
	int bsize[10], psize[10], bno, pno, flags[10], allocs[10];

	for (size_t i = 0; i < 10; i++)
	{
		flags[i] = 0;
		allocs[i] = -1;
	}

	printf("Enter the number of blocks: ");
	scanf("%d", &bno);

	printf("Enter the size of the blocks: ");
	for (size_t i = 0; i < bno; i++)
	{
		scanf("%d", &bsize[i]);
	}

	printf("Enter the number of processes: ");
	scanf("%d", &pno);

	printf("Enter the size of the processes: ");
	for (size_t i = 0; i < pno; i++)
	{
		scanf("%d", &psize[i]);
	}

	for (size_t i = 0; i < pno; i++)
	{
		for (size_t j = 0; j < bno; j++)
		{
			if (flags[j] == 0 && bsize[j] >= psize[i])
			{
				allocs[j] = i;
				flags[j] = 1;
				break;
			}
		}
	}

	int intf[100] = { 0 };

	for (size_t i = 0; i < pno; ++i) {
		if (bsize[i] >= psize[i]) {
			intf[i] = bsize[i] - psize[i];
		}
	}

	printf("First Fit\n");
	printf("Block no.\tBlock size\tProcess no.\tProcess size\tInternal Fragmentation");
	for (size_t i = 0; i < bno; i++)
	{
		printf("\n%zu\t\t%d\t\t", i + 1, bsize[i]);
		if (flags[i] == 1)
		{
			printf("%d\t\t%d\t\t%d", allocs[i] + 1, psize[allocs[i]], intf[i]);
		}
		else
		{
			printf("Not allocated");
		}
	}
	printf("\n");

	return 0;
}


/* ----------------- OUTPUT -----------------
 *
 *	Enter the number of blocks: 3
 *	Enter the size of the blocks:
 *	8 10 12
 *	Enter the number of processes: 3
 *	Enter the size of the processes:
 *	2 3 12
 *	 Fist Fit
 *
 *	Block no.       Block size      Process no.     Process size    Internal Fragmentation
 *	1               8               1               2               6
 *	2               10              2               3               7
 *	3               12              3               12              0
 *
 */
