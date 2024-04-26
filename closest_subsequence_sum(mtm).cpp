
/**
 * problem link - https://leetcode.com/problems/closest-subsequence-sum/
 * This problem is an application of a very useful concept known as meet in the middle.
*/

class Solution {
    void subset_cal(vector<int>& nums, vector<int>& sum) {
        int n = nums.size();
        for (int i = 0; i < (1 << n); i++) {
            int subsum = 0;
            for (int j = 0; j < n; j++) {
                if (i & (1 << j)) {
                    subsum += nums[j];
                }
            }
            sum.push_back(subsum);
        }
    }
public:
    int minAbsDifference(vector<int>& nums, int goal) {
        int n = nums.size();
        int left = n / 2, right = (n + 1) / 2;
        vector<int> v1, v2;
        for (int i = 0; i < n; i++) {
            if (i < left) v1.push_back(nums[i]);
            else v2.push_back(nums[i]);
        }
        vector<int> sum1, sum2;
        subset_cal(v1, sum1);
        subset_cal(v2, sum2);
        sort(sum2.begin(), sum2.end());
        long long ans = 1e14;
        for (int i : sum1) {
            int req = goal - i;
            int ind = upper_bound(sum2.begin(), sum2.end(), req) - sum2.begin();
            if (ind - 1 >= 0) {
                long long total = i + sum2[ind - 1];
                ans = min(ans, abs(total - goal));
            }
            if (ind < sum2.size()) {
                long long total = i + sum2[ind];
                ans = min(ans, abs(total - goal));
            }
        }
        return ans;
    }
};