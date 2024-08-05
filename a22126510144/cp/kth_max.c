// Kth maximum element in an array with O(nk), O(nlogn) and O(nlogk) time complexity
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int cmp(const void *a, const void *b) {
	return *(int *)a - *(int *)b;
}

int main(void) {
	printf("Enter the number of elements: ");
	int n; scanf("%d", &n);

	int arr[n];

	printf("Enter the elements: ");
	for (size_t i = 0; i < n; ++i) {
		scanf("%d", &arr[i]);
	}

	printf("Enter the value of k: ");
	int k; scanf("%d", &k);

	// Find the kth maximum element with O(nk) time complexity
	int max = 0;
	for (size_t i = 0; i < k; ++i) {
		for (size_t j = 0; j < n; ++j) {
			if (arr[j] >= arr[max]) {
				max = j;
			}
		}
		if (i != k - 1) {
			arr[max] = 0;
		}
	}
	printf("The %dth maximum element is: %d\n", k, arr[max]);

	// Find the kth maximum element with O(nlogn) time complexity
	qsort(arr, n, sizeof(int), cmp);
	printf("The %dth maximum element is: %d\n", k, arr[n - k + 1]);

	// Find the kth maximum element with O(nlogk) time complexity
	int h = k - 1;
	int queue[h];
	for (size_t i = 0; i < h; ++i) {
		queue[i] = arr[i];
	}
	qsort(queue, h, sizeof(int), cmp);
	for (size_t i = k; i < n; ++i) {
		if (arr[i] > queue[0]) {
			queue[0] = arr[i];
			qsort(queue, k, sizeof(int), cmp);
		}
	}
	printf("The %dth maximum element is: %d\n", k, queue[0]);

}

/********************************OUTPUT***************************************
 *
 * Enter the number of elements: 5
 * Enter the elements: 1 2 3 4 5
 * Enter the value of k: 2
 * The 2th maximum element is: 4
 * The 2th maximum element is: 4
 * The 2th maximum element is: 4
 *
 *****************************************************************************/
