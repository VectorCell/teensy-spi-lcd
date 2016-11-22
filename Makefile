SHELL := /bin/bash
CSTD   := c99
CPPSTD := c++11

ifeq "$(CXX)" "g++"
	GCCVERSIONLT48 := $(shell expr `gcc -dumpversion` \< 4.8)
	ifeq "$(GCCVERSIONLT48)" "1"
		CPPSTD := c++0x
	endif
endif

all: main.hex main.elf

main.hex: main.cc
	cp main.cc lib/main.cpp
	cd lib ; make
	cp lib/main.hex main.hex

main.elf:
	$(CXX) -std=$(CPPSTD) -O0 -Wall main.cc -o main.elf -DTESTING_MODE

test: main.elf
	timeout -k 2 1 ./main.elf && echo "FINISHED NORMALLY" || echo "TERMINATED"

load: main.hex
	sudo ./teensy_loader_cli -v -mmcu=mk20dx256 -w main.hex

clean:
	rm -f main.hex
	rm -f main.elf

purge: clean
	cd lib ; make clean
