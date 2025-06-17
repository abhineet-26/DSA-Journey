class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int n=prices.size();
        int maxprofit=0;
        int buy=prices[0];
        for (int i=1;i<n;i++){
            if(buy>prices[i]){
                buy=prices[i];
            }
            maxprofit=max(maxprofit,prices[i]-buy);
        }
        return maxprofit;
    }
};
