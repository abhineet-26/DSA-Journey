
class Solution {
public:
    long long maxDifference(vector<int>& nums) {
        int n = nums.size();
        long long next1 = 0;
        long long next2 = 0;
        for (int i = n - 1; i >= 0; i--) {
            long long sum1 = nums[i];
            long long take1;
            if (sum1 % 3 == 0)
                take1 = sum1 - next1;
            else
                take1 = sum1 + next1;
            long long best = take1;

            if (i + 1 < n) {
                long long sum2 = nums[i] + (long long)nums[i + 1];
                long long take2;
                if (sum2 % 3 == 0)
                    take2 = sum2 - next2;
                else
                    take2 = sum2 + next2;

                best = max(best, take2);
            }
            next2 = next1;
            next1 = best;
        }
        return next1;
    }
};

