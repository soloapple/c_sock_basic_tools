.PHONY: all clean

COMM_HDRS = $(wildcard *.h)
COMM_SRCS = $(wildcard *.c)
COMMCC_SRCS = $(wildcard *.cc)
COMM_OBJS = $(patsubst %.c , %.o, $(COMM_SRCS)) 
COMM_OBJS += $(patsubst %.cc, %.o, $(COMMCC_SRCS)) 

BASENAME = /usr

CFLAGS	 = -Wall -pipe -I/usr/local/include \
		  -I../../common \
		  -DPATH_ERRLOG=\"/tmp/sqlsys_error_log\" \
		  -g

LDFLAGS = -L/lib64 -lmysqlclient -lpthread
SRC = 

CC = g++

BINS = err_log_to_file

all: $(BINS)

err_log_to_file: $(COMM_HDRS) $(COMM_OBJS)
	$(CC) $(SRC) $(LDFLAGS) $(COMM_OBJS) $(CFLAGS) -o $@

clean:
	-rm -f *.o $(BINS) *core* *.gch
