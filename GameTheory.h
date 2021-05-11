#include <bits/stdc++.h>
using namespace std;
#define ll long long

//given n piles, and m different choices determine if the current n
//is a winning state or loosing state
void coin_pile_game()
{
    int maxN = 1e9;
    //true is winning state and false is losing state
    vector<bool> state(maxN);
    int n;
    cin >> n;
    //ex. choices = {1, 2, 3}
    int m;
    cin >> m;
    vector<int> choice(m);
    for (int i = 0; i < m; i++) cin >> choice[i];
    state[0] = false;
    for (int i = 1; i <= n; i++) {
        bool b = false;
        for (int c : choice) {
            int prev = i - c;
            if (prev >= 0 && !state[prev] && !b) {
                state[i] = true;
                b = true;
                continue;
            }
        }
        if (!b) state[i] = false;
    }
    if (state[n]) cout << "Winning state";
    else cout << "Losing state";
}

//given n piles of sticks each with stack[i] sticks
//we can choose any number of sticks from it S.T. player to choose
//last stick wins
//return if this is a losing state or winning state
void nim_game()
{
    int n;
    cin >> n;
    vector<int> stick(n);
    for (int i = 0; i < n; i++) cin >> stick[i];
    int nim_sum = stick[0];
    for (int i = 1; i < n; i++) {
        nim_sum ^= stick[i];
    }
    if (nim_sum == 0) cout << "Losing state";
    else cout << "Winning State";
}

