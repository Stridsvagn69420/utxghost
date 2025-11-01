#include "types.h"

char* utxstring(UtxStatus status) {
	switch (status) {
		case NONE:
			return "Success!";
		case FILE_EMPTY:
			return "Nothing to do :)";
		case NOT_UTMPX:
			return "File does not seem to be valid utmpx.";
		case MALLOC_ERROR:
			return "malloc() failed for some reason (you should honestly never see this o.o)";
		case READ_ERROR:
			return "Failed to read file!";
		case WRITE_ERROR:
			return "Failed to write file!";
		case TRUNCATE_ERROR:
			return "Failed to truncate file!";
		case OPEN_ERROR:
			return "Failed to open file!";
		case STAT_ERROR:
			return "Failed to get file metadata!";
		case UTIME_ERROR:
			return "Failed to set file times!";
		default:
			return "Unknown status";
	}
}

bool utxiserr(UtxStatus status) {
	switch (status) {
		case NONE:
		case FILE_EMPTY:
			return false;
		default:
			return true;
	}
}