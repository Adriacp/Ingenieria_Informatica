CTDS = g++
CFLAGS = -Wall -g

p05_automata_simulator: Clientep05_automata_simulator.cc alfabeto.cc estado.cc automata.cc transicion.cc
	$(CTDS) $(CFLAGS) Clientep05_automata_simulator.cc transicion.cc estado.cc alfabeto.cc automata.cc -o p05_automata_simulator 

.PHONY: clean

clean:
	rm -rf p05_automata_simulator
	rm -rf *.o
