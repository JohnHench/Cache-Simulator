CC = clang
CFLAGS = -Wall -Wextra -Werror -pedantic
FORMAT_TOOL = clang-format
FORMAT_FLAGS = -i -style=file

SRC = cache.c cacher.c
OBJ = $(SRC:.c=.o)

all: cacher

cacher: $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

format:
	$(FORMAT_TOOL) $(FORMAT_FLAGS) $(SRC) *.h

clean:
	rm -f $(OBJ) cacher
	