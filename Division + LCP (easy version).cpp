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
 * problem link - https://codeforces.com/contest/1968/problem/G1
 * this problem can be solved by using many methods like computing z-array and lps array etc.
 * I have solved it using **string hashing**
*/

const int mod = 1e9 + 7;

// class for efficiently calculating the hash values of a string
class StringHash {
	// uses double hashing
public:
	vector<int>ps1, ps2;
	int Q1 = 271, Q2 = 277, M1 = 1000000007, M2 = 998244353;
	StringHash(string s) {
		ps1 = vector<int>(s.size()+1); 
		ps2 = vector<int>(s.size()+1);
		for (int i = 1; i <= s.size(); i++) {
			int c = s[i-1] + 1;
			ps1[i] = ((Q1 * ps1[i-1]) + c) % M1;
			ps2[i] = ((Q2 * ps2[i-1]) + c) % M2;
		}
	}
	int binpow(int x, int y, int M) {
		if (y == 0) return 1;
		if (y % 2 == 1) return (x * binpow(x, y-1, M)) % M;
		int t = binpow(x, y/2, M);
		return (t * t) % M;
	}
	int substrHash1(int firstIndex, int lastIndex) {
		int rem = (binpow(Q1, lastIndex - firstIndex + 1, M1) * ps1[firstIndex]) % M1;
		return (ps1[lastIndex + 1] - rem + M1) % M1;
	}
	int substrHash2(int firstIndex, int lastIndex) {
		int rem = (binpow(Q2, lastIndex - firstIndex + 1, M2) * ps2[firstIndex]) % M2;
		return (ps2[lastIndex + 1] - rem + M2) % M2;
	}
	pair<int, int> substrHash(int firstIndex, int lastIndex) {
		return {substrHash1(firstIndex, lastIndex), substrHash2(firstIndex, lastIndex)};
	}
};



void solve() {
	int n, x, y;
	cin >> n >> x >> y;
	string s;
	cin >> s;

	int l = 1, r = n, ans = 0;
	while (l <= r) {
		int mid = l + (r - l) / 2;

		// kya l mid length ke prefix milenge
		StringHash h(s);
		auto req = h.substrHash(0, mid - 1);
		int cnt = 1;
		for (int i = mid; i < n;) {
			if (i + mid - 1 >= n) break;
			auto now = h.substrHash(i, i + mid - 1);
			if (now == req) {
				cnt++;
				i += mid;
			}
			else {
				i++;
			}
		}
		if (cnt >= x) {
			ans = mid;
			l = mid + 1;
		}
		else {
			r = mid - 1;
		}
	}
	cout << ans << "\n";
}

signed main() {
	ios_base::sync_with_stdio(0);
	cin.tie(NULL);
	int tt = 1;
	cin >> tt;
	while (tt--) {
		solve();
	}
	return 0;
}
