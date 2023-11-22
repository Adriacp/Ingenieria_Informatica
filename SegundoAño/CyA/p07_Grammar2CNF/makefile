CTDS = g++
CFLAGS = -Wall -g

p06NFA2DFA: Grammar2CNF.cc grammar.cc alphabet.cc symbol.cc
	$(CTDS) $(CFLAGS) Grammar2CNF.cc grammar.cc alphabet.cc symbol.cc -o Grammar2CNF 

.PHONY: clean

clean:
	rm -rf Grammar2CNF
	rm -rf *.o