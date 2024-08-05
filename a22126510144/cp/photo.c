// Photo-Shoot Problem
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void solve() {
	int n; scanf("%d", &n);
	int arr[n];

	for (size_t i = 0; i < n; ++i) {
		scanf("%d", &arr[i]);
	}

	if (arr[0] < arr[n - 1]) {
		for (size_t i = 0; i < n - 1; ++i) {
			if (!(arr[i] <= arr[i + 1])) {
				printf("N %ld\n", i);
				return;
			}
		}
		printf("L\n");
	} else {
		for (size_t i = 0; i < n - 1; ++i) {
			if (!(arr[i] >= arr[i + 1])) {
				printf("N\n");
				return;
			}
		}
		printf("R\n");
	}
	return;
}

int main(int argc, char *argv[]) {
	int t; scanf("%d", &t);

	while (t--) {
		solve();
	}
}

/********************************OUTPUT***************************************
 * N 1
 * R
 * R
 * L
 * N 2
 * R
 * N
 * N 2
 * L
 * L
 *****************************************************************************/
