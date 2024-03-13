#include <bits/stdc++.h>
#define int long long
#define INF 0x3F3F3F3F3F3F3FLL
using namespace std;
// #include <ext/pb_ds/assoc_container.hpp>
// #include <ext/pb_ds/tree_policy.hpp>
// using namespace __gnu_pbds;
// typedef tree<int, nuint_type, less_equal<int>, rb_tree_tag, tree_order_statistics_node_update> pbds;

// find_by_order , order_of_key

/**
 * problem link - https://atcoder.jp/contests/abc343/tasks/abc343_f
 * this is a point update question solved using SEGMENT TREE
*/


struct node {
	int big, small, cnt_big, cnt_small;
	node() {
		big = 0, small = 0, cnt_big = 0, cnt_small = 0;
	}
};

const int mod = 1e9 + 7;
const int N = 200005;
int arr[N];
node t[4 * N];

node merge(node left, node right) {
	node res;
	int a = left.big, b = left.small, ac = left.cnt_big, bc = left.cnt_small;
	int x = right.big, y = right.small, xc = right.cnt_big, yc = right.cnt_small;
	res.big = max(a, x);
	res.small = max(b, y);
	if (a != res.big) res.small = max(res.small, a);
	if (x != res.big) res.small = max(res.small, x);

	// updating the frequencies 
	if (a == res.big) res.cnt_big += ac;
	if (x == res.big) res.cnt_big += xc;
	if (a == res.small) res.cnt_small += ac;
	if (b == res.small) res.cnt_small += bc;
	if (x == res.small) res.cnt_small += xc;
	if (y == res.small) res.cnt_small += yc;
	return res;
}
void build(int id, int l, int r) {
	if (l == r) {
		t[id].big = arr[l];
		t[id].small = 0;
		t[id].cnt_big = 1;
		t[id].cnt_small = 0;
		return;
	}
	int mid = (l + r) / 2;
	build(2 * id, l, mid);
	build(2 * id + 1, mid + 1, r);
	t[id] = merge(t[2 * id], t[2 * id + 1]);
}
void update(int id, int l, int r, int pos, int val) {
	if (pos < l || pos > r) {
		return;
	}
	if (l == r) {
		t[id].big = val;
		t[id].small = 0;
		t[id].cnt_big = 1;
		t[id].cnt_small = 0;
		return;
	}
	int mid = (l + r) / 2;
	update(2 * id, l, mid, pos, val);
	update(2 * id + 1, mid + 1, r, pos, val);
	t[id] = merge(t[2* id], t[2 * id + 1]);
}
node query(int id, int l, int r, int ql, int qr) {
	if (r < ql || l > qr) {
		return node();
	}
	if (l >= ql && r <= qr) {
		return t[id];
	}
	int mid = (l + r) / 2;
	auto left = query(2 * id, l, mid, ql, qr);
	auto right = query(2 * id + 1, mid + 1, r, ql, qr);
	return merge(left, right);
}

void solve() {
	int n, q;
	cin >> n >> q;
	for (int i = 0; i < n; i++) {
		cin >> arr[i];
	}
	build(1, 0, n - 1);
	// auto ans = query(1, 0, n - 1, 0, 4) ;
	// cout << ans.small << " ";
	while ((q--)) {
		int ch;
		cin >> ch;
		if (ch == 1) {
			int p, x;
			cin >> p >> x;
			p--;
			update(1, 0, n - 1, p, x);
		}
		else {
			int l, r;
			cin >> l >> r;
			l--; r--;
			auto ans = query(1, 0, n - 1, l, r);
			
			cout << ans.cnt_small << "\n";
		}
	}
	
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
