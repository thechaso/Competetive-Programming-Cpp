#include <bits/stdc++.h>
using namespace std;
#define ll long long

int n;
//adj contains {to, weight}
vector<vector<pair<int, int>>> adj;

//O(n + m*log(m))
void prims()
{
    int source = 0;
    int cost = 0;
    vector<int> key(n, INT_MAX);
    vector<int> parent(n, -1);
    vector<bool> inMST(n, false);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, source});
    key[source] = 0;
    while (!pq.empty()) {
        pair<int, int> t = pq.top();
        pq.pop();
        int cur = t.second;
        inMST[cur] = true;
        for (pair<int, int> to: adj[cur]) {
            int neighbor = to.first, weight = to.second;
            if (!inMST[neighbor] && key[neighbor] > weight) {
                cost += weight;
                key[neighbor] = weight;
                pq.push({key[neighbor], neighbor});
                parent[neighbor] = cur;
            }
        }
    }
    cout << cost << endl;
    for (int i = 0; i < n; i++) cout << parent[i] << " - " << i << endl;
}

int main()
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
        //undirected edge
        adj[from].push_back({to, weight});
        adj[to].push_back({from, weight});
    }
    prims();
}

