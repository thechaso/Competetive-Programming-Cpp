#include <bits/stdc++.h>
using namespace std;

//given a graph with n edges and 2n nodes, find the size of the smallest and largest component with size >= 2

int n, m;
vector<vector<int>> adj;
vector<int> componenets;

int find(int x) {
    return componenets[x];
}

bool same(int a, int b) {
    return find(a) == find(b);
}

void unite(int a, int b) {
    int oc = componenets[a], nc = componenets[b];
    for (int i = 0; i < n; i++) {
        if (componenets[i] == oc) componenets[i] = nc;
    }
}

int main() {
    cin >> n;
    m = n;
    n *= 2;
    for (int i = 0; i < n; i++) {
        adj.push_back({});
        componenets.push_back(i);
    }
    for (int i = 0; i < m; i++) {
        int from, to;
        cin >> from >> to;
        from--; to--;
        unite(from, to);
    }
    map<int, int> freq;
    for (int i : componenets) freq[i]++;
    int mn = -1, mx = -1;
    for (auto p : freq) {
        int count = p.second;
        if (count >= 2) {
            if (mx == -1) mx = count;
            else mx = max(mx, count);
            if (mn == -1) mn = count;
            else mn = min(mn, count);
        }
    }
    cout << mn << " " << mx;
}
