#include <bits/stdc++.h>
using namespace std;
#define ll long long

//this algorithm is implemented using an undirected adjacency matrix

int n;
vector<vector<int>> adj;

vector<vector<int>> floydWarshall()
{
    vector<vector<int>> distance = adj;
    for (int k = 0; k < n; k++) {//k is intermediate node
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                 if (i == j) distance[i][j] = 0;
                 //if distance from node to intermediate node k is infinity, there is no path
                 //so this condition checks if there is a path, and then if there is a shorter path
                 else if (distance[i][k] != INT_MAX && distance[k][j] != INT_MAX)
                    distance[i][j] = min(distance[i][j], distance[i][k] + distance[k][j]);
            }
        }
    }
    return distance;
}

int run() {
    cin >> n;
    for (int i = 0; i < n; i++) adj.push_back(vector<int> (n, INT_MAX));
    int m;
    cin >> m;
    while (m--) {
        int from, to, weight;
        cin >> from >> to >> weight;
        //undirected edge
        adj[from][to] =  weight;
        adj[to][from] = weight;
    }
    //no self loops, so adj[i][i] = 0, fill diagonal
    for (int i = 0; i < n; i++) adj[i][i] = 0;
    for (vector<int> i : floydWarshall()) {
        for (int j : i) cout << j << " ";
        cout << endl;
    }
}

