#INCLUDES = -I../lib
bin_PROGRAMS = iproxy
iproxy_SOURCES = socket.c worker.c iproxy.c
iproxy_LDADD = ../lib/libsock.a 
iproxy_LDFLAGS = -L../dynamic_lib/ 
LIBS = -lhex_print -lpthread

