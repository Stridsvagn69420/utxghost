#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>
#include <utmpx.h>

const unsigned long utxsize = sizeof(struct utmpx);
const unsigned long namesize = sizeof(((struct utmpx*)0)->ut_user);

// TODO: Use two different fopen()s where one just reads (and errors on not found), and the other writes like it does now
// or make it a single call, but idk about portability there, because flags have to be modified and then apparently interrupts have to be checked as well (lol?)
// or just count how many bytes first, then rewind and copy it to malloc()'d memory

int main(int argc, char* argv[]) {
	// Read username
	char username[namesize];
	if (getlogin_r(username, namesize)) {
		printf("(Phasmo gameplay) What is your name???\n");
		return EXIT_FAILURE;
	}

	// Check for file
	if (argc < 2) {
		printf("No file provided!\n");
		return EXIT_FAILURE;
	}

	// Open file
	FILE* fp = fopen(argv[1], "ab+");
	if (!fp) {
		printf("Error: %s\n", strerror(errno));
		return EXIT_FAILURE;
	}

	// Get position and de-facto file size
	long pos = ftell(fp);
	if (pos % utxsize != 0) {
		printf("bad data or some error happened: %s\n", strerror(errno));
		fclose(fp);
		return EXIT_FAILURE;
	}

	// Exit if file is empty
	if (pos == 0) {
		printf("Nothing to read :)\n");
		fclose(fp);
		return EXIT_SUCCESS;
	}

	// Allocate space for data
	long utxn = pos / utxsize;
	struct utmpx** utxarrp = malloc(pos);
	if (utxarrp == NULL) {
		printf("Failed to allocate space D:\n");
		fclose(fp);
		return EXIT_FAILURE;
	}

	// Rewind to beginning and read
	rewind(fp);
	struct utmpx utxtmp; // can probably be skipped
	unsigned long count = 0;
	while (fread(&utxtmp, utxsize, 1, fp) == 1) {
		memcpy(utxarrp[count], &utxtmp, utxsize);
		count++;
	}

	// Check for read errors
	if (ferror(fp)) {
		printf("Error: %s\n", strerror(errno));
		printf("n: %li (expected), %li (actual)\n", utxn, count);
		free(utxarrp);
		fclose(fp);
		return EXIT_FAILURE;
	}

	// Filter out entries that match the username and write the rest
	rewind(fp);
	unsigned long removed = 0;
	for (unsigned int i = 0; i < utxn; i++) {
		struct utmpx* utxcurr = utxarrp[i];

		// Skip if name matches
		if (strcmp(utxcurr->ut_user, username) == 0) {
			removed++;
			continue;
		}

		// Attempt to write
		fwrite(utxcurr, utxsize, 1, fp);
		if (ferror(fp)) {
			printf("Write error: %s\n", strerror(errno));
		}
	}

	// Truncate excess space
	unsigned long newsize = pos - utxsize * removed;
	printf("Newsize: %li - Position: %li\n", newsize, ftell(fp));
	ftruncate(fileno(fp), ftello(fp));

	// Close file
	free(utxarrp);
	fclose(fp);
	return 0;
}