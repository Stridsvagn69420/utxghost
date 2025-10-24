// C Standard
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
// POSIX
#include <unistd.h>

// utxghost
#include "utx/remove_entries.h"
#include "cli/flags.h"

int main(int argc, char* argv[]) {
	// Get username
	char user[UT_USER_SIZE] = {0};
	getlogin_r(user, UT_USER_SIZE);

	// Get command-line config
	Fools fools = { false, false, false};
	getflags(argc, argv, &fools, user, UT_USER_SIZE);

	// Print config
	printf("help: %i  version: %i  daemon: %i\n", fools.help, fools.version, fools.daemon);
	printf("Username: %s\n", user);

	// Interate over non-option arguments
	for (int i = optind; i < argc; i++) {
		printf("Args: %s\n", argv[i]);
	}
	return EXIT_SUCCESS;
}