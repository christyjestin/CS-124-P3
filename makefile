CPPFLAGS=-std=c++17 -O3 -Wall
DEPS=stdc++.h utils.cc heap.cc partition_lib.cc
RM=rm
CPP=g++

partition: $(DEPS) partition.cc
	$(RM) partition
	$(CPP) $(CPPFLAGS) partition.cc -o %@

gen_outputs: $(DEPS) gen_outputs.cc
	$(CPP) $(CPPFLAGS) gen_outputs.cc -o gen_outputs.o

%: %.cc $(DEPS)
	$(CPP) $(CPPFLAGS) $< -o $@.o

clean:
	$(RM) *.o partition

clean_in:
		$(RM) experiments/inputs/*.txt

clean_out:
		$(RM) experiments/outputs/data.csv