CC = g++
PYLIBPATH = $(shell python-config --exec-prefix)/lib
LIB = -L$(PYLIBPATH) $(shell python-config --libs) -lboost_python
OPTS = $(shell python-config --include) -O2 -fPIC

default: zoo.so
	@python ./visit_zoo.py

zoo.so: zoo.o
	$(CC) -shared -Wl,-rpath,$(PYLIBPATH),--export-dynamic $< $(LIB) -o $@

zoo.o: zoo.cpp Makefile
	$(CC) $(OPTS) -c $< -o $@

clean:
	rm -rf *.so *.o

.PHONY: default clean
