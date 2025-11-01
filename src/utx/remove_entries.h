#ifndef UTX_REMOVE_ENTRIES_H
#define UTX_REMOVE_ENTRIES_H

// C
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
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
// `tv`: A `timeval` struct that will be set to the last non-removed entry's time.
UtxStatus remove_entries(FILE* file, const char* user, struct timeval* tv);

// Remove user entries from an utmpx file
//
// `path`: The path to an utmpx-compatible file.
// `user`: String of the username to be filtered out. Should be `UT_USER_SIZE` long.
UtxStatus remove_entries_path(const char* path, const char* user);

// Wrapper around an array of paths to be worked on.
// Note that this is used for utxghost's one-shot mode
// and it's designed to directly encapsulate main() behaviour.
//
// - `offset`: The offset when to start iterating (i.e. `optind` after `getopt()`)
// - `argc`: Length of argv
// - `argv`: char* array to be iterated over
// - `user`: Username to be removed
bool remove_entries_argv(int offset, int argc, const char* argv[], char* user);

#endif