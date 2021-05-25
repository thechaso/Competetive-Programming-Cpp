#include <bits/stdc++.h>
using namespace std;
#define ll long long

int n, q;
vector<int> parent;
const int LOG = 20;
vector<vector<int>> up;
vector<int> depth;

int kth_ancestor(int x, int k)
{
    for (int i = 0; i < LOG; i++) {
        if (k & (1 << i)) {//if ith bit is turned on it will contribute 2^j sum
            x = up[x][i];
        }
    }
    return x;
}

int main()
{
    cin >> n >> q;
    parent.resize(n);
    up = vector<vector<int>> (n, (vector<int> (LOG)));
    depth.resize(n);
    parent[0] = 0;
    for (int i = 1; i < n; i++) {
        int p;
        cin >> p;
        p--;
        parent[i] = p;
    }
    //build sparse table
    for (int i = 0; i < n; i++) {
        up[i][0] = parent[i];
        if (i) depth[i] = depth[parent[i]] + 1;
        for (int j = 1; j < LOG; j++) {
            up[i][j] = up[up[i][j - 1]][j - 1];
        }
    }
    while (q--) {
        int x, k;
        cin >> x >> k;
        x--;
        if (depth[x] < k) cout << -1 << "\n";
        else cout << kth_ancestor(x, k) + 1 << "\n";
    }
}

