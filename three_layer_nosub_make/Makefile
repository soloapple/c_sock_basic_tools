subdirs := $(shell find . -maxdepth 2 -type d)
subdirs := $(basename $(patsubst ./%, %, $(subdirs)))

DIR=.

define make_subdir
	@for subdir in $(subdirs); do \
		echo "cd $(DIR)/$$subdir";\
		(cd $(DIR)/$$subdir && make $@)\
	done;
endef

all:
	@echo "make all"
	@echo $(subdirs)	
	$(call make_subdir)

clean:
	@echo "make clean"
	@echo $(subdirs)
	$(call make_subdir,$@)
