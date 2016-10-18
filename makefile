# Main makefile
CC := gcc
SRCDIR := src
BUILDDIR := build
TESTDIR := test

TARGET := convert
TEST_TARGET := convert_tests

SOURCES := $(shell find $(SRCDIR) -type f -name *.c)
OBJECTS := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.c=.o))
TEST_SOURCES := $(shell find $(TESTDIR) -type f -name *.c)
TEST_OBJECTS := $(patsubst $(TESTDIR)/%,$(BUILDDIR)/%,$(TEST_SOURCES:.c=.o))
TEST_OBJECTS += $(OBJECTS)
TEST_OBJECTS := $(filter-out build/main.o, $(TEST_OBJECTS))

CFLAGS := -std=c99 -Wall -Wextra -Wpedantic -Werror -Wshadow -Wstrict-overflow\
          -fstack-protector -O2
LIBS := -lcheck -lm -lsubunit -lrt -lpthread
INC := -I include

all: convert tests
convert: $(TARGET)
tests: $(TEST_TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $^ -o $(TARGET) $(INC) $(CFLAGS) $(LIBS)

$(TEST_TARGET): $(TEST_OBJECTS)
	$(CC) $^ -o $(TEST_TARGET) $(INC) $(CFLAGS) $(LIBS)
	
$(BUILDDIR)/%.o: $(SRCDIR)/%.c
	mkdir -p $(BUILDDIR)
	$(CC) -c -o $@ $< $(INC) $(CFLAGS) $(LIBS)
	
$(BUILDDIR)/%.o: $(TESTDIR)/%.c
	mkdir -p $(BUILDDIR)
	$(CC)  -c -o $@ $< $(INC) $(CFLAGS) $(LIBS)

.PHONY: clean
clean:
	-@rm -rf $(BUILDDIR) $(TEST_TARGET) $(TARGET)
