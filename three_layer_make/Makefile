default:all

PWD=$(shell pwd)

.DEFAULT:
	$(MAKE) $@ -C layer1 M=$(PWD)
	$(MAKE) $@ -C rootdir
	
