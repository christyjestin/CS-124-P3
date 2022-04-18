CPPFLAGS=-std=c++17 -O3 -Wall
DEPS=stdc++.h utils.cc heap.cc
RM=rm
CPP=g++

partition: $(DEPS)
	$(CPP) $(CPPFLAGS) partition.cc -o partition

%: %.cc $(DEPS)
	$(CPP) $(CPPFLAGS) $< -o $@

clean:
	$(RM) partition *.o