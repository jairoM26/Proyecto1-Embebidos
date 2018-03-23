SUBDIRS = lib src
File= gpio
exe= test

all: $(SUBDIRS)
	././src/main

$(SUBDIRS):
		$(MAKE) -C $@		

clean:
	
	rm ./lib/$(File).o ./lib/$(File).a ./src/$(exe)

.PHONY: $(SUBDIRS)