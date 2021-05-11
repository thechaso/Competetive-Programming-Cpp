
#include <bits/stdc++.h>
using namespace std;
#define ll long long

//This is implemented using undirected edge list

int n, m;
//edge list will store {weight, source, destination}
vector<vector<int>> edges;
vector<int> component;
//ans edge list will store {source, destination, weight}
vector<vector<int>> ans;

//O(nm + m*log(m)) = O(n^2)
int kruskal()
{
    int cost = 0;
    sort(edges.begin(), edges.end());//sort edges by weight
    for (vector<int> edge : edges) {
        int weight = edge[0], from = edge[1], to = edge[2];
        if (component[from] != component[to]) {//check that there is no cycle
            cost += weight;//add to cost
            ans.push_back({from, to, weight});//create ans edge list
            int oldComp = component[from], newComp = component[to];
            //unite both components, make from node and all other nodes in its component
            //join to node's component
            for (int i = 0; i < n; i++) {
                if (component[i] == oldComp) {
                    component[i] = newComp;
                }
            }
        }
    }
    return cost;
}

int run()
{
    cin >> n >> m;
    for (int i = 0; i < n; i++) component.push_back(i);
    for (int i = 0; i < m; i++) {
        int from, to, weight;
        cin >> from >> to >> weight;
        edges.push_back({weight, from, to});
        edges.push_back({weight, to, from});
    }
    cout << "Minimum Spanning Tree" << endl << "Cost: " << kruskal() << endl;;
    cout << "Resulting Edge List: " << endl;
    for (vector<int> edge : ans) {
        for (int i : edge) cout << i << " ";
        cout << endl;
    }
}
