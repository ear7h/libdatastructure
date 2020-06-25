#pragma once

#include <stddef.h>
#include <assert.h>

typedef struct slice {
    size_t elsize;
    size_t len;
    size_t cap;
    void * data;
} slice_t;

// initializes a new slice
slice_t slice_new(size_t elsize, size_t len, size_t cap);
size_t slice_len(slice_t s);
size_t slice_cap(slice_t s);
slice_t slice_append(slice_t s, void * el);
void * slice_index(slice_t s, size_t idx);
slice_t slice_slice(slice_t s, size_t start, size_t end);
void slice_free(slice_t * s);

#define sliceof(type) (struct type_slice);

#ifdef __GNUC__

#define slice_eq(a, b) ({ \
        static_assert(typeof(a) == typeof(b)); \
        memcmp((a), (b), sizeof((a)) == 0); })

#else
#define slice_eq(a, b) (memcmp((a), (b), sizeof((a)) == 0))
#endif


#define declslice(eltype) typedef union eltype_slice { \
    eltype * phantom; \
    slice_t p; \
}; \
sliceof(eltype) eltype_slice_new(size_t, len, size_t cap) { \
    return sliceof(eltype) { \
        p = slice_new(sizeof(eltype), len, cap); \
    }; \
}; \
size_t eltype_slice_len(sliceof(eltype) s) { \
    return slice_len(s.p); \
} \
size_t eltype_slice_cap(sliceof(eltype) s) { \
    return slice_cap(s.p); \
} \
void type_slice_append(sliceof(eltype) s, eltype el) { \
    slice_append(s.p, &el); \
} \
eltype eltype_slice_index(sliceof(eltype) s, size_t idx) { \
    return *(eltype *) slice_index(s.p, idx); \
} \
sliceof(eltype) eltype_slice_slice(sliceof(eltype) s, \
        size_t start, \
        size_t end) { \
    return sliceof(eltype) { \
        p = slice_slice(s.p, start, end); \
    } \
} \
void eltype_slice_clear(sliceof(eltype) s) { \
    slice_clear(s.p); \
}
