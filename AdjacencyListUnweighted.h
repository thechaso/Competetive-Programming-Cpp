#include <bits/stdc++.h>
using namespace std;

int n;
vector<vector<int>> adj;

void printAdj()
{
    for (int i = 0; i < n; i++) {
        cout << i << ": ";
        for (int j : adj[i]) cout << j << " ";
        cout << endl;
    }
}

void dfsReucrsion(int cur, int destination, vector<bool>& visited, bool& res)
{
    if (visited[cur]) return;
    if (cur == destination) {
        res = true;
        return;
    }
    visited[cur] = true;
    vector<int> neighbors = adj[cur];
    for (int neighbor : neighbors) {
        dfsReucrsion(neighbor, destination, visited, res);
    }
}

bool hasPathDFS_recursion(int source, int destination)
{
    vector<bool> visited(n, false);
    bool res = false;
    dfsReucrsion(source, destination, visited, res);
    return res;
}

bool hasPathDFS_stack(int source, int destination)
{
    vector<bool> visited(n, false);
    stack<int> s;
    visited[source] = true;
    s.push(source);
    while (!s.empty()) {
        int cur = s.top();
        s.pop();
        if (cur == destination) return true;
        vector<int> neighbors = adj[cur];
        for (int neighbor : neighbors) {
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                s.push(neighbor);
            }
        }
    }
    return false;
}

void numCompsUtil_dfs(int node, vector<bool>& visited)
{
    stack<int> s;
    visited[node] = true;
    s.push(node);
    while (!s.empty()) {
        int cur = s.top();
        s.pop();
        vector<int> neighbors = adj[cur];
        for (int neighbor : neighbors) {
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                s.push(neighbor);
            }
        }
    }
}

int numComponents()
{
    int res = 0;
    vector<bool> visited(n, false);
    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            numCompsUtil_dfs(i, visited);
            res++;
        }
    }
    return res;
}

int sizeOfSpecificComp(int source, vector<bool>& visited)
{
    int res = 0;
    stack<int> s;
    visited[source] = true;
    s.push(source);
    res++;
    while (!s.empty()) {
        int cur = s.top();
        s.pop();
        vector<int> neighbors = adj[cur];
        for (int neighbor : neighbors) {
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                s.push(neighbor);
                res++;
            }
        }
    }
    return res;
}

vector<int> sizeOfComps()
{
    vector<int> res;
    vector<bool> visited(n, false);
    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            res.push_back(sizeOfSpecificComp(i, visited));
        }
    }
    return res;
}

void printAllPaths_dfs(int source, int destination, vector<bool> visited, string path, vector<string>& ans)
{
    if (cur == destination) {
        ans.push_back(path);
        return;
    }
    visited[cur] = true;
    for (int neighbor : adj[cur]) {
        if (!visited[neighbor]) {
            visited[neighbor] = true;
            dfs(neighbor, destination, visited, path + to_string(neighbor), ans);
            visited[neighbor] = false;
        }
    }
}

void printAllPaths(int source, int destination)
{
    vector<bool> visited(n, false);
    vector<string> ans;
    printAllPaths_dfs(source, destination, visited, to_string(source), ans);
    for (string path : ans) {
        cout << path << endl;
    }
}

vector<int> getSpecificComp(int source, vector<bool>& visited) {
    vector<int> nodes;
    stack<int> s;
    visited[source] = true;
    s.push(source);
    nodes.push_back(source);
    while (!s.empty()) {
        int cur = s.top();
        s.pop();
        for (int neighbor : adj[cur]) {
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                s.push(neighbor);
                nodes.push_back(neighbor);
            }
        }
    }
    sort(nodes.begin(), nodes.end());
    return nodes;
}

void printComps() {
    vector<vector<int>> ans;
    vector<bool> visited(n, false);
    for (int node = 0; node < n; node++) {
        if (!visited[node]) {
            vector<int> v = getSpecificComp(node, visited);
            ans.push_back(v);
        }
    }

    string s = "[";
    for (vector<int> i : ans) {
        s += "[";
        for (int j : i) s += (to_string(j) + ", ");
        s.pop_back();
        s.pop_back();
        s += "], ";
    }
    s.pop_back();
    s.pop_back();
    s += "]";
    cout << s;
}

bool hasCycle_dfs(int source, vector<bool>& visited) {
    stack<int> s;
    s.push(source);
    visited[source] = true;
    int prev = source;
    while (!s.empty()) {
        int cur = s.top();
        s.pop();
        for (int neighbor : adj[cur]) {
            if (visited[neighbor] && neighbor != prev) {
                return true;
            }
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                s.push(neighbor);
                prev = cur;
            }
        }
    }
    return false;
}

bool hasCycle() {
    vector<bool> visited(n, false);
    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            bool cycle = hasCycle_dfs(i, visited);
            if (cycle) return true;
        }
    }
    return false;
}

vector<string> color;

string getColor(string s) {
    if (s == "r") return "b";
    return "r";
}

bool bipartite_dfs(int source, vector<bool>& visited) {
    visited[source] = true;
    stack<int> s;
    s.push(source);
    while (!s.empty()) {
        int cur = s.top();
        s.pop();
        for (int neighbor : adj[cur]) {
            if(visited[neighbor]) {
                if (color[neighbor] == color[cur]) {
                    return false;
                }
            }
            else {
                if (color[neighbor] == "u") {
                    color[neighbor] = getColor(color[cur]);
                }
                else if (color[neighbor] == color[cur]) {
                    return false;
                }
                s.push(neighbor);
                visited[neighbor] = true;
            }
        }
    }
    return true;
}
bool isBipartite() {
    vector<bool> visited(n, false);
    for (int i = 0; i < n; i++) color.push_back("u");
    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            color[i]=  "b";
            bool res = bipartite_dfs(i, visited);
            if (!res) return false;
        }
    }
    return true;
}

int shortestPathBFS(int source, int destination)
{
    queue<int> q;
    vector<bool> visited(n, false);
    vector<int> distance(n, -1);
    q.push(source);
    visited[source] = true;
    distance[source] = 0;
    bool isConnected = false;
    while (!q.empty()) {
        int cur = q.front();
        q.pop();
        if (cur == destination) isConnected = true;
        vector<int> neighbors = adj[cur];
        for (int neighbor : neighbors) {
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                q.push(neighbor);
                if (distance[neighbor] == -1) distance[neighbor] = distance[cur] + 1;
                else distance[neighbor] = min(distance[neighbor], distance[cur] + 1);
            }
        }
    }
    if (isConnected) {
        int res = distance[destination];
        if (!res) cout << "Nodes not connected" << endl;
        else return res;
    }
}

int run()
{
    cout << "Number of nodes and edges: " << endl;
    cin >> n;
    for (int i = 0; i < n; i++) adj.push_back({});
    int m;
    cin >> m;
    cout << "Enter edges: " << endl;
    while (m--) {
        int from, to;
        cin >> from >> to;
        adj[from].push_back(to);
        adj[to].push_back(from);
    }
    cout << "Source and Destination: " << endl;
    int source, destination;
    cin >> source >> destination;
    cout << "Adjacency list: " << endl;
    printAdj();
    cout << "has path dfs recursion: ";
    if (hasPathDFS_recursion(source, destination)) cout << "true" << endl;
    else cout << "false" << endl;
    cout << "has path dfs stack: ";
    if (hasPathDFS_stack(source, destination)) cout << "true" << endl;
    else cout << "false" << endl;
    cout << "All paths from " << source << " to " << destination << ": " <<  endl;
    printAllPaths(source, destination);
    cout << "Number of connected components: " << numComponents() << endl;
    cout << "Size of each component: ";
    for (int i : sizeOfComps()) cout << i << " ";
    cout << endl;
    cout << "shortest path from " << source << " to " << destination << ": ";
    cout << shortestPathBFS(source, destination) << endl;
    cout << "Graph contains cycle: ";
    bool cycle = hasCycle();
    if (cycle) cout << "true";
    else cout << "false";
    cout << endl;
    cout << "Graph is Bipartite: ";
    bool bipartite = isBipartite();
    if (bipartite) cout << "true";
    else cout << "false";
    cout << endl;
}
