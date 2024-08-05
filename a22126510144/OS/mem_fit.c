// Experiment 10: First And Best Fit Memory Allocation

#include <stdio.h>
#include <stdbool.h>

void best_fit(int blockSize[], int m, int processSize[], int n)
{
	int allocation[n];
	for (int i = 0; i < n; i++)
	{
		allocation[i] = -1;
	}

	for (int i = 0; i < n; i++)
	{
		int bestIdx = -1;
		for (int j = 0; j < m; j++)
		{
			if (blockSize[j] >= processSize[i])
			{
				if (bestIdx == -1)
				{
					bestIdx = j;
				}
				else if (blockSize[bestIdx] > blockSize[j])
				{
					bestIdx = j;
				}
			}
		}

		if (bestIdx != -1)
		{
			allocation[i] = bestIdx;
			blockSize[bestIdx] -= processSize[i];
		}
	}

	printf("\nProcess No.\tProcess Size\tBlock No.\n");
	for (int i = 0; i < n; i++)
	{
		printf(" %d\t\t%d\t\t", i + 1, processSize[i]);
		if (allocation[i] != -1)
		{
			printf("%d\n", allocation[i] + 1);
		}
		else
		{
			printf("Not Allocated\n");
		}
	}
}

void first_fit(int blockSize[], int m, int processSize[], int n)
{
	int allocation[n];
	for (int i = 0; i < n; i++)
	{
		allocation[i] = -1;
	}

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			if (blockSize[j] >= processSize[i])
			{
				allocation[i] = j;
				blockSize[j] -= processSize[i];
				break;
			}
		}
	}

	printf("\nProcess No.\tProcess Size\tBlock No.\n");
	for (int i = 0; i < n; i++)
	{
		printf(" %d\t\t%d\t\t", i + 1, processSize[i]);
		if (allocation[i] != -1)
		{
			printf("%d\n", allocation[i] + 1);
		}
		else
		{
			printf("Not Allocated\n");
		}
	}
}

int main(void)
{
	int blockSize[] = {100, 500, 200, 300, 600};
	int processSize[] = {212, 417, 112, 426};
	int m = sizeof(blockSize) / sizeof(blockSize[0]);
	int n = sizeof(processSize) / sizeof(processSize[0]);

	printf("\nFirst Fit\n");
	first_fit(blockSize, m, processSize, n);

	printf("\nBest Fit\n");
	best_fit(blockSize, m, processSize, n);

	return 0;
}
