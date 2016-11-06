top_srcs=

subdirs := $(shell find . -maxdepth 1 -type d)
subdirs := $(basename $(patsubst ./%, %, $(subdirs)))

define make_subdir
	@for subdir in $(subdirs); do	\
		(cd $$subdir && make)		\
	done;
endef

define make_subdir_clean
	@for subdir in $(subdirs); do	\
		(cd $$subdir && make clean)	\
	done;
endef

all:
	$(call make_subdir)

clean:
	$(call make_subdir_clean)

