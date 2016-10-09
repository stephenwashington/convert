CFLAGS = -Wall -Wextra -pedantic -Werror -Wshadow -Wstrict-overflow \
-fno-strict-aliasing -O2
LIBS = -lcheck -lm -lsubunit -lrt -lpthread

OBJECTS = rpn_utilities.o check_rpn_utilities.o

all: check_rpn_utilities

check_rpn_utilities: $(OBJECTS)
	gcc -std=c99 -o check_rpn_utilities $(OBJECTS) $(CFLAGS) $(LIBS)

rpn_utilities.o: rpn_utilities.h
check_rpn_utilities.o: rpn_utilities.h

.PHONY: clean
clean:
	-rm -f rpn_utilities check_rpn_utilities $(OBJECTS)
