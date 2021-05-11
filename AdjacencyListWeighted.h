#include <bits/stdc++.h>
using namespace std;

int n;
vector<vector<pair<int, int>>> adj;
map<int, string> allPaths;
priority_queue<int, vector<int>, greater<int>> allWeights;

void dfs(int cur, int destination, vector<bool> visited, string path, int weight) {
    if (cur == destination) {
        allPaths[weight] = path;
        allWeights.push(weight);
        return;
    }
    visited[cur] = true;
    for (pair<int, int> neighbor : adj[cur]) {
        if (!visited[neighbor.first]) {
            visited[neighbor.first] = true;
            dfs(neighbor.first, destination, visited, path + to_string(neighbor.first), weight + neighbor.second);
            visited[neighbor.first] = false;
        }
    }
}


int main() {
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
        adj[from].push_back(make_pair(to, weight));
        adj[to].push_back(make_pair(from, weight));
    }
    int source, destination, criteria, k;
    cin >> source >> destination >> criteria >> k;
    vector<bool> visited(n, false);
    dfs(source, destination, visited, to_string(source), 0);
    pair<int, string> smallest = make_pair(allPaths.begin()->first, allPaths.begin()->second);
    pair<int, string> largest = make_pair(allPaths.begin()->first, allPaths.begin()->second);
    pair<int, string> justLarger = make_pair(allPaths.begin()->first, allPaths.begin()->second);
    bool jl = false;
    pair<int, string> justSmaller = make_pair(allPaths.begin()->first, allPaths.begin()->second);
    bool js = false;
    for (pair<int, string> p : allPaths) {
        int weight = p.first;
        string path = p.second;
        if (weight < smallest.first) {
            smallest = make_pair(weight, path);
        }
        if (weight > largest.first) {
            largest = make_pair(weight, path);
        }
        if (weight > criteria) {
            if (!jl) {
                justLarger = make_pair(weight, path);
                jl = true;
            }
            else if (weight < justLarger.first) {
                justLarger = make_pair(weight, path);
            }
        }
        if (weight < criteria) {
            if (!js) {
                justSmaller = make_pair(weight, path);
                js = true;
            }
            else if (weight > justSmaller.first) {
                justSmaller = make_pair(weight, path);
            }
        }
    }
    cout << "Smallest Path = " << smallest.second << "@" << smallest.first << endl;
    cout << "Largest Path = " << largest.second << "@" << largest.first << endl;
    cout << "Just Larger Path than " << criteria << " = " << justLarger.second << "@" << justLarger.first << endl;
    cout << "Just Smaller Path than " << criteria << " = " << justSmaller.second << "@" << justSmaller.first << endl;
    while (allWeights.size() > k) {
        allWeights.pop();
    }
    cout << k << "th largest path = " << allPaths[allWeights.top()] << "@" << allWeights.top() <<endl;
}

