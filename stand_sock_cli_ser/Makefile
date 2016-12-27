.PHONY:all

CFLAGS=-ggdb -pg 
CC=g++

head_path=.
head_h=syshead.h
head_h_gch=$(head_h).gch

all:tcp_client tcp_server

tcp_client:$(head_path)/$(head_h_gch)
	$(CC) stand_tcp_client.c $(CFLAGS) -o $@

tcp_server:$(head_path)/$(head_h_gch)
	$(CC) stand_tcp_server.c $(CFLAGS) -o $@

$(head_h_gch):$(head_h)
	$(CC) $^

clean:
	rm -rf a.out *.o tcp_client tcp_server *.gch
