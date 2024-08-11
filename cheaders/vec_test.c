#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NOB_IMPLEMENTATION
#include "nob.h"

#define VEC_IMPLEMENTATION
#include "vec.h"

int cmp(const void *a, const void *b) {
    return *(int *) a - *(int *) b;
}

int main() {
    srand(time(NULL));

    {
        Nob_String_View *vec_sv = Vec(Nob_String_View);

        vec_append(vec_sv, nob_sv_from_cstr("Hello"));
        vec_append(vec_sv, nob_sv_from_cstr(" "));
        vec_append(vec_sv, nob_sv_from_cstr("World"));
        vec_append(vec_sv, nob_sv_from_cstr("!"));


        Nob_String_View it_sv;
        vec_for_each(vec_sv, it_sv) {
            printf("[%.*s]", (int) it_sv.count, it_sv.data);
        }
        printf("\n");

        printf("Vector Head: %p\n", vec_header(vec_sv));
        vec_free(vec_sv);
    }

    int *vec_int = Vec(int);
    for (int i = 0; i < 10; i++) {
        vec_append(vec_int, (rand() % 100));
    }

    int removed = vec_remove(vec_int, 5);
    printf("Removed: %d\n", removed);

    {
        int it = 0;
        vec_for_each(vec_int, it) {
            printf("%2d ", it);
        }
        printf("\n");
    }

    printf("First: %d\n", vec_int[0]);
    printf("Last: %d\n", vec_int[vec_length(vec_int) - 1]);

    vec_insert(vec_int, 5, (int) 4);

    {
        int it = 0;
        vec_for_each(vec_int,  it) {
            printf("%2d ", it);
        }
        printf("\n");
    }

    printf("Max: %d\n", max(vec_int[0], vec_int[1], vec_int[2]));
    printf("Min: %d\n", min(vec_int[0], vec_int[1], vec_int[2]));
    printf("Vec Max: %d\n", vec_max(vec_int));
    printf("Vec Min: %d\n", vec_min(vec_int));

    {
        int it = 0;
        vec_for_each(vec_int, it) {
            printf("%2d ", it);
        }
        printf("\n");
    }

    vec_reverse(vec_int);
    printf("Reversed\n");
    {
        int it = 0;
        vec_for_each(vec_int, it) {
            printf("%2d ", it);
        }
        printf("\n");
    }

    vec_sort(vec_int, cmp);
    {
        int it = 0;
        vec_for_each(vec_int, it) {
            printf("%2d ", it);
        }
        printf("\n");
    }

    int a = vec_find(vec_int, 11);
    if (a == -1) {
        printf("Not Found\n");
    } else {
        printf("Found %d At: %d\n", vec_int[a], a);
    }

    vec_clear(vec_int);
    printf("Vec Cleared\n");
    printf("Vec Length: %zu\n", vec_length(vec_int));
    printf("Vec Capacity: %zu\n", vec_capacity(vec_int));

    vec_free(vec_int);

	{
		int **matrix = Vec(int*);
		vec_append(matrix, Vec(int));
		vec_append(matrix, Vec(int));
		vec_append(matrix, Vec(int));

		{ int *it = NULL;
		vec_for_each(matrix, it) {
			for (int j = 0; j < 3; j++) {
				vec_append(it, (i * 3 + j) + 1);
			}
		}}


		{ int *it = NULL;
		vec_for_each(matrix, it) {
			int item = 0;
			vec_for_each(it, item) {
				printf("%d ", item);
			}
			printf("\n");
		}}

		{ int *it = NULL;
		vec_for_each(matrix, it) {
			vec_free(it);
		}
		vec_free(matrix); }

		int *test = Vec(int);
		for (int i = 0; i < 10; i++) {
			vec_append(test, i);
		}

		vec_for_each_test(test) {
			printf("%2d", it);
		}}
		printf("\n");

		vec_free(test);
	}

	{
		printf("This should just work\n");
		Nob_String_View *vec_sv = NULL;
		vec_append(vec_sv, nob_sv_from_cstr("Hello"));
		vec_append(vec_sv, nob_sv_from_cstr(" "));
		vec_append(vec_sv, nob_sv_from_cstr("World"));

		for (size_t i = 0; i < vec_length(vec_sv); i++) {
			printf("%s", vec_sv[i].data);
		}
		printf("\n");
		vec_free(vec_sv);
	}

    return 0;
}
