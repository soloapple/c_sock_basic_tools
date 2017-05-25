.SUFFIXES:
.SUFFIXES: .g .o

LIBS=gao.o

all: $(LIBS)

### this not works.
#%.o:%g    
#	@echo "in %.o:%g"

### this works.
%.o:%.g    
	@echo "in %.o:%.g"

### this works by SUFFIXES
#.g.o:    
#	@echo "in .g.o"
