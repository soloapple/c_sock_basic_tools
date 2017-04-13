.PHONY:all

SRC = common.c
HDR = common.h
CC  = gcc
DST = test_mail rep_conf
CFLAGS = -Wall
	
all: $(DST)

test_mail: $(HDR)
	$(CC) read.c $(SRC) $(CFLAGS) -o test_mail

rep_conf: $(HDR)
	$(CC) rep_conf.c $(SRC) $(CFLAGS) -o rep_conf


clean:
	rm -rf $(DST)
