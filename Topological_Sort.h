#include <bits/stdc++.h>
using namespace std;
#define ll long long

int n, m;
vector<vector<int>> adj;
vector<int> in;

int main()
{
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        adj.push_back({});
        in.push_back(0);
    }
    for (int i = 0; i < m; i++) {
        int from, to;
        cin >> from >> to;
        adj[from - 1].push_back(to - 1);
        in[to - 1]++;
    }
    queue<int> no_indeg;
    vector<int> ans;
    for (int i = 0; i < n; i++) {
        if (!in[i]) {
            no_indeg.push(i);
        }
    }
    while (!no_indeg.empty()) {
        int cur = no_indeg.front();
        no_indeg.pop();
        ans.push_back(cur);
        for (int neighbor : adj[cur]) {
            in[neighbor]--;
            if (!in[neighbor]) no_indeg.push(neighbor);
        }
    }
    if (ans.size() != n) cout << "IMPOSSIBLE";
    else {
        for (int i : ans) cout << i + 1 << " ";
    }
}

