class Solution {
    public int pivotIndex(int[] nums) {
        int n= nums.length;
         int[] prefix= new int [n];
         prefix[0]=nums[0];
        for(int i=1;i<n;i++){
           prefix[i]=prefix[i-1]+nums[i];
        }
        for(int i=0;i<n;i++){
            int leftsum=(i==0)?0:prefix[i-1];
            int rightsum=prefix[n-1]-prefix[i];
            if (leftsum==rightsum){
                return i;
            }
        }
        return -1;
    }
}
