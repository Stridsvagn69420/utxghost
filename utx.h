// Submodule containing utmpx-related wrapper functions
#ifndef UTX_H
#define UTX_H

// C
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// POSIX
#include <unistd.h>
#include <utmpx.h>
#include <sys/stat.h>

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
	STAT_ERROR
} UtxStatus;

// Remove user entries from an utmpx file
//
// `file`: A utmpx-compatible file opened as `r+` or `rb+`. Any other mode will fail.
// `user`: String of the username to be filtered out. Should be `UT_USER_SIZE` long.
UtxStatus remove_entries(FILE* file, const char* user);

// Remove user entries from an utmpx file
//
// `path`: The path to an utmpx-compatible file.
// `user`: String of the username to be filtered out. Should be `UT_USER_SIZE` long.
UtxStatus remove_entries_path(const char* path, const char* user);

#endif