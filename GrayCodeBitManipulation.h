#include <bits/stdc++.h>
using namespace std;
#define ll long long

int binaryStringToInt(string binary)
{
    int n = stoi(binary, 0, 2);
    return n;
}

vector<string> grayCode(int n)
{
    if (n == 1) {
        vector<string> baseCase = {"0", "1"};
        return baseCase;
    }
    vector<string> prev = grayCode(n - 1);
    vector<string> cur;
    for (string i : prev) {
        cur.push_back("0" + i);
    }
    for (int i = prev.size() - 1; i >= 0; i--) {
        cur.push_back("1" + prev[i]);
    }
    return cur;
}

int main() {
    int n;
    cin >> n;
    vector<string> codes = grayCode(n);
    for (string i : codes) cout << i << " = " << binaryStringToInt(i) << endl;
}

