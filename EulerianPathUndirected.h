#include <bits/stdc++.h>
using namespace std;
#define ll long long

int n, m;
vector<vector<int>> adj;
vector<int> deg;
int start;
stack<int> eulerPath;

bool hasEulerianPath()
{
    //fill in degrees of each node
    for (int from = 0; from < n; from++) {
        for (int to : adj[from]) {
            deg[from]++;
        }
    }
    //check for Eulerian path
    int odd = 0;
    for (int i = 0; i < n; i++) {
        if (deg[i] % 2 == 1) odd++;
    }
    return (odd == 0) || (odd == 2);
}

void findStartNode()
{
    for (int i = 0; i < n; i++) {
        if (deg[i] % 2 == 1) {
            start = i;
            return;
        }
        else start = i;
    }
}


void getEulerPath(int cur)
{
    while (deg[cur] != 0) {
        int neighbor = adj[cur][--deg[cur]];
        getEulerPath(neighbor);
    }
    eulerPath.push(cur);
}

int main()
{
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        adj.push_back({});
        deg.push_back(0);
    }
    for (int i = 0; i < m; i++) {
        int from, to;
        cin >> from >> to;
        //undirected edge
        adj[from].push_back(to);
        adj[to].push_back(from);
    }
    bool exists = hasEulerianPath();

    if (exists) {
        findStartNode();
        getEulerPath(start);
        if (true) {
            while (!eulerPath.empty()) {
                cout << eulerPath.top() +1 << " ";
                eulerPath.pop();
            }
        }
        else cout << "Too many connected components, cannot find Eulerian Path";
    }
    else cout << "No Eulerian Path Possible on this graph";
}

