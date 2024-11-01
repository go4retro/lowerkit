TARGET = mkroms
LIBS = -lm
CC = gcc
CFLAGS = -g -Wall

.PHONY: default all clean create

default: $(TARGET) create
all: default

FONT_FILES = $(wildcard ../*.bin)
FONT_FILES += $(wildcard ../*.xxx)

FILES = $(filter %.fnt.txt,$(FONT_FILES:.bin=.fnt.txt) $(FONT_FILES:.xxx=.fnt.txt))
OBJS = $(patsubst %.c, %.o, $(wildcard *.c))
HDRS = $(wildcard *.h)

create: $(TARGET) $(FILES)

%.fnt.txt: %.bin $(TARGET)
	./$(TARGET) $< $(notdir $(patsubst %.bin, %.fnt.bin, $<)) > $(notdir $@)

%.fnt.txt: %.xxx $(TARGET)
	./$(TARGET) $< $(notdir $(patsubst %.xxx, %.fnt.bin, $<)) > $(notdir $@)

%.o: %.c $(HDRS)
	$(CC) $(CFLAGS) -c $< -o $@

.PRECIOUS: $(TARGET) $(OBJS)

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -Wall $(LIBS) -o $@

clean:
	-rm -f *.o
	-rm -f $(TARGET)
	-rm -f *.fnt.txt
	-rm -f *.fnt.bin

