.PHONY:all

CC=gcc
CFLAGS=-pg -ggdb -Wall
SRC=icmp_raw_grap.c xutils.c

all: grap_raw_link_pkg icmp_raw_grap


grap_raw_link_pkg:
	$(CC) grap_raw_link_pkg.c $(CFLAGS) -o $@
	
icmp_raw_grap:
	$(CC) $(SRC) $(CFLAGS) -o $@

clean:
	rm -rf grap_raw_link_pkg icmp_raw_grap 
	rm -rf a.out *.o 
