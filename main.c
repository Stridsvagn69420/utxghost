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

// TODO: The previous main method, it will get replaced though.
int simplemain(int argc, char* argv[]) {
	// Read username or use argument
	char username[UT_USER_SIZE];
	char* name;
	if (argc < 3 ) {
		if (getlogin_r(username, UT_USER_SIZE)) {
			printf("(Phasmo gameplay) What is your name???\n");
			return EXIT_FAILURE;
		}
		name = username;
	} else {
		name = argv[2];
	}

	// Check for file
	if (argc < 2) {
		printf("No file provided!\n");
		return EXIT_FAILURE;
	}

	// Remove entries
	if (remove_entries_path(argv[1], name)) {
		printf("An error occured while trying to remove your entries :(\n");
		printf("Error: %s\n", strerror(errno));
		return EXIT_FAILURE;
	}

	// Close file and exit
	printf("Done!\n");
	return EXIT_SUCCESS;
}

int main(int argc, char* argv[]) {
	return simplemain(argc, argv);
}