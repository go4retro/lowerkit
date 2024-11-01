TARGET = parseroms
LIBS = -lm
CC = gcc
CFLAGS = -g -Wall

.PHONY: default all clean create

default: $(TARGET)
all: default

FONT_FILES = $(wildcard ../*.bin)
FONT_FILES += $(wildcard ../*.xxx)

FILES = $(filter %.fnt.txt,$(FONT_FILES:.bin=.fnt.txt) $(FONT_FILES:.xxx=.fnt.txt))
#FILES = $(patsubst %.bin, %.fnt.txt, $(FONT_FILES))
OBJS = $(patsubst %.c, %.o, $(wildcard *.c))
HDRS = $(wildcard *.h)

create: $(TARGET) $(FILES)

%.fnt.txt: %.bin $(TARGET)
	./$(TARGET) $< > $(notdir $@)

%.fnt.txt: %.xxx $(TARGET)
	./$(TARGET) $< > $(notdir $@)

%.o: %.c $(HDRS)
	$(CC) $(CFLAGS) -c $< -o $@

.PRECIOUS: $(TARGET) $(OBJS)

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -Wall $(LIBS) -o $@

clean:
	-rm -f *.o
	-rm -f $(TARGET)
	-rm -f $(notdir $(FILES))
