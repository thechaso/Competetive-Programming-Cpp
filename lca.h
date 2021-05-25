#include <bits/stdc++.h>
using namespace std;
#define ll long long

int n, q;
const int LOG = 20;
vector<int> parent;
vector<vector<int>> up; //up[x][k] is the 2^kth ancestor of node x
vector<int> depth;

int lca(int a, int b)
{
    if (depth[a] < depth[b]) swap(a, b);
    int k = depth[a] - depth[b];
    //find kth ancestor of a so that depth[a] = depth[b]
    for (int i = LOG - 1; i >= 0; i--) {
        if (k & (1 << i)) {
            a = up[a][i];
        }
    }
    if (a == b) return a;
    //check the 2^i th ancestor for i in (LOG, 0] and check if this ancestor is same for a and b
    //if so we are jumping over lca, so if they are not equal, they are children of lca
    for (int i = LOG - 1; i >= 0; i--) {
        if (up[a][i] != up[b][i]) {
            a = up[a][i];
            b = up[b][i];
        }
    }
    return parent[a];
}

int main()
{
    cin >> n >> q;
    parent.resize(n);
    up = vector<vector<int>> (n, (vector<int> (LOG)));
    depth.resize(n);
    for (int i = 1; i < n; i++) {
        int p;
        cin >> p;
        p--;
        parent[i] = p;
    }
    parent[0] = 0;
    depth[0] = 0;
    for (int i = 0; i < n; i++) {
        up[i][0] = parent[i];
        if (i) depth[i] = depth[parent[i]] + 1;
        for (int j = 1; j < LOG; j++) {
            up[i][j] = up[up[i][j - 1]][j - 1];//2^(j - 1) * 2 = 2^j th ancestor
        }
    }
    while (q--) {
        int a, b;
        cin >> a >> b;
        a--; b--;
        cout << lca(a, b) + 1 << "\n";
    }
}

