#include <bits/stdc++.h>
using namespace std;

int n, m;
vector<vector<int>> adj;
priority_queue<vector<int>, vector<vector<int>>, greater<vector<int>>> pq;


void dfs(int cur, vector<bool> visited, int num, vector<int> path) {
    if (num == n) {
        pq.push(path);
        return;
    }
    for (int neighbor : adj[cur]) {
        if (!visited[neighbor]) {
            visited[neighbor] = true;
            path.push_back(neighbor);
            dfs(neighbor, visited, num+1, path);
            path.pop_back();
            visited[neighbor] = false;
        }
    }
}

int main() {
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        adj.push_back({});
    }
    for (int i = 0; i < m; i++) {
        int from, to, weight;
        cin >> from >> to >> weight;
        adj[from].push_back(to);
        adj[to].push_back(from);
    }
    int source;
    cin >> source;
    vector<bool> visited(n, false);
    visited[source] = true;
    dfs(source, visited, 1, {source});
    while (!pq.empty()) {
        vector<int> path = pq.top();
        pq.pop();
        int last = path[path.size() - 1];
        bool isCircuit = false;
        for (int neighbor : adj[source]) {
            if (neighbor == last) {
                isCircuit = true;
                break;
            }
        }
        for (int i : path) cout << i;
        if (isCircuit) cout << "*" << endl;
        else cout << "." << endl;
    }
}
