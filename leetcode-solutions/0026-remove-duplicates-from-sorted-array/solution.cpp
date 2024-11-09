class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        int i=1,k;
        while(i<nums.size()){
            if (nums[i]==nums[i-1]){
                nums.erase(nums.begin()+i);
            }
            else{
                i++;
            }
        }
        k=nums.size();
        return k;
    }
};
