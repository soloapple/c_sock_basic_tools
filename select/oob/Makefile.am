#INCLUDES = -I../lib
bin_PROGRAMS = oob_client oob_server
oob_client_SOURCES = oob_client.c
oob_client_LDADD = ../lib/libsock.a 
oob_client_LDFLAGS = -L../dynamic_lib/ 
oob_server_SOURCES = oob_server.c
oob_server_LDADD = ../lib/libsock.a 
oob_server_LDFLAGS = -L../dynamic_lib/ 
LIBS = -lhex_print -lpthread

