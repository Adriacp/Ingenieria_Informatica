CTDS = g++
CFLAGS = -Wall -g

TM_simulator: ClienteTMSimulator.cc turingmachine.cc alphabet.cc symbol.cc node.cc
	$(CTDS) $(CFLAGS) ClienteTMSimulator.cc turingmachine.cc alphabet.cc symbol.cc node.cc -o TM_simulator 

.PHONY: clean

clean:
	rm -rf TM_simulator
	rm -rf *.o