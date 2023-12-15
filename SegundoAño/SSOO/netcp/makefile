CTDS = g++-13 -o
CFLAGS = -std=c++23

netcp: netcp.cpp subprocess.cpp
	$(CTDS) netcp $(CFLAGS) netcp.cpp subprocess.cpp

.PHONY: clean

clean:
	rm -rf netcp
	
