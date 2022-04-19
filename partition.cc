#include "partition_lib.cc"
#include "stdc++.h"

using namespace std;

int main(int argc, char *argv[])
{
    int flag = atoi(argv[1]);
    assert(flag == 0 && argc == 4);
    int algorithm = atoi(argv[2]);
    assert((algorithm >= 0 && algorithm <= 3) || (algorithm >= 11 && algorithm <= 13));
    vector<ll> v = parse_file(argv[3]);
    switch (algorithm)
    {
    case 0:
        cout << kk(v) << endl;
        break;
    case 1:
        cout << repeated_random(v, true) << endl;
        break;
    case 2:
        cout << regular_hill_climb(v) << endl;
        break;
    case 3:
        cout << regular_sim_anal(v) << endl;
        break;
    case 11:
        cout << repeated_random(v, false) << endl;
        break;
    case 12:
        cout << partition_hill_climb(v) << endl;
        break;
    case 13:
        cout << partition_sim_anal(v) << endl;
        break;
    default:
        break;
    }
}