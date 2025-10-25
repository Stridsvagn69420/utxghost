#include "version.h"

// TODO: Try to automate this (CMake, compile-time env, macros)
#define APP_NAME "utxghost"
#define APP_VER_MAJOR 0
#define APP_VER_MINOR 1
#define APP_VER_PATCH 0

int print_version(void) {
	printf("%s v%i.%i.%i\n", APP_NAME, APP_VER_MAJOR, APP_VER_MINOR, APP_VER_PATCH);
	return EXIT_SUCCESS;
}