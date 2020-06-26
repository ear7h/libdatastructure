#include <test/test.h>

#include <datastructure/slice.h>

#define RANGE(idx, arr) (size_t idx = 0; i < sizeof(arr)/sizeof(arr[0]); idx++)

void test_new(T * t) {
    typedef struct tcase {
		size_t elsize;
		size_t len;
		size_t cap;
	} tcase;

	tcase tcases[] = {
		{ // 0
			.elsize=sizeof(int),
			.len=10,
			.cap=10,
		},
		{ // 1
			.elsize=sizeof(int),
			.len=0,
			.cap=10,
		},
		{ // 1
			.elsize=sizeof(int),
			.len=0,
			.cap=0,
		},
	};

	for RANGE(i, tcases) {
		tcase tc = tcases[i];

		slice_t s = slice_new(tc.elsize, tc.len, tc.cap);

		test_assert(t, slice_len(s) == tc.len);
		test_assert(t, slice_cap(s) == tc.cap);

		for SLICE_RANGE(i, s) {
			test_assert(t, *(int *) slice_index(s, i) == 0);
		}

		slice_free(&s);
	}
}

DECL_TESTS(test_new);
