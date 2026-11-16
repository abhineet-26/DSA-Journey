class Solution {
public:
    int countConsistent(vector<int>& nums) {
        int count;
        int n;
        int mini;
        int bitwise;
        n=nums.size();
        count=n;
        for(int i=0;i<n-1;i++){
            mini=nums[i];
            bitwise=nums[i];
            for(int j=i+1;j<n;j++){
                if(nums[j]<mini){
                    mini=nums[j];
                }
                bitwise=nums[j]&bitwise;
                if(mini==bitwise){
                    count++;
                }
            }
        }
        return count;
    }
};
