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
 * Problem link - https://atcoder.jp/contests/abc348/tasks/abc348_e
 * This problem is solved based on a concept called "Tree Re-rooting"
 * I think my approach is not that much efficient but since this is my first of this kind, i am hoping
 * to write much more efficient codes than this
*/

const int mod = 1e9 + 7;


void solve() {
	int n;
	cin >> n;
	vector<int> adj[n + 1];
	for (int i = 0; i < n - 1; i++) {
		int u, v;
		cin >> u >> v;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
	vector<int> cost(n + 1);
	for (int i = 1; i <= n; i++) cin >> cost[i];

	vector<int> subsum(n + 1), root(n + 1);
	function<int(int, int)> dfs1 = [&](int node, int par) -> int {
		int now = 0;
		for (int i : adj[node]) {
			if (i == par) continue;
			now += dfs1(i, node);
		}
		return subsum[node] = now + cost[node];
	};
	function<int(int, int)> dfs2 = [&](int node, int par) -> int {
		for (int i : adj[node]) {
			if (i == par) continue;
			root[node] += dfs2(i, node);
			root[node] += subsum[i];
		}
		return root[node];
	};
	vector<int> val;
	function<void(int, int)> dfs3 = [&](int node, int par) -> void {
		val.push_back(root[node]);
		for (int i : adj[node]) {
			if (i == par) continue;
			subsum[node] -= subsum[i];
			root[node] -= root[i] + subsum[i];
			subsum[i] += subsum[node];
			root[i] += root[node] + subsum[node];
			dfs3(i, node);
			root[i] -= root[node] + subsum[node];
			subsum[i] -= subsum[node];
			root[node] += root[i] + subsum[i];
			subsum[node] += subsum[i];
		}
	};
	dfs1(1, 0);
	dfs2(1, 0);
	dfs3(1, 0);
	cout << *min_element(val.begin(), val.end()) << "\n";
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
