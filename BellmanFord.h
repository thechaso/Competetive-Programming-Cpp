#include <bits/stdc++.h>
using namespace std;
#define ll long long

//This is implemented using undirected edge list

int n, m;
vector<vector<int>> edges;

vector<int> bellmanFord(int source) {
    vector<int> distance(n, INT_MAX);
    distance[source] = 0;
    for (int i = 0; i < n; i++) {
        for (vector<int> edge : edges) {
            int from = edge[0], to = edge[1], weight = edge[2];
            //if distance[from] i infinity, then adding to that will bring int number to negative
            //making algorithm return wrong answer
            if (distance[from] != INT_MAX && distance[from] + weight < distance[to]) {
                distance[to] = distance[from] + weight;
            }
        }
    }
    return distance;
}

bool containsNegativeCycle() {
    //when checking for negative cycle, source can be picked arbitrarily
    vector<int> distance = bellmanFord(0);
    vector<int> initDist = distance;
    for (vector<int> edge : edges) {
        int from = edge[0], to = edge[1], weight = edge[2];
        if (distance[from] != INT_MAX && distance[from] + weight < distance[to]) {
                return true;
            }
    }
    return false;
}


int run() {
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int from, to, weight;
        cin >> from >> to >> weight;
        //undirected edge
        edges.push_back({from, to, weight});
        edges.push_back({to, from, weight});
    }
    int source;
    cin >> source;
    if (containsNegativeCycle()) cout << "Graph contains negative cycle";
    else for (int i : bellmanFord(source)) cout << i << " ";
}
