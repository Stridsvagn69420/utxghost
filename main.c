// C Standard
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
// POSIX
#include <unistd.h>

// utxghost
#include "utx.h"

int main(int argc, char* argv[]) {
	// Read username
	char username[UT_USER_SIZE];
	if (getlogin_r(username, UT_USER_SIZE)) {
		printf("(Phasmo gameplay) What is your name???\n");
		return EXIT_FAILURE;
	}
	printf("Hello, %s!\n", username);

	// Check for file
	if (argc < 2) {
		printf("No file provided!\n");
		return EXIT_FAILURE;
	}

	// Open file
	FILE* fp = fopen(argv[1], "r+b");
	if (!fp) {
		printf("Error: %s\n", strerror(errno));
		return EXIT_FAILURE;
	}

	// Remove entries
	if (remove_entries(fp, username)) {
		printf("An error occured while trying to remove your entries :(\n");
		return EXIT_FAILURE;
	}

	// Close file and exit
	printf("Done!\n");
	fclose(fp);
	return EXIT_SUCCESS;
}