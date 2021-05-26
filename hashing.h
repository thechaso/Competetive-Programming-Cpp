#include <bits/stdc++.h>
using namespace std;
#define ll long long

ll get_hash(string s)
{
    ll p = 31, power = 1, m = pow(10, 9) + 7, ans = 0;
    for (int i = 0; i < s.size(); i++) {
        ans = (ans + (s[i] - 'a' + 1) * power) % m;
        power *= p % m;
    }
    return ans % m;
}

ll inv_power(ll a , ll n)
{
	ll result = 1;
	ll mod = pow(10, 9) + 7;
	while(n)
	{
		if(n & 1) result = (result * a) % mod;
		n >>= 1;
		a = (a * a) % mod;
	}

	return result;
}

vector<ll> dp;
vector<ll> inv;
void init(string s)
{
    dp.resize(s.size());
    inv.resize(s.size());
    ll p = 31, m = pow(10, 9) + 7;
    ll power = 1;
    inv[0] = 1;
    dp[0] = (s[0] - 'a') + 1;
    for (int i = 1; i < s.size(); i++) {
        power *= p;
        power %= m;
        inv[i] = inv_power(power, m - 2);
        dp[i] = (dp[i - 1] + (s[i] - 'a' + 1) * power) % m;
    }
}

ll substring_hash(int l, int r)
{
    ll m = pow(10, 9) + 7;
    ll ans = dp[r];
    if (l) ans -= dp[l - 1];
    ans *= inv[l] % m;
    return ans % m;
}

int main()
{
    string txt, pat;
    cin >> txt >> pat;
    ll ph = get_hash(pat);
    init(txt);
    int l = 0, r = 0;
    string window = "";
    int n = txt.size(), k = pat.size();
    while (r < k) {
        window += txt[r];
        r++;
    }
    ll occ = 0;
    while (r < n) {
        //process window not including r
        ll sh = substring_hash(l, r - 1);
        if (sh == ph) {
            cout << l << " ";
            occ++;
        }
        window.erase(window.begin());
        window += txt[r];
        r++;
        l++;
    }
    //process window not including r
    ll sh = substring_hash(l, r - 1);
    if (sh == ph) {
        cout << l << " ";
        occ++;
    }
    cout << occ;
}

