#include <stdlib.h>
#include <stdio.h>
#include <dlfcn.h>
#ifdef __linux__
#include <syslog.h>
#endif

int main() {

	int res = -1;
	int (*get_parameter)();
	int *n3lib;

	setlogmask (LOG_UPTO (LOG_NOTICE));
	openlog ("n3-spectrum", LOG_CONS | LOG_PID | LOG_NDELAY, LOG_LOCAL1);
	syslog (LOG_NOTICE, "testing...");
	n3lib = dlopen("/usr/lib/libn3.so", RTLD_LAZY);
	if(n3lib != NULL){
		*(void **)(&get_parameter) = dlsym(n3lib, "get_parameter");

		if(!get_parameter){
			syslog (LOG_NOTICE, "get_parameter function not found");
			dlclose(n3lib);
			return -1;
		}
		int type = get_parameter();
		syslog (LOG_NOTICE, "get_parameter: get sensor type: %d", type);
		if(type == -1) {
			return -1;
		}

		if(type == 10) {
			res = 0;
		} else {
			res = 0;
		}
	} else {
		syslog (LOG_NOTICE, "failed to open n3lib.so");
	}

	if(n3lib != NULL) {
		dlclose(n3lib);
	}
	closelog();

	return res;
}
