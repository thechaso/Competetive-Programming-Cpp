#include <bits/stdc++.h>
using namespace std;
#define ll long long

//Eulerian paths and circuits directed graph

int n, m;
vector<vector<int>> adj;
vector<int> in, out;
int start;
stack<int> eulerPath;

bool hasEularianPath()
{
    //fill out in and out degrees of each node
    for (int from = 0; from < n; from++) {
        for (int to : adj[from]) {
            in[to]++;
            out[from]++;
        }
    }
    int startNodes = 0, endNodes = 0;
    for (int i = 0; i< n; i++) {
        if (out[i] - in[i] > 1 || in[i] - out[i] > 1) return false;
        else if (out[i] - in[i] == 1) startNodes++;
        else if (in[i] - out[i] == 1) endNodes++;
    }
    return (startNodes == 0 && endNodes == 0) || (startNodes == 1 && endNodes == 1);
}

void findStartNode()
{
    for (int i = 0; i < n; i++) {
        if (out[i] - in[i] == 1) {
            start = i;
            return;
        }
        else if (out[i] > 0) start = i;
    }
}

//fill out eulerPath stack
void dfs(int cur)
{
   while (out[cur] != 0) {
        int neighbor = adj[cur][--out[cur]];
        dfs(neighbor);
   }
   eulerPath.push(cur);
}

int main()
{
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        adj.push_back({});
        in.push_back(0);
        out.push_back(0);
    }
    for (int i = 0; i < m; i++) {
        int from, to;
        cin >> from >> to;
        //directed edge
        adj[from].push_back(to);
    }
    if (hasEularianPath()) {
        findStartNode();
        dfs(start);
        if (eulerPath.size() == (m + 1)) {
            int endNode = start;
            while (!eulerPath.empty()) {
                if (eulerPath.size() == 1) endNode = eulerPath.top();
                cout << eulerPath.top() << " ";
                eulerPath.pop();
            }
            cout << endl;
            if (start == endNode) cout << "This is also an Eulerian Circuit";
        }
        else cout << "No Eulerian Path for whole graph, too many connected components";
    }
    else cout << "No Eulerian Path Found on Graph";
}

