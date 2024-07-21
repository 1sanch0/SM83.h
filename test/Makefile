CC = gcc

CFLAGS = -I../ -ggdb -std=c11 -Wall -Wextra -Werror -Wpedantic -Wshadow -Wpointer-arith -Wstrict-overflow=5 \
				 -Wswitch-default -Wswitch-enum -Wunreachable-code -Wconversion -Wcast-qual -Wcast-align \
				#  -fsanitize=address -fsanitize=undefined -fsanitize=leak \
	
all: test

.PHONY: test
test: libsm83.so
	python3 test.py

libsm83.so: ../SM83.h
	@echo '#define SM83_IMPLEMENTATION\n#include "SM83.h"' \
	| $(CC) $(CFLAGS) -x c - -shared -fPIC $^ -o $@
	
.PHONY: clean
clean:
	$(RM) libsm83.so
 