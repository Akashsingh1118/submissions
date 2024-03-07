#include <bits/stdc++.h>
#define int unsigned long long
#define INF 0x3F3F3F3F3F3F3FLL
using namespace std;
// #include <ext/pb_ds/assoc_container.hpp>
// #include <ext/pb_ds/tree_policy.hpp>
// using namespace __gnu_pbds;
// typedef tree<ll, null_type, less_equal<ll>, rb_tree_tag, tree_order_statistics_node_update> pbds;

// find_by_order , order_of_key

/**
 * problem link - https://atcoder.jp/contests/abc343/tasks/abc343_f
 * this is a point update question solved using segment tree
*/


const int mod = 1e9 + 7;
const int N = 200005;
const int MIN = 1ll * -1e14;

vector<int> t[4 * N];
vector<int> combine(vector<int> p1, vector<int> p2) {
	int a = p1[0], b = p1[1], ac = p1[2], bc = p1[3];
	int x = p2[0], y = p2[1], xc = p2[2], yc = p2[3];
	vector<int> res(4);
	res[0] = max(a, x);
	res[1] = max(b, y);
	if (a != res[0]) res[1] = max(res[1], a);
	if (x != res[0]) res[1] = max(res[1], x);

	// updating the frequencies 
	if (a == res[0]) res[2] += ac;
	if (x == res[0]) res[2] += xc;
	if (a == res[1]) res[3] += ac;
	if (b == res[1]) res[3] += bc;
	if (x == res[1]) res[3] += xc;
	if (y == res[1]) res[3] += yc;
	return res;
}
void build(int a[], int v, int tl, int tr) {
    if (tl == tr) t[v] = {a[tl], MIN, 1, 0};
	else {
        int tm = (tl + tr) / 2;
        build(a, v*2, tl, tm);
        build(a, v*2+1, tm+1, tr);
        t[v] = combine(t[v*2], t[v*2+1]);
    }
}
vector<int> get_max(int v, int tl, int tr, int l, int r) {
	if (tl>r || tr<l) return {MIN, MIN, 0, 0};
	if (tl>=l && tr<=r) return t[v];
    int tm = (tl + tr) / 2;
    return combine(get_max(v*2, tl, tm, l, r), get_max(v*2+1, tm+1, tr, l, r));
}

void update(int v, int tl, int tr, int pos, int new_val) {
    if (tl == tr) t[v] = {new_val, MIN, 1, 0};
	else {
        int tm = (tl + tr) / 2;
        if (pos <= tm) update(v*2, tl, tm, pos, new_val);
        else update(v*2+1, tm+1, tr, pos, new_val);
        t[v] = combine(t[v*2], t[v*2+1]);
    }
}
void solve() {
	int n;
	cin >> n;
	int q;
	cin >> q;
	int a[n];
	for (int i = 0; i < n; i++) {
		cin >> a[i];
	}
	build(a, 1, 0, n - 1);
	for (int i = 0; i < q; i++) {
		int tp;
		cin >> tp;
		if (tp == 1) {
			int p, x;
			cin >> p >> x;
			p--;
			a[p] = x;
			update(1, 0, n - 1, p, x);
		}
		else {
			int l, r;
			cin >> l >> r;
			auto h = get_max(1, 0, n - 1, l - 1, r - 1);
			if (h[1] == MIN) {
				cout << 0 << "\n";
			}
			else {
				cout << h[3] << "\n";
			}
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
}
