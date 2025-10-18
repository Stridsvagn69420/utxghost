#include "utx.h"

// TODO: Return an enum member instead of just 1 and 0 for easier error handling.
int remove_entries(FILE* file, const char* user) {
	// Get and check file size
	struct stat ut_stat;
	int filedesc = fileno(file);
	fstat(filedesc, &ut_stat);

	long utxsize = ut_stat.st_size;
	if (utxsize % UTMPX_SIZE != 0) {
		// ERR: file is probably not a utmpx-compatible file (size does not align)
		return 1;
	}
	if (utxsize == 0) {
		// ERR: file is empty (not an actual error)
		return 0;
	}

	// Allocate space
	struct utmpx* utx_arr = malloc(utxsize);
	if (!utx_arr) {
		// ERR: malloc error
		return 1;
	}

	// Read file
	long read_n = 0;
	struct utmpx utx; // TODO: can probably be skipped
	while (fread(&utx, UTMPX_SIZE, 1, file) == 1) {
		memcpy(&utx_arr[read_n], &utx, UTMPX_SIZE);
		read_n++;
	}

	// Check for read errors
	long utx_n = utxsize / UTMPX_SIZE;
	if (ferror(file) || utx_n != read_n) {
		// ERR: read error occured
		printf("Error: %s\n", strerror(errno));
		printf("n: %li (expected), %li (actual)\n", utx_n, read_n);
		free(utx_arr);
		return 1;
	}

	// Filter out entries
	rewind(file);
	long write_n = 0;
	for (unsigned int i = 0; i < read_n; i++) {
		// Skip if name matches
		struct utmpx utx_curr = utx_arr[i];
		if (strncmp(utx_curr.ut_user, user, UT_USER_SIZE) == 0) {
			continue;
		} else {
			write_n++;
		}

		// Attempt to write
		fwrite(&utx_curr, UTMPX_SIZE, 1, file);
		if (ferror(file)) {
			// ERR: write error occured
			printf("Write error: %s\n", strerror(errno));
		}
	}

	// Truncate excess space
	free(utx_arr);
	long newsize = UTMPX_SIZE * (read_n - write_n);
	if (ftruncate(filedesc, newsize) != 0) {
		// ERR: could not truncate
		return 1;
	}
	return 0;
}
