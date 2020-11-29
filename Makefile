CC = g++-10
CFLAGS = -g -Wall -std=c++2a

default: tests

tests: test_main.o Rule_test.o Rule.o
	$(CC) $(CFLAGS) -o bin/unit_tests build/test_main.o build/Rule_test.o build/Rule.o -Ilib -Iinclude

test_main.o: test/test_main.cpp
	$(CC) $(CFLAGS) -c test/test_main.cpp -o build/test_main.o -Ilib

Rule_test.o: test/engine/grammar/Rule_test.cpp include/bestinshow/engine/grammar/Rule.h
	$(CC) $(CFLAGS) -c test/engine/grammar/Rule_test.cpp -o build/Rule_test.o -Ilib -Iinclude

Rule.o: src/engine/grammar/Rule.cpp
	$(CC) $(CFLAGS) -c src/engine/grammar/Rule.cpp -o build/Rule.o -Iinclude

