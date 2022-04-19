#include "stdc++.h"
using namespace std;

default_random_engine gen{(unsigned int)time(0)};

int T = 50;
int N = 100;
ll R = LLONG_MAX;

string input_folder = "experiments/inputs/";

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

    uniform_int_distribution<ll> unif((ll)1, (ll)pow(10, 12));
    for (int i = 0; i < t; i++)
    {
        // Create new file
        ofstream f;
        string fname = input_folder + "t";
        fname += to_string(i);
        fname += "_in.txt";
        f.open(fname);

        for (int j = 0; j < n; j++)
        {
            f << unif(gen) % r;
            f << endl;
        }

        f.close();
    }
}