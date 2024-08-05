// Experiment 7 - Safety Algorithm
#include <stdio.h>
int main()
{
	int i, j, m, n, k, alloc[10][10], max[10][10], avail[10];
	printf("Enter no. of processes:");
	scanf("%d", &n);
	printf("Enter resources:");
	scanf("%d", &m);
	printf("Enter allocation matrix:\n");
	for (i = 0; i < n; i++)
		for (j = 0; j < m; j++)
			scanf("%d", &alloc[i][j]);
	printf("enter max matrix:\n");
	for (i = 0; i < n; i++)
		for (j = 0; j < m; j++)
			scanf("%d", &max[i][j]);
	printf("Enter available:");
	for (i = 0; i < m; i++)
		scanf("%d", &avail[i]);
	int f[n], ans[n], ind = 0, need[n][m], y = 0;
	for (k = 0; k < n; k++)
		f[k] = 0;
	for (i = 0; i < n; i++)
		for (j = 0; j < m; j++)
			need[i][j] = max[i][j] - alloc[i][j];
	printf("Need matrix are:\n");
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < m; j++)
			printf("%d ", need[i][j]);
		printf("\n");
	}
	for (k = 0; k < 5; k++)
		for (i = 0; i < n; i++)
			if (f[i] == 0)
			{
				int flag = 0;
				for (j = 0; j < m; j++)
					if (need[i][j] > avail[j])
					{
						flag = 1;
						break;
					}
				if (flag == 0)
				{
					ans[ind++] = i;
					for (y = 0; y < m; y++)
						avail[y] += alloc[i][y];
					f[i] = 1;
				}
			}
	int flag = 1;
	for (i = 0; i < n; i++)
		if (f[i] == 0)
		{
			flag = 0;
			printf("The following system is not safe\n");
			break;
		}
	if (flag == 1)
	{
		printf("Following is safe sequence\n");
		printf("System have no deadlock\n");
		for (i = 0; i < n - 1; i++)
			printf("p%d->", ans[i]);
		printf("p%d\n", ans[n - 1]);
	}
	return 0;
}

/* ----------------- OUTPUT -----------------
 *
 *  Enter no. of processes: 5
 *	Enter resources: 4
 *	Enter allocation matrix:
 *	0 0 1 2
 *	2 0 0 0
 *	0 0 3 4
 *	2 3 5 4
 *	0 3 3 2
 *	enter max matrix:
 *	0 0 1 2
 *	2 7 5 0
 *	6 6 5 5
 *	4 3 5 6
 *	0 6 5 2
 *	Enter available: 3 3 2 0
 *	Need matrix are:
 *	0 0 0 0
 *	0 7 5 0
 *	6 6 2 1
 *	2 0 0 2
 *	0 3 2 0
 *	Following is safe sequence
 *	System have no deadlock
 *	p0->p3->p4->p1->p2
 *
 */
