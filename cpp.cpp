#include <bits/stdc++.h>
#define int long long
#define INF 0x3F3F3F3F3F3F3FLL
using namespace std;
// #include <ext/pb_ds/assoc_container.hpp>
// #include <ext/pb_ds/tree_policy.hpp>
// using namespace __gnu_pbds;
// template <class T>
// using pbds = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

// find_by_order , order_of_key

/**
 * problem link - https://atcoder.jp/contests/abc350/tasks/abc350_e
 * this is an expected value kind of sum (probabilites and mean) 
**/

const int mod = 1e9 + 7;

void solve() {
	cout << fixed << setprecision(10);
	int n, a, x, y;
	cin >> n >> a >> x >> y;

	map<int, double> dp;
	function<double(int)> fun = [&](int n) -> double {
		if (n == 0) return 0;
		if (dp.count(n)) return dp[n];
		double ans = x + fun(n / a);
		double tot = 0;
		for (int i = 2; i <= 6; i++) {
			tot += fun(n / i);
		}
		ans = min(ans, tot / 5 + 6.0 / 5 * y);
		return dp[n] = ans;
	};
	cout << fun(n) << "\n";
}

signed main() {
	ios_base::sync_with_stdio(0);
	cin.tie(NULL);
	int tt = 1;
	// cin >> tt;
	while (tt--) {
		solve();
	}
	return 0;
}