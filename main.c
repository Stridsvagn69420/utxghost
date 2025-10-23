// C Standard
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
// POSIX
#include <unistd.h>
// GNU
#include <getopt.h>

// utxghost
#include "utx/remove_entries.h"

int main(int argc, char* argv[]) {
	// Set command-line options
	const char* shortopts = "Vhu:f:";
	static struct option cliopts[] = {
		{"version", no_argument, NULL, 'V'},
		{"help", no_argument, NULL, 'h'},
		{"user", required_argument, NULL, 'u'},
		{"file", required_argument, NULL, 'f'},
		//{"daemon", no_argument, NULL, 'd'},
		{NULL, no_argument, NULL, 0}
	};

	// Parse command-line options
	int c;
	while ((c = getopt_long(argc, argv, shortopts, cliopts, NULL)) != EOF) {
		printf("Opts: %d (%c)\n", c, (char) c);
	}
	return 0;
}