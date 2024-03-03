#include <bits/stdc++.h>
#define startt ios_base::sync_with_stdio(false);cin.tie(0);
#define ll long long
#define clock cout << "time taken : "<< (float)clock() / CLOCKS_PER_SEC << " secs" << endl
#define INF 0x3F3F3F3F3F3F3FLL
using namespace std;
// #include <ext/pb_ds/assoc_container.hpp>
// #include <ext/pb_ds/tree_policy.hpp>
// using namespace __gnu_pbds;
// typedef tree<ll, null_type, less_equal<ll>, rb_tree_tag, tree_order_statistics_node_update> pbds;
 
// find_by_order , order_of_key

const ll mod = 1e9+7;


/* problem link - https://atcoder.jp/contests/abc341/tasks/abc341_e
	this is a range update type question using fenwick tree
*/

class BIT {
public:
	vector<ll> table;
public:
	// assume one based indexing
	BIT(ll n) {
		table = vector<ll>(n + 1);
	}
	
	void update(ll ind, ll delta) {
		while (ind < (long long) table.size()) {
			table[ind] += delta;
			ind += (ind & (-ind));
		}
	}
	
	ll getSum(ll ind) {
		ll sum = 0;
		while (ind > 0) {
			sum += table[ind];
			ind -= (ind & (-ind));
		}
		return sum;
	}
	ll rangeSum(ll l, ll r) {
		return getSum(r) - getSum(l - 1);
	}
};


void solve() {
	ll n, q;
	cin >> n >> q;
	string s;
	cin >> s;
	BIT b1(n), b2(n);
	ll cnt = 0;
	for (ll i = 0; i < n; i++) {
		if (i + 1 < n && s[i] == s[i + 1]) {
			cnt++;
		}
		b2.update(i + 1, cnt);
		b2.update(i + 2, -cnt);
	}
	// for (ll i = 0; i < n; i++) {
	// 	cout << b2.getSum(i + 1) << " ";
	// }
	while (q--) {
		ll tp, l, r;
		cin >> tp >> l >> r;
		l--, r--;
		if (tp == 1) {
			b1.update(l + 1, 1);
			b1.update(r + 2, -1);
			ll x1 = b1.getSum(l + 1), x2 = b1.getSum(r + 1);
			char a = s[l], b = s[r];
			if (x1 % 2) {
				if (s[l] == '0') a = '1';
				else a = '0';
			}
			if (x2 % 2) {
				if (s[r] == '0') b = '1';
				else b = '0';
			}
			if (l - 1 >= 0) {
				ll x3 = b1.getSum(l);
				char c = s[l - 1];
				if (x3 % 2) {
					if (s[l - 1] == '0') c = '1';
					else c = '0';
				}
				if (c == a) {
					b2.update(l, 1);
				}
				else {
					b2.update(l, -1);
				}
			}
			if (r + 1 < n) {
				ll x4 = b1.getSum(r + 2);
				char d = s[r + 1];
				if (x4 % 2) {
					if (s[r + 1] == '1') d = '0';
					else d = '1'; 
				}
				if (b == d) {
					b2.update(r + 1, 1);
				}
				else {
					b2.update(r + 1, -1);
				}
			}
		}
		else {
			if (b2.rangeSum(l + 1, r)) {
				cout << "No\n";
			}		
			else {
				cout << "Yes\n";
			}
		}
	}
}


int main() { 
	startt	
	ll tt = 1;
	// cin >> tt;
	while (tt--) {
		solve();
	}	
}
