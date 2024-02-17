#include <bits/stdc++.h>
#define ll long long
using namespace std;

/** 
 * cses problem -> https://cses.fi/problemset/task/1647
 * it involves use of sparse tables
*/

void solve() {
	ll n, q;
	cin >> n >> q;
	vector<ll>arr(n);
	for (ll i = 0; i < n; i++) {
		cin >> arr[i];
	}

	// calculate the log of n 
	ll N = 0;
	while (1ll << (N + 1ll) <= n) {
		N++;
	}
	

	// preprocessing -> creating the sparse table 
	// dp[i][j] -- minimum of a segment starting at index i and of length (1 << j)
	vector<vector<ll>> dp(n, vector<ll>(N + 1));
	for (ll i = 0; i < n; i++) {
		dp[i][0] = arr[i];
	} 
	for (ll j = 1; j <= N; j++) {
		for (ll i = 0; (i + (1 << (j - 1))) < n; i++) {
			dp[i][j] = min(dp[i][j - 1], dp[i + (1 << (j - 1))][j - 1]);
		}
	}
	
	while (q--) {
		ll l, r;
		cin >> l >> r;
		
		// 0 based indexing 
		l--;
		r--;
		
		ll len = r - l + 1;
		ll k = 0;
		while (1ll << (k + 1ll) < len) {
			k++;
		}
		ll ans = min(dp[l][k], dp[r - (1 << k) + 1][k]);
		cout << ans <<  "\n";
	}
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
