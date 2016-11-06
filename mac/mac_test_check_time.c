#include <stdlib.h>
#include <stdio.h>
#include <time.h>

unsigned long long gLatestTime = 0;

#define ERROR(...)\
do{\
	fprintf(stderr, "[ERROR  ]%s %s(Line %d): ",__FILE__,__FUNCTION__,__LINE__);\
    fprintf(stderr, __VA_ARGS__);\
}while(0) 

#define WARNING(...)\
do{\
	fprintf(stdout, "[WARNING]%s %s(Line %d): ",__FILE__,__FUNCTION__,__LINE__);	\
    fprintf(stdout, __VA_ARGS__);\
}while(0)

#define INFO(...) \
do{\
	fprintf(stdout, "[INFO  ]%s %s(Line %d): ",__FILE__,__FUNCTION__,__LINE__); \
	fprintf(stdout, __VA_ARGS__); \
}while(0) 

#define GET_TIME() \
do{\
	struct timeval tp;\
	gettimeofday(&tp, NULL);\
	gLatestTime = tp.tv_sec*1000000+tp.tv_usec;\
	fprintf(stdout, "Current time is: %s[%d], %s: %ld.%ld",\
		   	__FILE__, __LINE__, __func__, tp.tv_sec, tp.tv_usec);\
}while(0)

#define SHOW_TIME(...) \
do{\
	struct timeval tp;\
	gettimeofday(&tp, NULL);\
	unsigned long long now = tp.tv_sec*1000000+tp.tv_usec;\
	if(gLatestTime != 0) \
	{\
		fprintf(stdout, ">>>>>>>>>Used Time: %s[%d], %s: %ld.%ld, %llu ms ", \
				__FILE__, __LINE__, __func__, tp.tv_sec, tp.tv_usec, (now-gLatestTime)/1000);\
		fprintf(stdout, __VA_ARGS__);\
		fprintf(stdout, "\n");\
	}\
	gLatestTime = now;\
}while(0)    
	
#ifdef DEBUG    
#define DBG(...) \
do{ \
	fprintf(stdout, "[DEBUG  ]%s %s(Line %d): ",__FILE__,__FUNCTION__,__LINE__); \
	fprintf(stdout, __VA_ARGS__); \
}while(0)    
#else    
#define DBG(...)    
#endif

	int
main ( int argc, char *argv[] )
{
	GET_TIME();
	//sleep(1);
	GET_TIME();
	SHOW_TIME("1");
	return EXIT_SUCCESS;
}	
