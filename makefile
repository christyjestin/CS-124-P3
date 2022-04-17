CPPFLAGS=-std=c++17 -O3 -Wall
DEPS=stdc++.h
RM=rm
CPP=g++

partition: partition.cc  $(DEPS)
	$(CPP) $(CPPFLAGS) partition.cc -o partition 

%.o: %.cc $(DEPS)
	$(CPP) $(CPPFLAGS) $< -o $@

clean:
	$(RM) partition *.o