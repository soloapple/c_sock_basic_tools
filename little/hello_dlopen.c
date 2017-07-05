/******************************************************************************
 *   Copyright (C), 2017, 360 Legendsec Co., Ltd.
 *   soloapple   2017年07月03日 02时26分44秒
 *
 *   
 *****************************************************************************/

#include <sys/types.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <dlfcn.h>

typedef struct {
	const char *module;
	int  (*GetValue)(char *pszVal);
	int   (*PrintfHello)();
} hello_ST_API;


int main(int argc, char **argv)
{
	hello_ST_API *hello;
	int i = 0;
	void *handle;
	char psValue[20] = {0};

	handle = dlopen("/revive/git/c_sock_basic_tools/little/hello.so", RTLD_LAZY);
	if (! handle) {
		printf("%s,%d, NULL == handle\n", __FUNCTION__, __LINE__);
		return -1;
	}
	dlerror();

	hello = dlsym(handle, "Hello");
	if (!hello) {
		printf("%s,%d, NULL == handle\n", __FUNCTION__, __LINE__);
		return -1;
	}

	if (hello && hello->PrintfHello)
		i = hello->PrintfHello();
	printf("%s, %d, i = %d\n", __FUNCTION__, __LINE__, i);
	if (hello && hello->GetValue)
		i = hello->GetValue(psValue);

	if (hello && hello->module)
	{
		printf("%s, %d, module = %s\n", __FUNCTION__, __LINE__, hello->module);
	}

	dlclose(handle);
	return 0;
}

