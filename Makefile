CC = gcc
CFLAGS = -Wall -Wextra -Iinclude -std=c2x

TARGET = lib/darray.a

.PHONY: release
release: CFLAGS += -O3
release: $(TARGET) tests

debug: CFLAGS += -O0 -g
debug: $(TARGET) tests

.PHONY: build
build:
	mkdir -p build
	mkdir -p bin/tests
	mkdir -p lib

.PHONY: clean
clean:
	rm -rf $(TARGET)
	rm -rf lib bin build


$(TARGET): build build/cpy.o
	ar rcs $(TARGET) build/cpy.o


.PHONY: tests
tests: LDLIBS += -lcheck -lsubunit
tests: test/cpy-tests.c
	$(CC) $(CFLAGS) $(LDFLAGS) $(LDLIBS) test/cpy-tests.c $(TARGET) -o bin/tests/cpy-tests


build/cpy.o: src/cpy.c include/cpy.h
	$(CC) $(CFLAGS) $(LDFLAGS) $(LDLIBS) -c src/cpy.c -o build/cpy.o


	

