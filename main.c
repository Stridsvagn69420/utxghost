#include <stdio.h>
#include <unistd.h>
#include <utmpx.h>

int main() {
	// Hello World (exploring unistd.h)
	char hostname[24];
	gethostname(hostname, 24);
	printf("Hello, %s@%s on %s!\n\n", getlogin(), hostname, ttyname(STDOUT_FILENO));

	// Note to self: either I'm stupid or those predefined functions are kind of dumb because I'll have to "fread() the data into the struct" anyway
	struct utmpx *data;
	data = getutxent();

	if (data == NULL) {
		printf("getutxent: returned nothing!\n");
		return 1;
	}

	// This also doesn't always output, or data is *very* delayed...
	while (data != NULL) {
		printf("%.*d ", (int)(sizeof data->ut_pid), data->ut_pid);
		printf("%.*s ", (int)(sizeof data->ut_line), data->ut_line);
		printf("%.*s ", (int)(sizeof data->ut_id), data->ut_id);
		printf("%.*s ", (int)(sizeof data->ut_user), data->ut_user);

		data = getutxent();
	}
	return 0;
}