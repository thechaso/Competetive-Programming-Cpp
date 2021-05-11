#include <iostream>
#include <vector>
#include <stack>
#include <queue>
using namespace std;

vector<vector<int>> createGraph(int n) {
    vector<vector<int>> graph;
    for (int i = 0; i < n; i++) {
        vector<int> newVector;
        graph.push_back(newVector);
    }
    return graph;
}

vector<vector<int>> addEdge(vector<vector<int>> graph, int v1, int v2)  {
    graph[v1].push_back(v2);
    graph[v2].push_back(v1);
    return graph;
}

void printGraph(vector<vector<int>> graph) {
    for (vector<int> i : graph) {
        cout << "[";
        for (int j : i) {
            cout << j << " ";
        }
        cout << "]" << endl;
    }
}

bool DFSUtil(vector<vector<int>> graph, int source, int destination, vector<bool> visited) {
    if (source == destination) return true;
    vector<int> neighbors = graph[source];
    for (int neighbor : neighbors) {
        if (!visited[neighbor]) {
            visited[neighbor] = true;
            bool isConncted = DFSUtil(graph, neighbor, destination, visited);
            if (isConncted) return true;
        }
    }
    return false;
}

bool hasPathDFS(vector<vector<int>> graph, int source, int destination) {
    vector<bool> visited;
    for (int i = 0; i < graph.size(); i++) visited.push_back(false);
    visited[source] = true;
    return DFSUtil(graph, source, destination, visited);
}

bool hasPathDFS_Stack(vector<vector<int>> graph, int source, int destination) {
    vector<bool> visited;
    for (int i = 0; i < graph.size(); i++) visited.push_back(false);
    stack<int> s;
    visited[source] = true;
    s.push(source);
    while (!s.empty()) {
        int curNode = s.top();
        s.pop();
        if (curNode == destination) return true;
        vector<int> neighbors = graph[curNode];
        for (int neighbor : neighbors) {
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                s.push(neighbor);
            }
        }
    }
    return false;
}

vector<bool> getConnectedCompsUtil(vector<vector<int>> graph, int source, vector<bool> visited) {
    stack<int> s;
    visited[source]=  true;
    s.push(source);
    while (!s.empty()) {
        int curNode = s.top();
        s.pop();
        vector<int> neighbors = graph[curNode];
        for (int neighbor : neighbors) {
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                s.push(neighbor);
            }
        }
    }
    return visited;
}

int getConnectedComps(vector<vector<int>> graph) {
    int numComps = 0;
    vector<bool> visited;
    for (int i = 0; i < graph.size(); i++) visited.push_back(false);
    for (int i = 0; i < graph.size(); i++) {
        if (!visited[i]) {
            visited = getConnectedCompsUtil(graph, i, visited);
            numComps++;
        }
    }
    return numComps;
}

pair<int, vector<bool>> sizeOfSpecificComp(vector<vector<int>> graph, int curNode, vector<bool> visited) {
    int compSize = 0;
    stack<int> s;
    visited[curNode] = true;
    s.push(curNode);
    compSize++;
    while (!s.empty()) {
        int cur = s.top();
        s.pop();
        vector<int> neighbors = graph[cur];
        for (int neighbor : neighbors) {
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                s.push(neighbor);
                compSize++;
            }
        }
    }
    pair<int, vector<bool>> p = make_pair(compSize, visited);
    return p;
}



vector<int> getSizeOfConnectdComps(vector<vector<int>> graph) {
    vector<bool> visited;
    for (int i = 0; i < graph.size(); i++) visited.push_back(false);
    vector<int> sizeComps;
    for (int i = 0; i < graph.size(); i++) {
        if (!visited[i]) {
            pair<int, vector<bool>> p = sizeOfSpecificComp(graph, i, visited);
            sizeComps.push_back(p.first);
            visited = p.second;
        }
    }
    return sizeComps;
}

vector<int> getIndegree(vector<vector<int>> graph) {
    vector<int> in;
    for (int i = 0; i < graph.size(); i++) in.push_back(0);
    for (int from = 0; from < graph.size(); from++) {
        vector<int> neighbors = graph[from];
        for (int to : neighbors) {
            in[to]++;
        }
    }
    return in;
}

vector<int> getOutDegree(vector<vector<int>> graph) {
    vector<int> out;
    for (int i = 0; i < graph.size(); i++) out.push_back(0);
    for (int from = 0; from < graph.size(); from++) {
        vector<int> neighbors = graph[from];
        int numOutEdges = neighbors.size();
        out[from] += numOutEdges;
    }
    return out;
}

int shortestPathBFS(vector<vector<int>> graph,  int source, int destination) {
    vector<bool> visited;
    for (int i = 0; i < graph.size(); i++) visited.push_back(false);
    queue<int> q;
    vector<int> parent;
    for (int i = 0; i < graph.size(); i++) parent.push_back(NULL);
    visited[source] = true;
    q.push(source);
    parent[source] = -1;
    while (!q.empty()) {
        int curNode = q.front();
        q.pop();
        if (curNode == destination) break;
        vector<int> neighbors = graph[curNode];
        for (int neighbor : neighbors) {
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                q.push(neighbor);
                parent[neighbor] = curNode;
            }
        }
    }
    int distance = 0;
    int curNode = destination;
    while (parent[curNode] != -1) {
        curNode = parent[curNode];
        distance++;
    }
    return distance;
}

int run() {
    int n;
    int e;
    cout << "Number of Nodes: ";
    cin >> n;
    cout << "Number of Edges: ";
    cin >> e;
    cout << "Enter " << e << " edges: " << endl;
    vector<vector<int>> graph = createGraph(n);
    for (int i = 0; i < e; i++) {
        int v1;
        int v2;
        cin >> v1;
        cin >> v2;
        graph = addEdge(graph, v1, v2);
    }
    cout << "Enter Source and Destination: " << endl;
    int source;
    int destination;
    cin >> source >> destination;

    printGraph(graph);

    bool hasPath = hasPathDFS_Stack(graph, source, destination);
    if (hasPath) cout << "The source and destination are connected" << endl;
    else cout << "The source and the destination are not connected" << endl;

    int numComps = getConnectedComps(graph);
    cout << "Number of connected components: " << numComps << endl;

    vector<int> sizeComps = getSizeOfConnectdComps(graph);
    cout << "Size of each connected component: " << endl;
    for (int i : sizeComps) cout << i << " ";
    cout << endl;

    vector<int> in = getIndegree(graph);
    vector<int> out = getOutDegree(graph);
    cout << "In degree of each node: " << endl;
    for (int i : in) cout << i << " ";
    cout << endl;
    cout << "Out degree of each node: " << endl;
    for (int i : out) cout << i <<  " ";
    cout << endl;

    int shortestPath = shortestPathBFS(graph, source, destination);
    cout << "Shortest Path from source node to destination node is: " << shortestPath << endl;
}


