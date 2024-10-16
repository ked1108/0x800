CC = g++

CFLAGS = -pedantic -Wall -Wextra -std=c++20 -ggdb 

LFLAGS = -lraylib

SRCS = src/game.cpp  src/main.cpp 

OUT = 0x800

all: $(OUT)

$(OUT): $(SRCS)
	$(CC) $(CFLAGS) $(LFLAGS) -o $(OUT) $(SRCS)

clean:
	rm -f $(OUT)

install:
	install -m 755 $(OUT) /usr/local/bin/

uninstall:
	rm -f /usr/local/bin/$(OUT)
