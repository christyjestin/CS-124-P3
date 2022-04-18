#include "stdc++.h"
#include <chrono>
using namespace std;
using namespace std::chrono;

int T = 50;
int N = 100;
ll R = LLONG_MAX;

string input_folder = "experiments/inputs/";
string output_folder = "experiments/outputs/";

int main(int argc, char **argv)
{
    // Setting up args
    int n, t;
    ll r;
    if (argc < 4)
    {
        t = T;
        n = N;
        r = R;
    }
    else
    {
        t = stoi(argv[1]);
        n = stoi(argv[2]);
        r = stoll(argv[3]);
    }

    ofstream f(output_folder + "recorded_times.csv");

    f << "Input, Repeated Random, Hill Climbing, Sim. Annealing, Prep. Repeated Rand, Prep. Hill Climbing, Prep. Sim. Annealing,\n";

    for (int i = t; i < n; i += 1)
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

        ll res_rep_rand = 0;
        ll res_hill = 0;
        ll res_sim = 0;
        ll res_prep_rep_rand = 0;
        ll res_prep_hill = 0;
        ll res_prep_sim = 0;

        f << to_string(i) << ", " << res_rep_rand << ", " << res_hill << res_sim << res_prep_rep_rand << res_prep_hill << res_prep_sim << ",\n";
    }

    f.close();
}