#include "stdc++.h"
using namespace std;

/*
    Code for a Maximum Heap
*/
template <class T>
class Heap
{
public:
    int len;
    vector<T> v;
    void insert(T);
    T peak();
    void max_heapify(int);
    T extract_max(T);
    int get_parent(int);
    int get_lchild(int);
    int get_rchild(int);

    Heap(vector<T>);
};

template <class T>
Heap<T>::Heap(vector<T> v)
{
    len = 0;
    for (auto it = v.begin(); it != v.end(); it++)
        insert(*it);
}

template <class T>
int Heap<T>::get_parent(int i)
{
    return (i - 1) / 2;
}

template <class T>
int Heap<T>::get_lchild(int i)
{
    return (2 * i) + 1;
}

template <class T>
int Heap<T>::get_rchild(int i)
{
    return (2 * i) + 2;
}

template <class T>
void Heap<T>::insert(T x)
{
    len++;
    int i = len - 1;
    if ((int) v.size() >= len)
        v[i] = x;
    else
        v.push_back(x);
    int p = get_parent(i);
    while (v[i] > v[p])
    {
        T c = v[i];
        v[i] = v[p];
        v[p] = c;
        i = p;
        if (i <= 0)
            break;
        p = get_parent(i);
    }
}

template <class T>
T Heap<T>::peak()
{
    return v[0];
}

template <class T>
void Heap<T>::max_heapify(int i)
{
    bool changed = true;
    while (changed)
    {
        changed = false;
        int l = get_lchild(i);
        int r = get_rchild(i);
        int largest = i;
        if (l < len && v[l] > v[largest])
            largest = l;
        if (r < len && v[r] > v[largest])
            largest = r;

        if (largest != i)
        {
            changed = true;
            // swap parent with largest child
            T p = v[i];
            v[i] = v[largest];
            v[largest] = p;

            i = largest;
        }
    }
}

template <class T>
T Heap<T>::extract_max(T def)
{
    if (len < 1)
        return def;
    T mn = v[0];
    v[0] = v[len - 1];
    len--;
    max_heapify(0);
    return mn;
}