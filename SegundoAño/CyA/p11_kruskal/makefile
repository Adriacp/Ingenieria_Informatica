CTDS = g++
CFLAGS = -g

TM_simulator: EMSTmain.cpp point_set.cpp point_types.cpp sub_tree.cpp
	$(CTDS) $(CFLAGS) EMSTmain.cpp point_set.cpp point_types.cpp sub_tree.cpp -o EMST

.PHONY: clean

clean:
	rm -rf EMST
	rm -rf *.o