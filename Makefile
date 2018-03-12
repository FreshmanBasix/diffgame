CC=gcc

SDL_FLAGS=`sdl2-config --cflags --libs` -lSDL2_image
CFLAGS=-Wall

TARGET=diffgame
MNT_DIR=.
SRCS=$(wildcard $(MNT_DIR)/src/*.c)
OBJS=$(SRCS:.c=.o)

.PHONY: clean run all

all: $(OBJS)
	$(CC) -o $(TARGET) $(OBJS) $(CFLAGS) $(SDL_FLAGS)
	@rm $(OBJS)

clean:
	@rm $(OBJS)
	@rm diffgame

run: all
	$(BIN) &

build_dir:
	@mkdir -p $(MNT_DIR)/build

.c.o: build_dir
	$(CC) -c $(CFLAGS) $(SDL_FLAGS) $< -o $@
