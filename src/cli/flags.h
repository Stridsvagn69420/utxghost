#ifndef CLI_FLAGS_H
#define CLI_FLAGS_H

// C Standard
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
// GNU
#include <getopt.h>

// Short-option string for getopt()
extern const char shortopts[];
// Long-option array for getopt_long()
extern const struct option longopts[];

// Flag-booleans combined as a single datatype
typedef struct {
	bool help;
	bool version;
	bool daemon;
} Fools;

// Wrapper function around getopt_long()
void getflags(int argc, char* argv[], Fools* bools, char* user, size_t usersize);

#endif