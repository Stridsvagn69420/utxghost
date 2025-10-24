// Submodule containing utmpx-related wrapper functions
#ifndef UTX_REMOVE_ENTRIES_H
#define UTX_REMOVE_ENTRIES_H

// C
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// POSIX
#include <unistd.h>
#include <utmpx.h>
#include <sys/stat.h>
// utxghost
#include "types.h"

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