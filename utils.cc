#include "stdc++.h"
#include "heap.cc"

using namespace std;

default_random_engine gen{(unsigned int)time(0)};

// Performs KK on a set of numbers
ll kk(vector<ll> v)
{
    Heap<ll> h(v);

    while (h.len > 1)
    {
        ll m1 = h.extract_max(0);
        ll m2 = h.extract_max(0);
        ll res = m1 - m2;
        if (res == m1)
            return m1;
        h.insert(res);
    }

    return h.extract_max(0);
}

// randomly generate a partition (sampling with replacement from 1 to n)
vector<int> partition(int n)
{
    uniform_int_distribution<int> dist(0, n - 1);
    vector<int> p;
    for (int i = 0; i < n; i++)
    {
        p.push_back(dist(gen));
    }
    return p;
}

// group elements based on partition and then run karmarkar-karp
ll group_kk(vector<ll> v, vector<int> partition)
{
    assert(v.size() == partition.size());
    vector<ll> group(v.size(), (ll)0);
    for (int i = 0; i < (int)v.size(); i++)
    {
        group[partition[i]] += v[i];
    }
    return kk(group);
}