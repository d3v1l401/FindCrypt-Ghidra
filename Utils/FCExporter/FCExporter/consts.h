#pragma once
#define IS_LITTLE_ENDIAN

#if defined(__GNUC__) || defined(__MWERKS__)
#define WORD64_AVAILABLE
typedef unsigned long long word64;
typedef unsigned long word32;
typedef unsigned char byte;
#define W64LIT(x) x##LL
#elif defined(_MSC_VER) || defined(__BCPLUSPLUS__)
#define WORD64_AVAILABLE
typedef unsigned __int64 word64;
typedef unsigned __int32 word32;
typedef unsigned __int8 byte;
#define W64LIT(x) x##ui64
#endif

struct array_info_t
{
	const void *array;
	size_t size;
	size_t size_elem;
	const char *name;
	const char *algorithm;
};

extern const array_info_t non_sparse_consts[];
extern const array_info_t sparse_consts[];

#define ARR(x)  x, sizeof(x), sizeof(x[0]), #x

