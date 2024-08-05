// Maximum Sum of a Subarray
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int main(void) {
	printf("Enter the number of elements in the array: ");
	int n; scanf("%d", &n);

	int arr[n], sum = 0;
	for (int i = 0; i < n; i++) {
		printf("Enter the element at index %d: ", i);
		scanf("%d", &arr[i]);
		if (sum + arr[i] > sum) {
			sum += arr[i];
		}
	}
	printf("The maximum sum of a subarray is: %d\n", sum);
}

/********************************OUTPUT***************************************
* Enter the number of elements in the array: 5
* Enter the element at index 0: -4
* Enter the element at index 1: 1
* Enter the element at index 2: 3
* Enter the element at index 3: -1
* Enter the element at index 4: 5
* The maximum sum of a subarray is: 9
******************************************************************************/
