#include "flags.h"

// Option array for getopt_long() and its getopt() string
const struct option longopts[] = {
	{"version", no_argument, NULL, 'V'},
	{"help", no_argument, NULL, 'h'},
	{"user", required_argument, NULL, 'u'},
	{NULL, no_argument, NULL, 0}
};
const char shortopts[] = "Vhu:";

// Wrapper function around getopt_long()
void getflags(int argc, char* argv[], Fools* bools, char* user, size_t usersize) {
	opterr = false;
	int c;
	while ((c = getopt_long(argc, argv, shortopts, longopts, NULL)) != EOF) {
		switch (c) {
			case 'h':
				bools->help = true;
				break;
			case 'V':
				bools->version = true;
				break;
			case 'u':
				strncpy(user, optarg, usersize);
				break;
		}
	}
}