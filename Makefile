DESTDIR = /usr/local/bin

CC = gcc
CC_ARGS = -std=c99 -Wall -Werror -Wextra -Wpedantic -pedantic-errors -Wno-unknown-warning-option -Wno-stringop-overflow
CC_CMD = $(CC) $(CC_ARGS)

C_FILES = main.c args.c linked-list.c map.c

all: $(C_FILES)
	$(CC_CMD) -O3 $(C_FILES) -o uniq-lines
	strip uniq-lines

debug: $(C_FILES)
	$(CC_CMD) -gdwarf $(C_FILES) -o uniq-lines-debug

install: uniq-lines
	install -m 755 uniq-lines $(DESTDIR)

clean:
	rm uniq-lines; rm uniq-lines-debug
