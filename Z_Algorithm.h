#include <bits/stdc++.h>
using namespace std;
#define ll long long

string text, pattern;

vector<int> z(string s) {
    int n = s.size();
    vector<int> z(n);
    int x = 0, y = 0;
    for (int i = 1; i < n; i++) {
        z[i] = max(0,min(z[i-x],y-i+1));
        while (i+z[i] < n && s[z[i]] == s[i+z[i]]) {
            x = i; y = i+z[i]; z[i]++;
        }
    }
    return z;
}

int run()
{
    cin >> text >> pattern;
    string concat = text + "$" + pattern;
    vector<int> z_arr = z(concat);
    for (int i = 0; i < z_arr.size(); i++) {
        if (z_arr[i] == pattern.size()) cout << i - pattern.size() - 1 << " ";
    }
}

