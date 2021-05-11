#include <bits/stdc++.h>
using namespace std;
#define ll long long

int n;
vector<vector<pair<int, int>>> adj;

vector<int> dijkstra(int source)
{
    vector<int> distance(n, INT_MAX);
    //pq will store {distance from source to node, node}
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    vector<bool> processed(n, false);
    distance[source] = 0;
    pq.push({0, source});
    while (!pq.empty()) {
        int cur = pq.top().second;
        pq.pop();
        if (processed[cur]) continue;
        processed[cur] = true;
        for (pair<int, int> neighbor : adj[cur]) {
            int node = neighbor.first, weight = neighbor.second;
            if (distance[cur] + weight < distance[node]) {
                distance[node] = distance[cur] + weight;
                pq.push({distance[node], node});
            }
        }
    }
    return distance;
}


int run()
{
    cin >> n;
    for (int i = 0; i < n; i++) {
        vector<pair<int, int>> vp;
        adj.push_back(vp);
    }
    int m;
    cin >> m;
    while (m--) {
        int from, to, weight;
        cin >> from >> to >> weight;
        adj[from].push_back({to, weight});
        adj[to].push_back({from, weight});
    }
    int source;
    cin >> source;
    for (int i : dijkstra(source)) cout << i << " ";
}

