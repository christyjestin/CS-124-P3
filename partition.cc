#include "utils.cc"
#include "stdc++.h"

using namespace std;

// one file for the heap
// one file for utils: kk, prepartitioning
// one file for search algorithms

int MAX_ITER = 25;

default_random_engine gen;
bernoulli_distribution coin_flip(0.5);

// randomly generate assignment by flipping a coin for each element and then calculate the residual
ll regular_random(vector<ll> v) {
    ll residual = 0;
    for (int j = 0; j < v.size(); j++) {
        residual += coin_flip(gen) ? v[j] : -v[j];
    }
    return residual;
}

// generate a random partition and then run karmarkar-karp with that partition
inline ll prepartition_random(vector<ll> v) {
    return group_kk(v, partition(v.size()));
}

ll repeated_random(vector<ll> v, bool use_regular_rep) {
    ll residual = -1;
    for (int iter = 0; iter < MAX_ITER; iter++) {
        ll current = use_regular_rep ? regular_random(v) : prepartition_random(v);
        if (residual == -1 || current < residual) residual = current;
    }
    return residual;
}

ll regular_hill_climb(vector<ll> v) {
    uniform_int_distribution<int> i_dist(0, v.size()-1);
    uniform_int_distribution<int> j_dist(0, v.size()-2);
    vector<bool> assignment;
    ll residual = 0;
    // random initial assignment
    for (int j = 0; j < v.size(); j++) {
        assignment.push_back(coin_flip(gen));
        residual += assignment.back() ? v[j] : -v[j];
    }
    for (int iter = 0; iter < MAX_ITER; iter++) {
        int i = i_dist(gen);
        int j = j_dist(gen);
        if (j >= i) j++;
        bool second_flip = coin_flip(gen);
        ll neighbor = residual - 2 * (assignment[i] ? v[i] : -v[i]);
        if (second_flip) neighbor -= 2 * (assignment[j] ? v[j] : -v[j]);
        if (neighbor < residual) {
            residual = neighbor;
            assignment[i] = !assignment[i];
            if (second_flip) assignment[j] = !assignment[j];
        }
    }
    return residual;
}

int main(int argc, char* argv[]) {
    int flag = atoi(argv[1]);
    assert(flag == 0 && argc == 4);
    int algorithm = atoi(argv[2]);
}