#include <bits/stdc++.h>
using namespace std;
#define ll long long

//O(n^3) time
void print_substrings(string str)
{
    for (int start = 0; start < str.size(); start++) {
        for (int stop = start; stop < str.size(); stop++) {
            string sub = str.substr(start, stop - start + 1);
            cout << sub << endl;
        }
    }
}

//O(2^n) time
void print_subsequences(string str, string cur = "", int i = 0)
{
    if (i == str.size()) {
        cout << cur << endl;
        return;
    }
    print_subsequences(str, cur, i + 1);
    print_subsequences(str, cur + str[i], i  + 1);
}

//O(n) time
vector<string> prefix_array(string str)
{
    vector<string> prefix(str.size());
    prefix[0] = str[0];
    for (int i = 1; i < str.size(); i++) prefix[i] += (prefix[i - 1] + str[i]);
    return prefix;
}

//O(n) time
vector<string> suffix_array(string str)
{
    vector<string> suffix(1);
    suffix[0] = str[str.size() - 1];
    string cur = suffix[0];
    for (int i = str.size() - 2; i >= 0; i--) {
        cur += str[i];
        suffix.push_back(cur);
        reverse(suffix[suffix.size() - 1].begin(), suffix[suffix.size() - 1].end());
    }
    return suffix;
}

void print_rotations(string str)
{
    for (int i = 0; i < str.size(); i++) {
        rotate(str.begin(), str.begin() + 1, str.end());
        cout << str << endl;
    }
}

//print consecutive substrings of str of size k
void sliding_window(string str, int k)
{
    string window = "";
    int ptr = 0;
    while (ptr < k) {
        window += str[ptr];
        ptr++;
    }
    while (ptr < str.size()) {
        //process window
        cout << window << endl;
        window.erase(window.begin() + 0);
        window += str[ptr];
        ptr++;
    }
    //process last window
    cout << window << endl;
}

//O(n*log(n) + n!) time
void print_permutations(string str)
{
    sort(str.begin(), str.end());
    do {
        cout << str << endl;
    } while (next_permutation(str.begin(), str.end()));
}
