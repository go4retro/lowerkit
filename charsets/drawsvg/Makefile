TARGET = drawsvg
LIBS = -lm
CC = gcc
CFLAGS = -g -Wall

.PHONY: default all clean create

default: $(TARGET) create
all: default

FONT_ROMS = $(wildcard ../mkroms/*.bin)
FONT_ROMS += $(wildcard ../basic/*.xtr.bin)

FILES = $(filter %.svg,$(FONT_ROMS:.bin=.svg))
OBJS = $(patsubst %.c, %.o, $(wildcard *.c))
HDRS = $(wildcard *.h)

create: $(TARGET) $(FILES)

%.svg: %.bin $(TARGET)
	./$(TARGET) $< > $(notdir $@)

%.o: %.c $(HDRS)
	$(CC) $(CFLAGS) -c $< -o $@

.PRECIOUS: $(TARGET) $(OBJS)

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -Wall $(LIBS) -o $@

clean:
	-rm -f *.o
	-rm -f $(TARGET)
	-rm -f *.svg

