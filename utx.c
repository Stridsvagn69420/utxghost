#include "utx.h"

#define UTX_OPEN_MODE "r+b"

UtxStatus remove_entries(FILE* file, const char* user) {
	// Get and check file size
	struct stat ut_stat;
	int filedesc = fileno(file);
	if(fstat(filedesc, &ut_stat)) {
		return STAT_ERROR;
	}

	// Check file size conditions
	long utxsize = ut_stat.st_size;
	if (utxsize % UTMPX_SIZE != 0) {
		return NOT_UTMPX;
	}
	if (utxsize == 0) {
		return FILE_EMPTY;
	}

	// Allocate space
	struct utmpx* utx_arr = malloc(utxsize);
	if (!utx_arr) {
		return MALLOC_ERROR;
	}

	// Read file
	long read_n = 0;
	while (fread(&utx_arr[read_n], UTMPX_SIZE, 1, file) == 1) {
		read_n++;
	}

	// Check for read errors
	long utx_n = utxsize / UTMPX_SIZE;
	if (ferror(file) || utx_n != read_n) {
		free(utx_arr);
		return READ_ERROR;
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
			free(utx_arr);
			return WRITE_ERROR;
		}
	}

	// Truncate excess space
	free(utx_arr);
	long newsize = UTMPX_SIZE * (read_n - write_n);
	if (ftruncate(filedesc, newsize)) {
		return TRUNCATE_ERROR;
	}
	return NONE;
}

UtxStatus remove_entries_path(const char* path, const char* user) {
	FILE* fp = fopen(path, UTX_OPEN_MODE);
	if (!fp) {
		return OPEN_ERROR;
	}

	UtxStatus status = remove_entries(fp, user);
	fclose(fp);
	return status;
}