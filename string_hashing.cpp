#define ll long long

/** problem link - https://leetcode.com/problems/count-prefix-and-suffix-pairs-ii/description/
 * solved using string hashing
 */

class StringHash {
	// uses double hashing
public:
    vector<ll>ps1, ps2;
    ll Q1 = 271, Q2 = 277, M1 = 1000000007, M2 = 998244353;
    StringHash(string s) {
        ps1 = vector<ll>(s.size()+1); 
        ps2 = vector<ll>(s.size()+1);
        for (ll i = 1; i <= s.size(); i++) {
            ll c = s[i-1] + 1;
            ps1[i] = ((Q1 * ps1[i-1]) + c) % M1;
            ps2[i] = ((Q2 * ps2[i-1]) + c) % M2;
        }
    }
    ll binpow(ll x, ll y, ll M) {
        if (y == 0) return 1;
        if (y % 2 == 1) return (x * binpow(x, y-1, M)) % M;
        ll t = binpow(x, y/2, M);
        return (t * t) % M;
    }
    ll substrHash1(ll firstIndex, ll lastIndex) {
        ll rem = (binpow(Q1, lastIndex - firstIndex + 1, M1) * ps1[firstIndex]) % M1;
        return (ps1[lastIndex + 1] - rem + M1) % M1;
    }
    ll substrHash2(ll firstIndex, ll lastIndex) {
        ll rem = (binpow(Q2, lastIndex - firstIndex + 1, M2) * ps2[firstIndex]) % M2;
        return (ps2[lastIndex + 1] - rem + M2) % M2;
    }
    pair<ll, ll> substrHash(ll firstIndex, ll lastIndex) {
        return {substrHash1(firstIndex, lastIndex), substrHash2(firstIndex, lastIndex)};
    }
};
class Solution {
public:
    long long countPrefixSuffixPairs(vector<string>& words) {
        int n = words.size();
        map<pair<ll, ll>, ll> mp;
        ll ans = 0;
        for (ll i = n - 1; i >= 0; i--) {
            ll m = words[i].size();
            StringHash sh(words[i]);
            auto hash = sh.substrHash(0, m - 1); // find the hash of words[i]
            if (mp.count(hash)) ans += mp[hash];
            for (ll j = 0; j < m; j++) {
                auto prehash = sh.substrHash(0, j);
                auto suffhash = sh.substrHash(m - j - 1, m - 1);
                if (prehash == suffhash) mp[prehash]++;
            }
        }
        return ans;
    }
};