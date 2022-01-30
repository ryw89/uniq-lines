DESTDIR = /usr/local/bin
GCC_CMD = gcc -std=c99 -Wall -Werror -Wextra -Wpedantic -pedantic-errors
C_FILES = main.c args.c linked-list.c set.c

all: $(C_FILES)
	$(GCC_CMD) -O3 $(C_FILES) -o uniq-lines
	strip uniq-lines

debug: $(C_FILES)
	$(GCC_CMD) -gdwarf $(C_FILES) -o uniq-lines-debug

install: uniq-lines
	install -m 755 uniq-lines $(DESTDIR)

clean:
	rm uniq-lines; rm uniq-lines-debug
