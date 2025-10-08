#include <stdio.h>
#include <utmpx.h>
#include <unistd.h>

int main() {
	// Hello World (exploring unistd.h)
	char hostname[24];
	gethostname(hostname, 24);
	printf("Hello, %s@%s on %s!\n\n", getlogin(), hostname, ttyname(STDOUT_FILENO));

	struct utmpx *data;
	data = getutxent();

	if (data == NULL) {
		printf("getutxent: returned nothing!\n");
		return 1;
	}

	// whoa, this is worthless (so far)
	while (data != NULL) {
		printf("%.*d ", (int)(sizeof data->ut_pid), data->ut_pid);
		printf("%.*s ", (int)(sizeof data->ut_line), data->ut_line);
		printf("%.*s ", (int)(sizeof data->ut_id), data->ut_id);
		printf("%.*s ", (int)(sizeof data->ut_user), data->ut_user);

		data = getutxent();
	}

	// Close and exit
	endutxent();
	return 0;
}