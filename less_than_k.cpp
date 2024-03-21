
/**
 * there are q queries given with attributes [l, r, x, y, k]
 * find all the elements such that -> (a[i] * x) + y <= k in range [l, r]
 * so essentially it boils down to a[i] <= (k - y) / x
 * let k' = (k - y) / x
 * so we need to find all the indices in range [l, r] such that a[i] <= k'
 * Hence this has been solved using fenwick tree and offline queries method
*/

int bit[100100];
void update(int ind, int val, int n) {
   while (ind <= n) {
      bit[ind] += val;
      ind += ind & (-ind);
   }
}
int getsum(int ind) {
   int sum = 0;
   while (ind > 0) {
      sum += bit[ind];
      ind -= ind & (-ind);
   }
   return sum;
}
vector <int> madQueries (int n, int q, vector <int> &a, vector <vector<int>> &queries) {
   memset(bit, 0, sizeof bit);
   vector<pair<int, int>> arr;
   for (int i = 1; i <= n; i++) {
      arr.push_back(make_pair(a[i - 1], i));
   }
   sort(arr.begin(), arr.end());
   vector<int> ans(q);
   vector<vector<int>> temp;
   for (int i = 0; i < q; i++) {
      int num = (queries[i][4] - queries[i][3]);
      int val = queries[i][2] != 0 ? num / queries[i][2] : 0;
      temp.push_back({val, queries[i][0], queries[i][1], queries[i][2], queries[i][3], i});
   }
   sort(temp.begin(), temp.end());
   int curr = 0;
   for (int i = 0; i < q; i++) {
      int val = temp[i][0];
      while (curr < n && arr[curr].first <= val) {
        update(arr[curr].second, 1, n + 1);
        curr++;
      }
      int res = getsum(temp[i][2]) - getsum(temp[i][1] - 1);
      ans[temp[i][5]] = res;
   }
   return ans;
}