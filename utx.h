// Submodule containing utmpx-related wrapper functions
#ifndef UTX_H
#define UTX_H

// C
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
// POSIX
#include <unistd.h>
#include <sys/stat.h>
#include <utmpx.h>

// Size of a single utmpx struct
#define UTMPX_SIZE	sizeof(struct utmpx)
// Size of utmpx's ut_user field
#define UT_USER_SIZE	sizeof(((struct utmpx*)0)->ut_user)

// Remove user entries from an utmpx file
//
// `file`: A utmpx-compatible file opened as `r+` or `rb+`. Any other mode will fail.
// `user`: String of the username to be filtered out. Should be `UT_USER_SIZE` long.
int remove_entries(FILE* file,	const char* user);

#endif
