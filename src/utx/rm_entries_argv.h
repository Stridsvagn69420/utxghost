#ifndef UTX_RM_ENTRIES_ARGV
#define UTX_RM_ENTRIES_ARGV

// C Standard
#include <string.h>
#include <errno.h>
// utxghost
#include "remove_entries.h"
#include "types.h"

// Wrapper around an array of paths to be worked on.
// Note that this is used for utxghost's one-shot mode
// and it's designed to directly encapsulate main() behaviour.
bool rm_entries_argv(int offset, int argc, const char* argv[], char* user);

#endif