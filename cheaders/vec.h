/* STB-style vector implementation
 *
 * Must be compiler with GCC as it uses the typeof() function which is a GCC
 * extension.
 */
#ifndef VEC_H_
#define VEC_H_

#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

typedef struct {
    void *(*alloc)(size_t bytes, void *context);
    void *(*free)(size_t bytes, void *ptr, void *context);
    void *context;
} Allocator;

typedef struct {
    size_t length;
    size_t capacity;
    size_t padding;
    Allocator* a;
} Vec_Header;

#define ARRAY_INITIAL_CAPACITY 16

void *vec_init(size_t item_size, size_t capacity, Allocator *a);
void *vec_ensure_capacity(void *a, size_t item_count, size_t item_size);
void vec_free(void *a);

#define Vec(T, a) (T *) vec_init(sizeof(T), ARRAY_INITIAL_CAPACITY, a)
#define vec_header(a) ((Vec_Header *)(a) - 1)
#define vec_length(a) (vec_header(a)->length)
#define vec_capacity(a) (vec_header(a)->capacity)

#define vec_append(a, v) ( \
    (a) = vec_ensure_capacity(a, 1, sizeof(v)), \
    (a)[vec_header(a)->length] = (v), \
    &(a)[vec_header(a)->length++]) \

#define vec_insert(a, i, v) ({ \
    (a) = vec_ensure_capacity(a, 1, sizeof(v)); \
    memmove((a) + (i - 1) + 1, (a) + (i - 1), (vec_header(a)->length - (i)) * sizeof(*(a))); \
    (a)[i - 1] = (v); \
    vec_header(a)->length += 1; \
})

#define vec_remove(a, i) ({ \
    Vec_Header* header = vec_header(a); \
    typeof(*(a)) removed_value = (a)[i - 1]; \
    memmove((a) + (i - 1), (a) + (i - 1) + 1, (header->length - (i)) * sizeof(*(a))); \
    header->length -= 1; \
    removed_value; \
})

#define vec_pop_back(a) ({ \
    typeof(*(a)) removed_value = (a)[vec_header(a)->length - 1]; \
    vec_header(a)->length -= 1; \
    removed_value; \
})

#define vec_clear(a) ({ \
    vec_header(a)->length = 0; \
})

#define vec_reserve(a, n) ({ \
    (a) = vec_ensure_capacity(a, n, sizeof(*(a))); \
})

#define vec_for_each(a, v) \
    for (size_t i = 0; i < vec_header(a)->length && ((v) = (a)[i], 1); ++i)

#define vec_for_each_test(a) \
	{ \
		typeof(*(a)) it; \
		vec_for_each(a, it)

#define vec_max(a) ({ \
    typeof(*(a)) max = (a)[0]; \
    for (size_t i = 1; i < vec_header(a)->length; ++i) { \
        if ((a)[i] > max) { \
            max = (a)[i]; \
        } \
    } \
    max; \
})

#define vec_min(a) ({ \
    typeof(*(a)) min = (a)[0]; \
    for (size_t i = 1; i < vec_header(a)->length; ++i) { \
        if ((a)[i] < min) { \
            min = (a)[i]; \
        } \
    } \
    min; \
})

#define vec_reverse(a) ({ \
    size_t length = vec_header(a)->length; \
    for (size_t i = 0; i < length / 2; ++i) { \
        typeof(*(a)) tmp = (a)[i]; \
        (a)[i] = (a)[length - i - 1]; \
        (a)[length - i - 1] = tmp; \
    } \
})

#define vec_sort(a, cmp) ({ \
    qsort((a), vec_header(a)->length, sizeof(*(a)), cmp); \
})

#define vec_find(a, v) ({ \
    bool found = false; \
    size_t low = 0; \
    size_t high = vec_header(a)->length; \
    size_t mid = 0; \
    while (low < high) { \
        mid = low + (high - low) / 2; \
        if ((a)[mid] == (v)) { \
            found = (a) + mid; \
            break; \
        } else if ((a)[mid] < (v)) { \
            low = mid + 1; \
        } else { \
            high = mid; \
        } \
    } \
    if (!found) { \
        mid = -1; \
    } \
    mid; \
})

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


#ifdef VEC_IMPLEMENTATION

#ifndef CUSTOM_ALLOCATOR
    void *my_alloc(size_t bytes, void *context) {
        (void)context;
        return malloc(bytes);
    }

    void *my_free(size_t bytes, void *ptr, void *context) {
        (void)ptr;
        (void)context;
        free(ptr);
        return NULL;
    }
    Allocator my_allocator = {my_alloc, my_free, 0};
#endif

void *vec_init(size_t item_size, size_t capacity, Allocator *a) {
    size_t header_size = item_size * capacity + sizeof(Vec_Header);
    size_t vec_size = item_size * capacity;
    size_t total_size = header_size + vec_size;

    void *ptr = a->alloc(total_size, a->context);

    if (ptr) {
        Vec_Header *h = (Vec_Header *)ptr;
        h->capacity = capacity;
        h->length = 0;
        h->a = a;
        void *arr_ptr = h + 1;
        return arr_ptr;
    }

    return NULL;
}

void *vec_ensure_capacity(void *a, size_t item_count, size_t item_size) {
    Vec_Header *h = vec_header(a);
    size_t desired_capacity = h->length + item_count;

    if (h->capacity < desired_capacity) {
        size_t new_capacity = h->capacity * 2;
        while (new_capacity < desired_capacity) {
            new_capacity *= 2;
        }

        size_t new_size = sizeof(Vec_Header) + new_capacity * item_size;
        Vec_Header *new_h = h->a->alloc(new_size, h->a->context);
        assert(new_h != NULL && "Failed to allocate memory");

        if (new_h) {
            size_t old_size = sizeof(*h) + h->length * item_size;
            memcpy(new_h, h, old_size);

            if (h->a->free) {
                h->a->free(old_size, h, h->a->context);
            }

            new_h->capacity = new_capacity;
            h = new_h + 1;
        } else {
            h = 0;
        }
    } else { h += 1; }

    return h;
}

void vec_free(void *a) {
    Vec_Header *h = vec_header(a);
    size_t size = sizeof(Vec_Header) + h->capacity * h->padding;
    h->a->free(size, h, h->a->context);
}
#endif // VEC_IMPLEMENTATION

#endif // VEC_H_
