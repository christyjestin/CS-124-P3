CPPFLAGS=-std=c++17 -O3 -Wall
DEPS=stdc++.h utils.cc heap.cc
RM=rm
CPP=g++

partition: $(DEPS) partition.cc
	$(CPP) $(CPPFLAGS) partition.cc -o partition

gen_outputs: $(DEPS) gen_outputs.cc
	$(CPP) $(CPPFLAGS) gen_outputs.cc -o gen_outputs.o

%: %.cc $(DEPS)
	$(CPP) $(CPPFLAGS) $< -o $@.o

clean:
	$(RM) *.o partition