#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>

typedef struct {
    int *data;
    size_t size;
} darray;

/*
 * Create an empty darray object of size 0 and return a pointer to it. If the
 * creation should fail, return NULL.
 */
darray *da_create() {
    darray *array = (darray *)malloc(sizeof(darray));
    if (array == NULL) {
        printf("[ERROR] Array init failed.");
        return NULL;
    }

    array->size = 0;
    printf("%lu", array->size);
    fflush(stdout);

    array->data = malloc(sizeof(int));
    if (array->data == NULL) {
        free(array);
        return NULL;
    }

    return array;
}

/*
 * Access the element stored at index idx within the darray and return a
 * pointer to it. If the idx is out of range for the darray, return NULL
 * instead. If the provided array pointer is NULL, return NULL.
 */
int *da_get(darray *array, size_t idx) {
    if (array == NULL) {
        return NULL;
    }

    if (idx >= array->size) {
        return NULL;
    }

    int *out = &array->data[idx];
    return out;
}

/*
 * Increase the length of array by 1 and place value within the newly created
 * spot. If the append operation fails, return 0. Otherwise return 1. Return 0
 * also if the provided array pointer is null.
 */
int da_append(darray *array, int value) {

    size_t newSize = array->size + 1;
    array->size = newSize;

    int *result = (int *)realloc(array->data, array->size * sizeof(int));

    if (result) {
        array->data = result;
    } else {
        printf("[ERROR] Reallocation failed.");
        return 0;
    }

    array->data[array->size - 1] = value;
    return 1;
}

/*
 * Returns the size of the array. Note that this size should be the accessible
 * size (using get, for example), not the physical size of the allocation,
 * which may be larger. If array is NULL, return 0.
 */
size_t da_size(darray *array) {
    if (!array) {
        return 0;
    }
    return array->size;
}

/*
 * Free all the allocated memory associated with array. If array is NULL, do
 * nothing.
 */
void da_delete(darray *array) {
    if (array) {
        free(array->data);
        free(array);
    }
}
