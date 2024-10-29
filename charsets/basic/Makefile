TARGET = parsebas
LIBS = -lm
CC = gcc
CFLAGS = -g -Wall

.PHONY: default all clean parse

default: $(TARGET) parse
all: default

FILES = $(patsubst %.xtr, %.xtr.txt, $(wildcard *.xtr))
OBJS = $(patsubst %.c, %.o, $(wildcard *.c))
HDRS = $(wildcard *.h)

parse: $(TARGET) $(FILES)

%.xtr.txt: %.xtr $(TARGET)
	./$(TARGET) $< $<.bin > $@

%.o: %.c $(HDRS)
	$(CC) $(CFLAGS) -c $< -o $@

.PRECIOUS: $(TARGET) $(OBJS)

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -Wall $(LIBS) -o $@

clean:
	-rm -f *.o
	-rm -f $(TARGET)
	-rm -f *.xtr.txt
	-rm -f *.bin
