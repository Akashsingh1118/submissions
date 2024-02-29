#include <bits/stdc++.h>
#define ll long long
using namespace std;
// #include <ext/pb_ds/assoc_container.hpp>
// #include <ext/pb_ds/tree_policy.hpp>
// using namespace __gnu_pbds;
// typedef tree<ll, null_type, less_equal<ll>, rb_tree_tag, tree_order_statistics_node_update> pbds;

// find_by_order , order_of_key

/**
 * problem link - https://cses.fi/problemset/task/2220
 * it involves digit dp concepts
*/
const ll mod = 1e9+7;
 
ll dp[20][2][11][2];
ll fun(string& s, int n, bool tight, int prev, bool lead) {
	if (n == 0) return 1;
	if (dp[n][tight][prev][lead] != -1) return dp[n][tight][prev][lead];
	ll ub = tight ? (s[s.size() - n] - '0') : 9;
	ll ans = 0;
	for (ll i = 0; i <= ub; i++) {
		if (i == prev && lead == 0) continue;
		ans += fun(s, n - 1, tight & (i == ub), i, lead & (i == 0));
	}
	return dp[n][tight][prev][lead] = ans;
}
 
void solve() {
	ll n1, n2;
	cin >> n1 >> n2;
	n1--;
	string s1 = to_string(n1);
	string s2 = to_string(n2);
	memset(dp, -1, sizeof dp);
	ll l = fun(s1, s1.size(), 1, 0, 1);
	memset(dp, -1, sizeof dp);
	ll r = fun(s2, s2.size(), 1, 0, 1);
	ll ans = r - l;
	cout << ans << endl;
}
 
 
int main() {
	ios_base::sync_with_stdio(0);
    cin.tie(0);
	ll t = 1;
	// cin >> t;
	while (t--) {
		solve();
	}
}