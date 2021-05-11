#include <bits/stdc++.h>
using namespace std;
#define ll long long

int n, m;
vector<vector<int>> adj;
vector<vector<int>> revAdj;
vector<bool> visited_1, visited_2;
stack<int> s;
vector<int> who;
vector<vector<int>> compGraph;
int numComps;

void dfs_1_util(int cur)
{
    visited_1[cur] = true;
    for (int neighbor : adj[cur]) {
        if (!visited_1[neighbor]) {
            dfs_1_util(neighbor);
        }
    }
    s.push(cur);
}

void dfs_1()
{
    for (int i = 0; i < n; i++) {
        if (!visited_1[i]) {
            dfs_1_util(i);
        }
    }
}

void dfs_2(int cur, vector<int>& component, int rep)
{
    who[cur] = rep;
    component.push_back(cur);
    visited_2[cur] = true;
    for (int neighbor : revAdj[cur]) {
        if (!visited_2[neighbor]) {
            dfs_2(neighbor, component, rep);
        }
    }
}

void kosaraju()
{
    vector<vector<int>> scc;
    while (!s.empty()) {
        int cur = s.top();
        s.pop();
        if (!visited_2[cur]) {
            numComps++;
            vector<int> component;
            dfs_2(cur, component, cur);
            scc.push_back(component);
        }
    }
    cout << "There are " << numComps << " SCCs" << endl;
    cout << "Strongly Connected Components are: " << endl;
    for (vector<int> i : scc) {
        for (int j : i) cout << j << " ";
        cout << endl;
    }
    cout << "Representative node of each node: " << endl;
    for (int i : who) cout << i << " ";
    cout << endl;
}

void compressGraph()
{
    for (int from = 0; from < n; from++) {
        for (int to : adj[from]) {
            if (who[from] != who[to]) {
                compGraph[who[from]].push_back(who[to]);
            }
        }
    }
    cout << "Compressed Graph based on SCCs: " << endl;
    for (int from = 0; from < n; from++) {
        cout << from << ": ";
        for (int to : compGraph[from]) cout << to << " ";
        cout << endl;
    }
}

int run()
{
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        adj.push_back({});
        revAdj.push_back({});
        visited_1.push_back(false);
        visited_2.push_back(false);
        who.push_back(i);
        compGraph.push_back({});
    }
    for (int i = 0; i < m; i++) {
        int from, to;
        cin >> from >> to;
        //directed edge;
        adj[from].push_back(to);
        revAdj[to].push_back(from);
    }
    dfs_1();
    kosaraju();
    compressGraph();
}

