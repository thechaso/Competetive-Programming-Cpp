#include <bits/stdc++.h>
using namespace std;
#define ll long long

int constructBit(vector<int> v)
{
    int bitRep = 0;
    for (int i : v) {
        bitRep |= (1 << i);
    }
    return bitRep;
}

int getSize(int bitRep)
{
    return __builtin_popcount(bitRep);
}

vector<int> getElementsOfSet(int bitRep)
{
    vector<int> v;
    for (int i = 0; i < 32; i++) {
        if ((bitRep & (1 << i)) != 0) v.push_back(i);
    }
    return v;
}

int get_intersection(int a, int b)
{
    return a & b;
}

int get_union(int a, int b)
{
    return a | b;
}

int get_complement(int a)
{
    return ~a;
}

int get_difference(int a, int b)
{
    return a & ~b;
}

int total_difference(int a, int b)
{
    return a ^ b;
}

int run()
{
    vector<int> x = {1, 3, 4, 8}, y = {3, 6, 8, 9};
    int a = constructBit(x), b = constructBit(y);
    int union_ = get_union(a, b), intersection = get_intersection(a, b);
    int complement_a = get_complement(a), complement_b = get_complement(b);
    int difference_a = get_difference(a, b), difference_b = get_difference(b, a);
    int difference = total_difference(a, b);
    cout << "Original Sets: " << endl;
    for (int i : x) cout << i << " ";
    cout << endl;
    for (int i : y) cout << i << " ";
    cout << endl;
    cout << "Union: " << endl;
    for (int i : getElementsOfSet(union_)) cout << i << " ";
    cout << endl;
    cout << "Intersection: " << endl;
    for (int i : getElementsOfSet(intersection)) cout << i << " ";
    cout << endl;
    cout << "Complements: " << endl;
    for (int i : getElementsOfSet(complement_a)) cout << i << " ";
    cout << endl;
    for (int i : getElementsOfSet(complement_b)) cout << i << " ";
    cout << endl;
    cout << "Specific Differences: " << endl;
    for (int i : getElementsOfSet(difference_a)) cout << i << " ";
    cout << endl;
    for (int i : getElementsOfSet(difference_b)) cout << i << " ";
    cout << endl;
    cout << "Total Difference: " << endl;
    for (int i : getElementsOfSet(difference)) cout << i << " ";
}

