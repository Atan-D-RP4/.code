#include <stdio.h>
#include <stdbool.h>

#define MAX_FRAMES 3

#define REF_STRING_LENGTH 15
int findPageFault(int refString[], int policy);
void fifo(int refString[], int frames[], int pointer, int fault);
void lru(int refString[], int frames[], int pointer, int fault);
void optimal(int refString[], int frames[], int pointer, int fault);

int main() {

    int refString[REF_STRING_LENGTH];
    // 1 2 1 3 7 4 5 6 3 1 2 4 6 3 1
    printf("Enter the reference string: ");
    for (int i = 0; i < REF_STRING_LENGTH; i++)
        scanf("%d", &refString[i]);

    printf("Page Faults with FIFO: %d\n\n", findPageFault(refString, 0));
    printf("Page Faults with LRU: %d\n\n", findPageFault(refString, 1));
    printf("Page Faults with Optimal: %d\n\n", findPageFault(refString, 2));

    return 0;
}

int findPageFault(int refString[], int policy) {
    int frames[MAX_FRAMES];
    bool hit;
    int pointer = 0;
    int fault = 0;

    for (int i = 0; i < MAX_FRAMES; i++)
        frames[i] = -1;

    for (int i = 0; i < REF_STRING_LENGTH; i++) {
        hit = false;
        for (int j = 0; j < MAX_FRAMES; j++) {
            if (frames[j] == refString[i]) {
                hit = true;
                break;
            }
        }

        if (!hit) {
            fault++;
            switch (policy) {
                case 0:
                    fifo(refString, frames, pointer, fault);
                    break;
                case 1:
                    lru(refString, frames, pointer, fault);
                    break;
                case 2:
                    optimal(refString, frames, pointer, fault);
                    break;
            }
        }
    }

    return fault;
}

void fifo(int refString[], int frames[], int pointer, int fault) {
    printf("Page Fault %d: ", fault);
    for (int i = 0; i < MAX_FRAMES; i++)
        printf("%d ", frames[i]);
    printf("-> %d\n", refString[pointer]);

    frames[pointer] = refString[pointer];
    pointer = (pointer + 1) % MAX_FRAMES;
}

void lru(int refString[], int frames[], int pointer, int fault) {
    int least = pointer;
    printf("Page Fault %d: ", fault);
    for (int i = 0; i < MAX_FRAMES; i++)
        printf("%d ", frames[i]);
    printf("-> %d\n", refString[pointer]);

    for (int i = 0; i < MAX_FRAMES; i++) {
        int j;
        for (j = pointer - 1; j >= 0; j--)
            if (frames[i] == refString[j])
                break;

        if (j == -1)
            least = i;
        else if (j < least)
            least = i;
    }

    frames[least] = refString[pointer];
}

void optimal(int refString[], int frames[], int pointer, int fault) {
    int max = -1;
    int index;
    printf("Page Fault %d: ", fault);
    for (int i = 0; i < MAX_FRAMES; i++)
        printf("%d ", frames[i]);
    printf("-> %d\n", refString[pointer]);

    for (int i = 0; i < MAX_FRAMES; i++) {
        int j;
        for (j = pointer; j < REF_STRING_LENGTH; j++) {
            if (frames[i] == refString[j]) {
                if (j > max) {
                    max = j;
                    index = i;
                }
                break;
            }
        }
        if (j == REF_STRING_LENGTH)
            index = i;
    }

    frames[index] = refString[pointer];
}

