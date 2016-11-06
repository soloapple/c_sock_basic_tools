default:install

.DEFAULT:
	@echo $@
	$(MAKE) $@ -C layer2

install:
	@echo "+++++++++++++++++++++++++++++"
	@echo "layer 1 install"
	@echo "+++++++++++++++++++++++++++++"
	$(MAKE) $@ -C layer2

all:
	@echo "+++++++++++++++++++++++++++++"
	@echo "layer 1 all"
	@echo "+++++++++++++++++++++++++++++"
	$(MAKE) $@ -C layer2


