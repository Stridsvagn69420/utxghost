// C Standard
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
// POSIX
#include <unistd.h>

// utxghost
#include "utx/sysfiles.h"
#include "utx/remove_entries.h"
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

	// Print username to be removed from files
	printf("User: %s\n", user);

	bool errd;
	// If optind is smaller than argc, there are non-option arguments left in argv.
	if (optind < argc) {
		errd = remove_entries_argv(optind, argc, (const char**) argv, user);
	} else {
		errd = remove_entries_argv(0, sysfilesc, sysfilesv, user);
	}
	return (errd) ? EXIT_FAILURE : EXIT_SUCCESS;
}