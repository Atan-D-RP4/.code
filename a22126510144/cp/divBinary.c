// Division With Binary Search

#include <stdio.h>
#include <stdlib.h>
#include <float.h>

double bin_div(int dividend, int divisor) {
	// Check if divisor is 0
	if (divisor == 0) {
		printf("Error: Division by 0\n");
		exit(1);
	}

	// Check if dividend is 0
	if (dividend == 0) {
		return 0;
	}

	// Perform Division by Binary Search
	double low = 0, high = (double) dividend;
	double mid = 0;

	while (low <= high) {
		mid = low + (high - low) / 2;
		float diff = (mid * divisor) - dividend;
		if (diff > FLT_EPSILON) {
			high = mid - FLT_EPSILON;
		} else if (diff < -FLT_EPSILON) {
			low = mid + FLT_EPSILON;
		} else {
			break;
		}
	}
	return mid;
}

int main(void) {
	int dividend, divisor;
	float quotient;

	printf("Enter Dividend and Divisor(x/y): ");
	scanf("%d/%d", &dividend, &divisor);
	printf("Dividend: %d, Divisor: %d\n", dividend, divisor);

	quotient = bin_div(dividend, divisor);

	printf("Quotient: %.5f\n", quotient);

}

/********************************OUTPUT***************************************
 * Enter Dividend and Divisor(x/y): 22/7
 * Dividend: 22, Divisor: 7
 * Quotient: 3.14286
 *
 * Enter Dividend and Divisor(x/y): 10/3
 * Dividend: 10, Divisor: 3
 * Quotient: 3.33333
 *****************************************************************************/
