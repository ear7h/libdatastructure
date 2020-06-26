#pragma once

#include <stddef.h>
#include <stdint.h>

typedef struct slice {
    size_t elsize;
    size_t len;
    size_t cap;
    void * data;
} slice_t;

// initializes a new slice
slice_t slice_new(size_t elsize, size_t len, size_t cap);

// get the length of a slice
size_t slice_len(slice_t s);

// get the capacity of a slice
size_t slice_cap(slice_t s);

// append items to the end of a slice
slice_t slice_append(slice_t s, void * el);

// get a pointer to the data at the specific index
void * slice_index(slice_t s, size_t idx);

// get a sub-slice of an exisiting slice
slice_t slice_slice(slice_t s, size_t start, size_t end);

// free data associated with a slice. It takes a pointer to clear
// the state of the slice object, preventing potential erroneous
// memory accesses.
void slice_free(slice_t * s);

#define SLICE_RANGE(idx, slc) (size_t idx = 0; idx < slc.len; idx++)

