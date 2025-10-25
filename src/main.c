// C Standard
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <errno.h>
// POSIX
#include <unistd.h>

// utxghost
#include "utx/remove_entries.h"
#include "utx/sysfiles.h"
#include "cli/flags.h"
#include "cli/help.h"
#include "cli/version.h"

int main(int argc, char* argv[]) {
	// Get username
	char user[UT_USER_SIZE] = {0};
	getlogin_r(user, UT_USER_SIZE);

	// Get command-line config
	Fools fools = { false, false, false };
	getflags(argc, argv, &fools, user, UT_USER_SIZE);

	// Handle flag-booleans
	if (fools.help) {
		return print_help();
	} else if (fools.version) {
		return print_version();
	}
	// TODO: Implement daemon mode
	if (fools.daemon) {
		fprintf(stderr, "daemon mode is not implemented yet :(\n");
	}

	// Print username
	printf("User: %s\n", user);

	// Remove from files
	if ((argc - optind) < 1) {
		// TODO: Use system files
	} else {
		// TODO: Use command-line provided files
	}
	return EXIT_SUCCESS;
}