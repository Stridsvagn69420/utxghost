// C Standard Library
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
// POSIX Library
#include <unistd.h>
#include <sys/stat.h>
#include <utmpx.h>

const unsigned long utmpx_size = sizeof(struct utmpx);
const unsigned long ut_user_size = sizeof(((struct utmpx*)0)->ut_user);

// TODO: Description, also move this to a separate file, also also return an enum member instead of just 1 and 0 for easier error handling. 
int remove_entries(FILE* file, const char* user) {
	// Get and check file size
	struct stat ut_stat;
	int filedesc = fileno(file);
	fstat(filedesc, &ut_stat);

	long utxsize = ut_stat.st_size;
	if (utxsize % utmpx_size != 0) {
		// ERR: file is probably not a utmpx-compatible file (size does not align)
		return 1;
	}
	if (utxsize == 0) {
		// ERR: file is empty (not an actual error)
		return 0;
	}

	// Allocate space
	struct utmpx** utx_arr = malloc(utxsize);
	if (!utx_arr) {
		// ERR: malloc error
		return 1;
	}

	// Read file
	long read_n = 0;
	struct utmpx utx; // TODO: can probably be skipped
	while (fread(&utx, utmpx_size, 1, file) == 1) {
		memcpy(utx_arr[read_n], &utx, utmpx_size);
		read_n++;
	}

	// Check for read errors
	long utx_n = utxsize / utmpx_size;
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
		struct utmpx* utx_curr = utx_arr[i];
		if (strncmp(utx_curr->ut_user, user, ut_user_size) == 0) {
			continue;
		} else {
			write_n++;
		}

		// Attempt to write
		fwrite(utx_curr, utmpx_size, 1, file);
		if (ferror(file)) {
			// ERR: write error occured
			printf("Write error: %s\n", strerror(errno));
		}
	}

	// Truncate excess space
	free(utx_arr);
	long newsize = utmpx_size * (read_n - write_n);
	if (ftruncate(filedesc, newsize) != 0) {
		// ERR: could not truncate
		return 1;
	}
	return 0;
}

int main(int argc, char* argv[]) {
	// Read username
	char username[ut_user_size];
	if (getlogin_r(username, ut_user_size)) {
		printf("(Phasmo gameplay) What is your name???\n");
		return EXIT_FAILURE;
	}

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
	}

	// Close file
	fclose(fp);
	return 0;
}