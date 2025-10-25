#include "sysfiles.h"

#ifdef __linux__
	const int sysfilesc = 2;
	const char* sysfilesv[] = {
		"/var/run/utmp",
		"/var/log/wtmp"
	};
#elif (__NetBSD__) || (__DragonFly__)
	const int sysfilesc = 2;
	const char* sysfilesv[] = {
		"/var/run/utmpx",
		"/var/log/lastlogx"
	};
#elif __FreeBSD__
	const int sysfilesc = 2;
	const char* sysfilesv[] = {
		"/var/run/utx.active",
		"/var/log/utx.lastlogin"
	};
#else
	#error Your OS is not supported
#endif