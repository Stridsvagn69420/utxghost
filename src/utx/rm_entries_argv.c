#include "rm_entries_argv.h"

bool rm_entries_argv(int offset, int argc, const char* argv[], char* user) {
	bool err_once = false;
	for (int i = offset; i < argc; i++) {
		// Print current iteration
		printf("[%s] Removing entries... ", argv[i]);

		// Actually do what it's supposed to do
		UtxStatus status = remove_entries_path(argv[i], user);

		// Print possible error
		if (utxiserr(status)) {
			printf("%s (%s)\n", utxstring(status), strerror(errno));
			err_once = true;
		} else {
			printf("%s\n", utxstring(status));
		}
	}
	return err_once;
}