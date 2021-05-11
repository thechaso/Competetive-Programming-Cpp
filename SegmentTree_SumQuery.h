#include <bits/stdc++.h>
using namespace std;
#define ll long long

vector<int> tree;

int query(int node, int node_low, int node_high, int query_low, int query_high)
{
    //if  node is completely inside interval return sum
    if ((query_low <= node_low) && (node_high <= query_high)) return tree[node];
    //if node is disjoint, not even touching interval,return 0
    if ((node_low > query_high) || (node_high < query_low)) return 0;
    //recurse in left and right children if the node interval is partially inside query interval
    int mid = (node_low + node_high) / 2;
    int left_result = query(node * 2, node_low, mid, query_low, query_high);
    int right_result = query(node * 2 + 1, mid + 1, node_high, query_low, query_high);
    return left_result + right_result;
}

void point_update(int n, int index, int value)
{
    index += n;//get leaf node in tree
    tree[index] = value;
    while (index != 1) {
        int parent = index / 2;
        tree[parent] = tree[parent * 2] + tree[parent * 2 + 1];
        index = parent;
    }
    tree[1] += value;
}

void range_update(int node, int node_low, int node_high, int update_low, int update_high, int value)
{
    if ((update_low <= node_low) && (node_high <= update_high)) {
        tree[node] += value;
        return;
    }
    if ((node_low > update_high) || (node_high < update_low)) {
        return;
    }
    int mid = (node_low + node_high) / 2;
    range_update(node * 2, node_low, mid, update_low, update_high, value);
    range_update(node * 2 + 1, mid + 1, node_high, update_low, update_high, value);
    tree[node] = tree[node * 2] + tree[node * 2 + 1];
}

int run()
{
    int n, q;
    cin >> n >> q;
    vector<int> arr(n);
    for (int i = 0; i < n; i++) cin >> arr[i];
    //resize arr so that size is power of 2
    while (__builtin_popcount(n) != 1) {
        arr.push_back(0);
        n++;
    }
    //build tree
    //if there are n leaf nodes, then (2 * n) - 1 nodes in tree excluding tree[0]
    //number of nodes = 2^0 + 2^1 + 2^2 + ... + 2^(n-1) = 2^n - 1 nodes
    tree.resize(2 * n);
    for (int i = 0; i < n; i++) {
        tree[n + i] = arr[i];//copying array values for leaf nodes
    }
    for (int i = n - 1; i >= 1; i--) {
        tree[i] = tree[2 * i] + tree[2 * i + 1];
    }

    //answer queries
    while (q--) {
        string op;
        cin >> op;
        if (op == "query") {
            int query_low, query_high;
            cin >> query_low >> query_high;
            cout << query(1, 0, n - 1, query_low, query_high) << endl;
        }
        if (op == "point_update") {
            int index, value;
            cin >> index >> value;
            point_update(n, index, value);
            cout << "value updated" << endl;
        }
        if (op == "range_update") {
            int update_low, update_high, value;
            cin >> update_low >> update_high >> value;
            range_update(1, 0, n - 1, update_low, update_high, value);
            cout << "values updated" << endl;
        }
    }

}

