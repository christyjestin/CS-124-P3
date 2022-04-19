#include "utils.cc"
#include "stdc++.h"

using namespace std;

// one file for the heap
// one file for utils: kk, prepartitioning
// one file for search algorithms

int MAX_ITER = 25000;

bernoulli_distribution coin_flip(0.5);

// randomly generate assignment by flipping a coin for each element and then calculate the residual
ll regular_random(vector<ll> v)
{
    ll residual = 0;
    for (int j = 0; j < (int)v.size(); j++)
    {
        residual += coin_flip(gen) ? v[j] : -v[j];
    }
    return abs(residual);
}

// generate a random partition and then run karmarkar-karp with that partition
inline ll prepartition_random(vector<ll> v)
{
    return group_kk(v, partition(v.size()));
}

ll repeated_random(vector<ll> v, bool use_regular_rep)
{
    ll residual = -1;
    for (int iter = 0; iter <= MAX_ITER; iter++)
    {
        ll current = use_regular_rep ? regular_random(v) : prepartition_random(v);
        if (residual == -1 || current < residual)
            residual = current;
    }
    return residual;
}

ll regular_hill_climb(vector<ll> v)
{
    uniform_int_distribution<int> i_dist(0, v.size() - 1);
    uniform_int_distribution<int> j_dist(0, v.size() - 2);
    vector<bool> assignment;
    ll residual = 0;
    // random initial assignment
    for (int j = 0; j < (int)v.size(); j++)
    {
        assignment.push_back(coin_flip(gen));
        residual += assignment.back() ? v[j] : -v[j];
    }

    for (int iter = 0; iter < MAX_ITER; iter++)
    {
        // randomly generate two indices i,j with i \neq j
        int i = i_dist(gen);
        int j = j_dist(gen);
        if (j >= i)
            j++;

        bool second_flip = coin_flip(gen);
        // change residual to reflect the neighbor's assignment
        ll neighbor = residual - 2 * (assignment[i] ? v[i] : -v[i]);
        if (second_flip)
            neighbor -= 2 * (assignment[j] ? v[j] : -v[j]);
        // switch to neighbor if the neighbor's assignment is better
        if (abs(neighbor) < abs(residual))
        {
            residual = neighbor;
            assignment[i] = !assignment[i];
            if (second_flip)
                assignment[j] = !assignment[j];
        }
    }
    return abs(residual);
}

ll partition_hill_climb(vector<ll> v)
{
    uniform_int_distribution<int> i_dist(0, v.size() - 1);
    uniform_int_distribution<int> j_dist(0, v.size() - 2);
    // random initial assignment
    vector<int> assignment = partition(v.size());
    ll residual = group_kk(v, assignment);

    for (int iter = 0; iter < MAX_ITER; iter++)
    {
        // randomly generate two indices i,j with p_i \neq j
        int i = i_dist(gen);
        int j = j_dist(gen);
        int p_i = assignment[i];
        if (j >= p_i)
            j++;

        assignment[i] = j;
        ll neighbor = group_kk(v, assignment);
        // switch back if the neighbor's assignment isn't better
        if (neighbor > residual)
        {
            assignment[i] = p_i;
        }
        else
        {
            residual = neighbor;
        }
    }
    return residual;
}

double T(int iter)
{
    return pow(10, 10) * pow(0.8, iter / 300);
}

ll regular_sim_anal(vector<ll> v)
{
    uniform_int_distribution<int> i_dist(0, v.size() - 1);
    uniform_int_distribution<int> j_dist(0, v.size() - 2);
    uniform_real_distribution<double> unif(0.0, 1.0);
    vector<bool> assignment;
    ll residual = 0;
    // random initial assignment
    for (int j = 0; j < (int)v.size(); j++)
    {
        assignment.push_back(coin_flip(gen));
        residual += assignment.back() ? v[j] : -v[j];
    }
    ll min_residual = abs(residual);

    for (int iter = 0; iter < MAX_ITER; iter++)
    {
        // randomly generate two indices i,j with i \neq j
        int i = i_dist(gen);
        int j = j_dist(gen);
        if (j >= i)
            j++;

        bool second_flip = coin_flip(gen);
        // change residual to reflect the neighbor's assignment
        ll neighbor = residual - 2 * (assignment[i] ? v[i] : -v[i]);
        if (second_flip)
            neighbor -= 2 * (assignment[j] ? v[j] : -v[j]);
        // switch to neighbor if the neighbor's assignment is better or just randomly sometimes
        double prob = exp((abs(residual) - abs(neighbor)) / T(iter));
        if (abs(neighbor) < abs(residual) || unif(gen) < prob)
        {
            residual = neighbor;
            assignment[i] = !assignment[i];
            if (second_flip)
                assignment[j] = !assignment[j];
        }
        if (abs(residual) < min_residual)
            min_residual = abs(residual);
    }
    return min_residual;
}

ll partition_sim_anal(vector<ll> v)
{
    uniform_int_distribution<int> i_dist(0, v.size() - 1);
    uniform_int_distribution<int> j_dist(0, v.size() - 2);
    uniform_real_distribution<double> unif(0.0, 1.0);
    // random initial assignment
    vector<int> assignment = partition(v.size());
    ll residual = group_kk(v, assignment);
    ll min_residual = abs(residual);

    for (int iter = 0; iter < MAX_ITER; iter++)
    {
        // randomly generate two indices i,j with i \neq j
        int i = i_dist(gen);
        int j = j_dist(gen);
        int p_i = assignment[i];
        if (j >= i)
            j++;

        assignment[i] = j;
        ll neighbor = group_kk(v, assignment);
        double prob = exp((abs(residual) - abs(neighbor)) / T(iter));
        // switch if the neighbor's assignment is better or just randomly sometimes
        if (neighbor < residual || unif(gen) < prob)
        {
            residual = neighbor;
        }
        else
        {
            assignment[i] = p_i;
        }
        if (abs(residual) < min_residual)
            min_residual = abs(residual);
    }
    return min_residual;
}

vector<ll> parse_file(char *filename)
{
    vector<ll> v;
    ifstream file(filename);
    if (file.is_open())
    {
        string line;
        while (getline(file, line))
            v.push_back(stoll(line));
        file.close();
    }
    return v;
}