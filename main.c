#define _GNU_SOURCE

#include <stdio.h>
#include <unistd.h>
#include <utmpx.h>

int main() {
	char hostname[24];
	gethostname(hostname, 24);
	printf("Hello, %s@%s on %s!\n\n", getlogin(), hostname, ttyname(STDOUT_FILENO));

	// This only works with glibc, so basically Linux only.
	utmpxname(UTMPX_FILENAME);
	setutxent();
	struct utmpx *data;
	data = getutxent();

	if (data == NULL) {
		printf("getutxent: returned nothing!\n");
		return 1;
	}

	while (data != NULL) {
		printf("%.*d ", (int)(sizeof data->ut_pid), data->ut_pid);
		printf("%.*s ", (int)(sizeof data->ut_line), data->ut_line);
		printf("%.*s ", (int)(sizeof data->ut_id), data->ut_id);
		printf("%.*s\n", (int)(sizeof data->ut_user), data->ut_user);

		data = getutxent();
	}

	endutxent();
	return 0;
}