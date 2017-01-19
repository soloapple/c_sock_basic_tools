.PHONY:all

CC=gcc
CFLAGS=-pg -ggdb -Wall
LIB_SRC=xutils.c

all: grap_raw_link_pkg icmp_raw_grap net_raw_data_passer

grap_raw_link_pkg:
	$(CC) grap_raw_link_pkg.c $(LIB_SRC) $(CFLAGS) -o $@
	
icmp_raw_grap:
	$(CC) icmp_raw_grap.c $(LIB_SRC) $(CFLAGS) -o $@

net_raw_data_passer:
	$(CC) net_raw_data_passer.c $(LIB_SRC) $(CFLAGS) -o $@

clean:
	rm -rf grap_raw_link_pkg icmp_raw_grap net_raw_data_passer
	rm -rf a.out *.o 
