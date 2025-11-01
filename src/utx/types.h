#ifndef UTX_TYPES_H
#define UTX_TYPES_H

// C Standard
#include <stdbool.h>
// POSIX
#include <utmpx.h>

// Size of a single utmpx struct
#define UTMPX_SIZE	sizeof(struct utmpx)
// Size of utmpx's ut_user field
#define UT_USER_SIZE	sizeof(((struct utmpx*)0)->ut_user)

typedef enum {
	// No error
	NONE,

	// File is empty (not an actual error)
	FILE_EMPTY,

	// File size does not equal a multiple of utmpx's size
	NOT_UTMPX,

	// malloc() failed to allocate space
	MALLOC_ERROR,

	// fread() failed. Error can be read via `errno`.
	READ_ERROR,

	// fwrite() failed. Error can be read via `errno`.
	WRITE_ERROR,

	// ftruncate() failed. Error can be read via `errno`.
	TRUNCATE_ERROR,

	// fopen() failed. Error can be read via `errno`.
	OPEN_ERROR,

	// fstat() failed. Error can be read via `errno`.
	STAT_ERROR,

	// futimes() failed. Error can be read via `errno`.
	UTIME_ERROR
} UtxStatus;

// Get string to print for a given UtxStatus
char* utxstring(UtxStatus status);

// Check if UtxStatus code is an error
bool utxiserr(UtxStatus status);

#endif