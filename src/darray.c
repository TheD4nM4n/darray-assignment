#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>

typedef struct {
    int *array;
    size_t size;
} darray;

/*
 * Create an empty darray object of size 0 and return a pointer to it. If the
 * creation should fail, return NULL.
 */
darray *da_create() {
    darray *result = (darray *)malloc(sizeof(darray));
    if (result == NULL) {
        printf("[ERROR] Array init failed.");
        return NULL;
    }

    result->size = 0;

    result->array = malloc(0 * sizeof(int));
    if (result->array == NULL) {
        free(result);
        return NULL;
    }

    return result;
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

    int *out = array->array[idx];
    return out;
}

/*
 * Increase the length of array by 1 and place value within the newly created
 * spot. If the append operation fails, return 0. Otherwise return 1. Return 0
 * also if the provided array pointer is null.
 */
int da_append(darray *array, int value) {
    int newSize = array->size;
    printf('%d', newSize);

    int *result = (int *)realloc(array->array, ((newSize + 1) * sizeof(int)));

    if (result) {
        array->array = result;
        array->size++;
    } else {
        printf("[ERROR] Reallocation failed.");
        return 0;
    }

    array->array[array->size] = value;
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
        free(array->array);
        free(array);
    }
}

int main(int argc, char **argv) {
    darray *array = da_create();
    
    if (array == NULL) {
        printf("aborted (trump wouldnt like that)");
        return 1;
    }

    for (int i=0; i<100; i++) {
        assert(da_append(array, i) == 1);
    }

    assert(da_size(array) == 100);

    for (int i=0; i<100; i++) {
        assert(*(da_get(array, i)) == i);
    }

    assert(da_get(array, 101) == NULL);

    da_delete(array);
}
