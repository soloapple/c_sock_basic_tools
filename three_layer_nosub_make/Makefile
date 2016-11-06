subdirs := $(shell find . -maxdepth 2 -type d)
subdirs := $(basename $(patsubst ./%, %, $(subdirs)))

define make_subdir
	@for subdir in $(subdirs); do \
		(cd $$subdir && make)\
	done;
endef

all:
	@echo $(subdirs)	
	$(call make_subdir)
