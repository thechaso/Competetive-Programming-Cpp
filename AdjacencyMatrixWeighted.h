#include <bits/stdc++.h>
using namespace std;

int n;
vector<vector<int>> adj;

void printAdj()
{
    for (vector<int> i : adj) {
        for (int j : i) cout << j << " ";
        cout << endl;
    }
}

int run()
{
    cin >> n;
    for (int i = 0; i < n; i++) {
        adj.push_back(vector<int>(n));
    }
    int m;
    cin >> m;
    while (m--) {
        int from, to, weight;
        cin >> from >> to >> weight;
        adj[from][to] = weight;
        adj[to][from] = weight;
    }
    printAdj();
}
