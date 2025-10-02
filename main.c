#include <stdio.h>
#include <utmpx.h>

int main() {
	printf("Hello, World!\n");

	struct utmpx *data;
	data = getutxent();

	if (data == NULL) {
		printf("getutxent: returned nothing!\n");
		return 1;
	} else {
		printf("yeee we ballin\n");
	}

	// whoa, this is worthless (so far)
	while (data != NULL) {
		printf("%.*hd " , (int)(sizeof data->ut_type), data->ut_type);
		printf("%.*d " , (int)(sizeof data->ut_pid), data->ut_pid);
		printf("%.*s " , (int)(sizeof data->ut_line), data->ut_line);
		printf("%.*s " , (int)(sizeof data->ut_id), data->ut_id);
		printf("%.*s " , (int)(sizeof data->ut_user), data->ut_user);
		printf("%.*d\n" , (int)(sizeof data->ut_session), data->ut_session);

		data = getutxent();
	}
	return 0;
}