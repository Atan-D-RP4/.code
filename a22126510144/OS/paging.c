// Experiment 8 - Paging Algorithms
#include <stdio.h>
#include <stdbool.h>

int n, f;
int in[100];
int p[50];
int hit = 0, fault = 0;
int fifo_count = 0, opt_count = 0, lru_count = 0;

void get_data() {
    printf("Enter the number of frames: ");
    scanf("%d", &f);
    printf("Enter the number of pages: ");
    scanf("%d", &n);
    printf("Enter the reference string: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &in[i]);
    }
}

void init() {
    fault = 0;
    for (int i = 0; i < f; i++) {
        p[i] = 9999;
    }
}

int isHit(int data) {
    hit = 0;
    for (int i = 0; i < f; i++) {
        if (p[i] == data) {
            hit = 1;
            break;
        }
    }
    return hit;
}

void displayPages() {
    for (int i = 0; i < f; i++) {
        if (p[i] != 9999) {
            printf("%d ", p[i]);
        }
    }
}

void displayPageFaults() {
    printf("\n\nTotal page faults: %d\n", fault);
}

void fifo() {
    init();
    int j = 0;
    printf("\nFIFO:\n");
    for (int i = 0; i < n; i++) {
        printf("\nFor %d: ", in[i]);
        if (isHit(in[i]) == 0) {
            for (int k = 0; k < f - 1; k++) {
                p[k] = p[k + 1];
            }
            p[f - 1] = in[i];
            fault++;
            fifo_count++;
            displayPages();
        } else {
            printf("No page fault");
        }
    }
    fifo_count = fault;
    displayPageFaults();
}

void optimal() {
    init();
    int near[50];
    printf("\nOptimal:\n");
    for (int i = 0; i < n; i++) {
        printf("\nFor %d: ", in[i]);
        if (isHit(in[i]) == 0) {
            for (int k = 0; k < f; k++) {
                int pg = p[k];
                int found = 0;
                for (int l = i; l < n; l++) {
                    if (pg == in[l]) {
                        near[k] = l;
                        found = 1;
                        break;
                    } else {
                        found = 0;
                    }
                }
                if (!found) {
                    near[k] = 9999;
                }
            }
            int max = -9999;
            int repindex;
            for (int k = 0; k < f; k++) {
                if (near[k] > max) {
                    max = near[k];
                    repindex = k;
                }
            }
            p[repindex] = in[i];
            fault++;
            opt_count++;
            displayPages();
        } else {
            printf("No page fault");
        }
    }
    opt_count = fault;
    displayPageFaults();
}

void lru() {
    init();
    int least[50];
    printf("\nLRU:\n");
    for (int i = 0; i < n; i++) {
        printf("\nFor %d: ", in[i]);
        if (isHit(in[i]) == 0) {
            for (int k = 0; k < f; k++) {
                int pg = p[k];
                int found = 0;
                for (int l = i - 1; l >= 0; l--) {
                    if (pg == in[l]) {
                        least[k] = l;
                        found = 1;
                        break;
                    } else {
                        found = 0;
                    }
                }
                if (!found) {
                    least[k] = -9999;
                }
            }
            int min = 9999;
            int repindex;
            for (int k = 0; k < f; k++) {
                if (least[k] < min) {
                    min = least[k];
                    repindex = k;
                }
            }
            p[repindex] = in[i];
            fault++;
            lru_count++;
            displayPages();
        } else {
            printf("No page fault");
        }
    }
    lru_count = fault;
    displayPageFaults();
}

void compare() {
    if (fifo_count < opt_count && fifo_count < lru_count) {
        printf("\n\nFIFO has the least page faults");
    } else if (opt_count < fifo_count && opt_count < lru_count) {
        printf("\n\nOptimal has the least page faults");
    } else {
        printf("\n\nLRU has the least page faults");
    }
    printf("\n\n");
}

int main() {
    get_data();
    fifo();
    optimal();
    lru();
    printf("\n\nFIFO: %d\nOptimal: %d\nLRU: %d\n", fifo_count, opt_count, lru_count);
    compare();
    return 0;
}
