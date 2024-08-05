#include <stddef.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <limits.h>

#define typeof(x) _Generic((x), \
	int: "int", 		\
	float: "float", 	\
	double: "double", 	\
	char: "char", 		\
	bool: "bool", 		\
	default: "other") 	\

#define max(a, ...) ({ \
    typeof(a) args[] = {a, __VA_ARGS__}; \
    typeof(a) max = args[0]; \
    for (size_t i = 1; i < sizeof(args) / sizeof(args[0]); ++i) { \
        if (args[i] > max) { \
            max = args[i]; \
        } \
    } \
    max; \
})

#define min(a, ...) ({ \
    typeof(a) args[] = {a, __VA_ARGS__}; \
    typeof(a) min = args[0]; \
    for (size_t i = 1; i < sizeof(args) / sizeof(args[0]); ++i) { \
        if (args[i] < min) { \
            min = args[i]; \
        } \
    } \
    min; \
})

typedef struct ListNode
{
    uint8_t data;
    struct ListNode* link;
} ListNode;

typedef struct String {
	char* str;
	size_t count;
} String;

void swap(int* a, int* b);
bool checkLoop(ListNode *start);
int* arraySum(int* arr1, int* arr2, int size);
int bin_search(int *array, int left, int right, int key);
void show_bin_num(int a);
bool check_prime(int num);
int bit_divide(int dividend, int divisor);
int bit_product(int a, int b);
int bit_diff(int x, int y);
unsigned int bit_sum(int a, int b);
char* strrev(char* string, int size);
char* get_string(char* s);
int BinomialCoefficient(int n, int r);

int BinomialCoefficient(int n, int r) {
	if (n < r || r < 0 || n < 0)
		return -1;

	if (r == 0 || r == n || n == 0) return 1;
		return BinomialCoefficient(n - 1, r - 1) + BinomialCoefficient(n - 1, r);
}

char* get_string(char* s)
{
    typedef struct node
    {
        char character;
        struct node *next;
    } node;

    // Implementation of dynamic string
    node *list = NULL;
    printf("%s", s);
    int x = 0;
    int char_count = 0;
    while (1) // Take user inputed dynamic string
    {
        char character;
        node *new = malloc(sizeof(node));
        if (new == NULL)
        {
            printf("ERROR: Couldn't allocate memory\n");
            exit(0);
        }
        scanf("%c", &character);
        if (character == '\n') // Exit case when user has completed
        {
            free(new);
            break;
        }

        new->character = character;
        new->next = list;
        list = new;
        char_count++;
    }

    // Copy string to an array
    char* string = (char*)malloc(sizeof(char) * (char_count + 1));
    node *new = list;
    for (int i = char_count - 1; i >= 0; i--) // Also cleans the nodes after use
    {
        string[i] = new->character;
        node *tmp = new->next;
        free(new);
        new = tmp;
    }
    string[char_count] = '\0'; // Now this string is in usable format
    return string;
}

char* strrev(char* string, int size)
{
    char* rev_string = (char*)malloc(sizeof(char) * size);

    for (int i = size - 1, j = 0; i >= 0 && j < size;)
        rev_string[j++] = string[i--];
    rev_string[size] = '\0';
    return rev_string;
}

int rev(int num)
{
    int rev_num = 0;
    while (num > 0)
    {
        rev_num = rev_num * 10 + num % 10;
        num /= 10;
    }
    return rev_num;
}

unsigned int bit_sum(int a, int b)
{
    int result = a ^ b;
    int carry = (a & b) << 1;
    if (carry == 0)
        return result;
    else
        return bit_sum(carry, result);
}

int bit_diff(int x, int y) {
    while (y != 0) {
        // Borrow contains common set bits of y and unset bits of x
        int borrow = (~x) & y;

        // Subtraction of bits of x and y where at least one of the bits is not set
        x = x ^ y;

        // Borrow is shifted by one so that subtracting it from x gives the required difference
        y = borrow << 1;
    }
    return x;
}

int bit_product(int a, int b)
{
    int result = 0;
    while (b > 0)
    {
        if (b & 1)
            result += a;
        a = a << 1;
        b = b >> 1;
    }
    return result;
}

int bit_divide(int dividend, int divisor) {
    // Handle special cases
    if (divisor == 0) {
        printf("Error: Division by zero\n");
        return 0;
    }

    if (dividend == 0) {
        return 0;
    }

    if (dividend == INT_MIN && divisor == -1) {
        printf("Error: Integer overflow\n");
        return INT_MAX;
    }

    // Determine the sign of the result
    int sign = (dividend < 0) ^ (divisor < 0) ? -1 : 1;

    // Make both dividend and divisor positive
    unsigned int u_dividend = (dividend < 0) ? -dividend : dividend;
    unsigned int u_divisor = (divisor < 0) ? -divisor : divisor;

    // Initialize the quotient
    int quotient = 0;

    // Bitwise division
    while (u_dividend >= u_divisor) {
        int shift = 0;

        // Keep left-shifting the divisor until it's greater than the dividend
        while (u_dividend >= (u_divisor << shift)) {
            shift++;
        }

        // Update the dividend and quotient
        u_dividend -= u_divisor << (shift - 1);
        quotient += 1 << (shift - 1);
    }

    return sign * quotient;
}

bool check_prime(int num)
{
    if(((num % 6 == 5 || num % 6 == 1)) || ((num == 3 || num == 2)))
    {
        return true;
    }
    return false;
}

void show_bin_num(int a)
{
    if (a == 0)
    {
        printf("0\n");
        return;
    }
    int bin[32]; int i, j;
    printf("%2d in Binary: ", a);
    for (i = 0; a > 0 && i < 32; a /= 2)
    {
        bin[i++] = a % 2;
    }
    for (j = i - 1; j >= 0; j--)
        printf("%d", bin[j]);
    printf("\n");
}

int bin_search(int *arr, int left, int right, int key)
{
    if (right >= 0)
    {
        int mid = left + ((right - 1)/ 2);
        if (key == arr[mid])
            return mid;
        else if (key < arr[mid])
            return bin_search(arr, left, mid - 1, key);
        else if (key > arr[mid])
            return bin_search(arr, mid + 1, right, key);
    }
    printf("%d  Not Found in Stored Data\n", key);
    exit(0);
}

int* arraySum(int* arr1, int* arr2, int size)
{
    int *arrSum = (int*)calloc(size + 1, sizeof(int)), carry = 0;
    arrSum[size] = -1;

    // Logic for addition of the single-digit arrays arr1 and arr2

    for (int i = 0; i < size; i++)
    {
        int sum = arr1[i] + arr2[i] + carry;
        arrSum[i] = sum % 10;  // Store the current digit in arrSum

        carry = sum / 10;  // Update carry for the next iteration
    }

    // If there is a carry after the loop, store it in the extra digit
    if (carry > 0)
    {
        arrSum[size] = carry;
    }

    return arrSum;
}

bool checkLoop(ListNode *start)
{
    // Awesome debug function for Linked Lists
    ListNode *slow, *fast;
    slow = fast = start;
    while (fast != NULL && fast->link != NULL)
    {
        slow = slow->link;
        fast = fast->link->link;
        if (fast == slow)
        {
            slow = start;
            int index = 0;
            while (slow != fast)
            {
                index++;
                slow = slow->link;
                fast = fast->link;
            }
            printf("List has Looped at node with data %d at position %d\n", slow->data, index);
            return true;
        }
    }

    return false;
}

void swap(int* a, int* b)
{
    if(a != b)
    {
        *a ^= *b;
        *b ^= *a;
        *a ^= *b;
    }
}
