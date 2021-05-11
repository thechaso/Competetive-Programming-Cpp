#include <bits/stdc++.h>
using namespace std;
#define ll long long

int n;
vector<vector<int>> adj;

void topSortUtil(int cur, vector<bool>& visited, stack<int>& s)
{
    visited[cur] = true;
    for (int neighbor : adj[cur]) {
        if (!visited[neighbor]) {
            topSortUtil(neighbor, visited, s);
        }
    }
    s.push(cur);
}

vector<int> topSort()
{
    vector<bool> visited(n, false);
    stack<int> s;
    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            topSortUtil(i, visited, s);
        }
    }
    vector<int> ordering;
    while (!s.empty()) {
        ordering.push_back(s.top());
        s.pop();
    }
    return ordering;
}

vector<int> shortestPathDAG(int source)
{
    vector<int> ordering = topSort();
    vector<int> distance(n, -1);
    distance[source] = 0;
    for (int i = 0; i < n; i++) {
        int cur = ordering[i];
        if (distance[cur] != -1) {
            for (int neighbor : adj[cur]) {
                if (distance[neighbor] == -1) distance[neighbor] = distance[cur] + 1;
                else distance[neighbor] = min(distance[neighbor], distance[cur] + 1);
            }
        }
    }
    return distance;
}

vector<int> longestPathDAG(int source)
{
    vector<int> ordering = topSort();
    vector<int> distance(n, -1);
    distance[source] = 0;
    for (int i = 0; i < n; i++) {
        int cur = ordering[i];
        if (distance[cur] != -1) {
            for (int neighbor : adj[cur]) {
                if (distance[neighbor] == -1) distance[neighbor] = distance[cur] + 1;
                else distance[neighbor] = max(distance[neighbor], distance[cur] + 1);
            }
        }
    }
    return distance;
}

int run()
{
    int m;
    cin >> n >> m;
    for (int i = 0; i < n; i++) adj.push_back({});
    while (m--) {
        int from, to;
        cin >> from >> to;
        //directed edge
        adj[from].push_back(to);
    }
    int source;
    cin >> source;
    cout << "Topological Sorting: " << endl;
    for (int i : topSort()) cout << i << " ";
    cout << endl << "Shortest Path on DAG using DP: " << endl;
    for (int i : shortestPathDAG(source)) cout << i << " ";
    cout << endl << "Longest Path on DAG using DP: " << endl;
    for (int i : longestPathDAG(source)) cout << i << " ";
}

