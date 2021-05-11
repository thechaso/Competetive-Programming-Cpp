#include <bits/stdc++.h>
using namespace std;
#define ll long long

vector<vector<int>> add(vector<vector<int>> a, vector<vector<int>> b)
{
    //assuming a and b have same dimensions
    for (int i = 0; i < a.size(); i++) {
        for (int j = 0; j < a[0].size(); j++) {
            a[i][j] += b[i][j];
        }
    }
    return a;
}

vector<vector<int>> matrixMultiplication(vector<vector<int>> a, vector<vector<int>> b)
{
    int ar = a.size(), ac = a[0].size(), br = b.size(), bc = b[0].size();
    if (ac != br) {
        cout << "Matrices cannot be multiplied";
        return {{}};
    }
    vector<vector<int>> ans(ar, (vector<int> (bc)));
    for (int i = 0; i < ans.size(); i++) {
        for (int j = 0; j < ans[0].size(); j++) {
            //row and col have the same size since ac and br have same size
            int res = 0;
            for (int k = 0; k < ac; k++) {
                res += (a[i][k] * b[k][j]);
            }
            ans[i][j] = res;
        }
    }
    return ans;
}

bool isIdentityMatrix(vector<vector<int>> m)
{
    for (int i = 0; i < m.size(); i++) {
        if (m[i][i] != 1) return false;
    }
    return true;
}

//matrix powers only apply to square matrices
vector<vector<int>> matrixPower(vector<vector<int>> m, int exp)
{
    if (exp == 0) {
        vector<vector<int>> ans(m.size(), (vector<int>(m.size(), 0)));
        for (int i = 0; i < m.size(); i++) ans[i][i] = 1;
        return ans;
    }
    vector<vector<int>> ans = m;
    for (int i = 1; i < exp; i++) {
        ans = matrixMultiplication(ans, m);
    }
    return ans;
}

//return the number of paths from nodes i to j of length k in matrix
//S.T. matrix[i][j] = ans
vector<vector<int>> numberPaths(vector<vector<int>> adj, int k)
{
    adj = matrixPower(adj, k);
    return adj;
}

vector<vector<int>> matrixMin(vector<vector<int>> a, vector<vector<int>> b)
{
    int ar = a.size(), ac = a[0].size(), br = b.size(), bc = b[0].size();
    if (ac != br) {
        cout << "Matrices cannot be multiplied";
        return {{}};
    }
    vector<vector<int>> ans(ar, (vector<int> (bc)));
    for (int i = 0; i < ans.size(); i++) {
        for (int j = 0; j < ans[0].size(); j++) {
            //row and col have the same size since ac and br have same size
            int res = 0;
            for (int k = 0; k < ac; k++) {
                //res += (a[i][k] * b[k][j]);
                res = min(res, a[i][k] + b[k][j]);
            }
            ans[i][j] = res;
        }
    }
    return ans;
}

//matrix powers only apply to square matrices
vector<vector<int>> matrixMinPower(vector<vector<int>> m, int exp)
{
    if (exp == 0) {
        vector<vector<int>> ans(m.size(), (vector<int>(m.size(), 0)));
        for (int i = 0; i < m.size(); i++) ans[i][i] = 1;
        return ans;
    }
    vector<vector<int>> ans = m;
    for (int i = 1; i < exp; i++) {
        ans = matrixMin(ans, m);
    }
    return ans;
}

//return the shortest of paths from nodes i to j of length k in matrix
//S.T. matrix[i][j] = ans
vector<vector<int>> shortestPaths(vector<vector<int>> adj, int k)
{
    adj = matrixMinPower(adj, k);
    return adj;
}


vector<vector<int>> createUnweighted_AdjMatrix()
{
    int n, m;
    cin >> n >> m;
    //adj matrix 1 means there is direct edge
    vector<vector<int>> adj(n, (vector<int>(n)));
    while (m--) {
        int from, to;
        cin >> from >> to;
        //directed edge
        adj[from][to] = 1;
        //adj[to][from] = 1;
    }
    /*
    for (auto i : adj) {
        for (int j : i) cout << j << " ";
        cout << endl;
    }
    */
    return adj;
}

vector<vector<int>> createWeightd_AdjMatrix()
{
    int n, m;
    cin >> n >> m;
    //adj matrix 1 means there is direct edge
    vector<vector<int>> adj(n, (vector<int>(n, INT_MAX)));
    while (m--) {
        int from, to, weight;
        cin >> from >> to >> weight;
        //directed edge
        adj[from][to] = weight;
        //adj[to][from] = 1;
    }
    /*
    for (auto i : adj) {
        for (int j : i) cout << j << " ";
        cout << endl;
    }
    */
    return adj;
}

/*
6
8
0 3 4
1 0 2
1 4 1
1 5 2
2 1 4
3 1 1
5 2 3
5 4 2
*/


