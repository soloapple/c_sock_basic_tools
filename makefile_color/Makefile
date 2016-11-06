CCCOLOR="\033[34m"
LINKCOLOR="\033[34;1m"
SRCCOLOR="\033[33m"
BINCOLOR="\033[37;1m"
MAKECOLOR="\033[32;1m"
ENDCOLOR="\033[0m"

OPTIMIZATION?=-O2

STD=-std=c99 -pedantic
WARN=-Wall -W
OPT=$(OPTIMIZATION)
DEBUG=-g -ggdb
CFLAGS=-m32

FINAL_CFLAGS=$(STD) $(WARN) $(OPT) $(DEBUG) $(CFLAGS) 

QUIET_CC = @printf '    %b %b\n' $(CCCOLOR)CC$(ENDCOLOR) $(SRCCOLOR)$@$(ENDCOLOR) 1>&2;
QUIET_LINK = @printf '    %b %b\n' $(LINKCOLOR)LINK$(ENDCOLOR) $(BINCOLOR)$@$(ENDCOLOR) 1>&2;

DEMO_SERVER_SRC = demo.c
DEMO_CLIENT_SRC = demo.c
	
DEMO_CC = $(QUIET_CC) $(CC) $(FINAL_CFLAGS)
DEMO_LD = $(QUIET_LINK) $(CC) $(FINAL_LDFLAGS)

DEMO_SERVER_NAME=server
DEMO_CLIENT_NAME=client

$(DEMO_SERVER_NAME): $(DEMO_SERVER_SRC)
	$(DEMO_CC) -o $@ $^ 

$(DEMO_CLIENT_NAME): $(DEMO_CLIENT_SRC)
	$(DEMO_LD) -o $@ $^ 


all: $(DEMO_SERVER_NAME) $(DEMO_CLIENT_NAME)
	@echo "Hint: It's a good idea to run 'make test' ;)" 

.PHONY:	all

clean:
	rm -rf server client
