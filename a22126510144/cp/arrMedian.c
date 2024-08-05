// Median Of Two Sorted Arrays
#include <stdio.h>
#include <stdlib.h>

double findMedianSortedArrays(int* nums1, int nums1Size, int* nums2, int nums2Size) {
	int nums3Size = nums1Size + nums2Size;
	int nums3[nums3Size];
	int i = 0, j = 0, k = 0;
	int l = 0, h = nums3Size + 1;
	int mid = l + (h - 1) / 2;
	double median = 0;
	while (i < nums1Size && j < nums2Size)
	{
		if (nums1[i] < nums2[j])
			nums3[++k] = nums1[++i];
		else
			nums3[++k] = nums2[++j];
	}

	for (; i < nums1Size; nums3[++k] = nums1[++i]);

	for (; j < nums2Size; nums3[++k] = nums2[++j]);

	if (nums3Size % 2 == 0 && nums3Size > 1)
		median = (float)(nums3[mid - 1] + nums3[mid]) / 2;
	else
		median = nums3[mid];

	return median;
}

int main(void) {
	int n, m;
	printf("Enter Size of Two Arrays: ");
	scanf("%d %d", &n, &m);

	int arr1[n], arr2[m];

	printf("Enter The First Array: \n");
	for (int i = 0; i < n; ++i) {
		scanf("%d", &arr1[i]);
	}

	printf("Enter The Second Array: \n");
	for (int i = 0; i < m; ++i) {
		scanf("%d", &arr2[i]);
	}

	printf("The median of the two arrays is: %f\n", findMedianSortedArrays(arr1, n, arr2, m));
}

/********************************OUTPUT***************************************
 * Enter Size of Two Arrays: 5 6
 * Enter The First Array:
 * -5 3 6 12 15
 * Enter The Second Array:
 * -12 -10 -6 -3 4 10
 * The median of the two arrays is: 3.000000
 *
 * Enter Size of Two Arrays: 4 6
 * Enter The First Array:
 * 2 3 5 8
 * Enter The Second Array:
 * 10 12 14 16 18 20
 * The median of the two arrays is: 8.000000
 *****************************************************************************/
