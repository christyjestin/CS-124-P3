#include "stdc++.h"
#include "partition_lib.cc"
using namespace std;

int TRIALS = 50;
int N = 100;

string input_folder = "experiments/inputs/";
string output_folder = "experiments/outputs/";

int main(int argc, char **argv)
{
    // Setting up args
    int n, t;
    if (argc < 4)
    {
        t = TRIALS;
        n = N;
    }
    else
    {
        t = stoi(argv[1]);
        n = stoi(argv[2]);
    }

    ofstream f(output_folder + "data.csv");

    f << "Input, KK, Repeated Random, Hill Climbing, Sim. Annealing, Prep. Repeated Rand, Prep. Hill Climbing, Prep. Sim. Annealing,\n";

    for (int i = 0; i < t; i += 1)
    {
        string fname = input_folder + "t";
        fname += to_string(i);
        fname += "_in.txt";

        ifstream inp;
        inp.open(fname);

        vector<ll> v;
        for (int j = 0; j < n; j++)
        {
            ll num;
            inp >> num;
            v.push_back(num);
        }

        // Getting residuals

        ll res_kk = kk(v);
        ll res_rep_rand = repeated_random(v, true);
        ll res_hill = regular_hill_climb(v);
        ll res_sim = regular_sim_anal(v);
        ll res_prep_rep_rand = repeated_random(v, false);
        ll res_prep_hill = partition_hill_climb(v);
        ll res_prep_sim = partition_sim_anal(v);

        f << to_string(i) << ", " << res_kk << ", " << res_rep_rand << ", " << res_hill << ", " << res_sim << ", " << res_prep_rep_rand << ", " << res_prep_hill << ", " << res_prep_sim << ",\n";
    }

    f.close();
}