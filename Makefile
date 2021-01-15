CC = g++-10
CFLAGS = -g -Wall -std=c++2a -Iinclude

default: tests

tests: test_main.o Rule_test.o Rule.o Grammar_test.o Grammar.o
	$(CC) $(CFLAGS) -o bin/unit_tests build/test_main.o build/Rule_test.o build/Rule.o build/Grammar_test.o build/Grammar.o -Ilib

test_main.o: test/test_main.cpp
	$(CC) $(CFLAGS) -c test/test_main.cpp -o build/test_main.o -Ilib

Rule_test.o: test/engine/grammar/Rule_test.cpp
	$(CC) $(CFLAGS) -c test/engine/grammar/Rule_test.cpp -o build/Rule_test.o -Ilib

Rule.o: src/engine/grammar/Rule.cpp
	$(CC) $(CFLAGS) -c src/engine/grammar/Rule.cpp -o build/Rule.o

Grammar_test.o: test/engine/grammar/Grammar_test.cpp
	$(CC) $(CFLAGS) -c test/engine/grammar/Grammar_test.cpp -o build/Grammar_test.o -Ilib

Grammar.o: src/engine/grammar/Grammar.cpp
	$(CC) $(CFLAGS) -c src/engine/grammar/Grammar.cpp -o build/Grammar.o

libgrammar.a: Rule.o Grammar.o
	ar rcs lib/bestinshow/engine/grammar/libgrammar.a build/Rule.o build/Grammar.o

ExampleGrammar.o: src/engine/grammar/ExampleGrammar.cpp
	$(CC) $(CFLAGS) -c src/engine/grammar/ExampleGrammar.cpp -o build/ExampleGrammar.o

parsing_example.o: src/parsing_example.cpp
	$(CC) $(CFLAGS) -c src/parsing_example.cpp -o build/parsing_example.o

parsing_example: parsing_example.o ExampleGrammar.o libgrammar.a
	$(CC) $(CFLAGS) -o bin/parsing_example build/parsing_example.o -L./lib/bestinshow/engine/grammar -l grammar build/ExampleGrammar.o