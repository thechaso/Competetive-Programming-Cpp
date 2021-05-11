#include <bits/stdc++.h>
using namespace std;
#define ll long long

vector<int> tree;

int query(int node, int node_low, int node_high, int query_low, int query_high)
{
    if ((query_low <= node_low) && (node_high <= query_high)) return tree[node];
    if ((node_high < query_low) || (node_low > query_high)) return INT_MAX;
    int mid = (node_low + node_high) / 2;
    int left = query(node  * 2, node_low, mid, query_low, query_high);
    int right = query(node * 2 + 1, mid + 1, node_high, query_low, query_high);
    return min(left, right);
}

int main()
{
    int n, q;
    cin >> n >> q;
    vector<int> arr(n);
    for (int i = 0; i < n; i++) cin >> arr[i];

    //build tree
    while (__builtin_popcount(n) != 1) {
        arr.push_back(INT_MAX);
        n++;
    }
    tree.resize(2 * n);
    fill(tree.begin(), tree.end(), INT_MAX);
    //fill in leaf nodes
    for (int i = 0; i < n; i++) tree[n + i] = arr[i];
    //bottom up traversal to populate tree
    for (int i = n - 1; i >= 1; i--) {
        tree[i] = min(tree[2 * i], tree[2 * i + 1]);
    }

    //answer queries
    while (q--) {
        string op;
        cin >> op;
        if (op == "query") {
            int query_low, query_high;
            cin >> query_low >> query_high;
            cout << query(1, 0, n - 1, query_low, query_high);
        }
    }
}

