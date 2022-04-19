CPPFLAGS=-std=c++17 -O2
DEPS=stdc++.h utils.cc heap.cc partition_lib.cc
RM=rm
CPP=g++

partition: $(DEPS) partition.cc
	$(CPP) $(CPPFLAGS) partition.cc -o $@

gen_outputs: $(DEPS) gen_outputs.cc
	$(CPP) $(CPPFLAGS) gen_outputs.cc -o $@

%: %.cc $(DEPS)
	$(CPP) $(CPPFLAGS) $< -o $@

clean:
	$(RM) partition

clean_gen:
	$(RM) gen_outputs

clean_in:
		$(RM) experiments/inputs/*.txt

clean_out:
		$(RM) experiments/outputs/data.csv