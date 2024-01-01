class Solution {
public:
    vector<int> findClosestElements(vector<int>& arr, int k, int x) {

        vector<int> ans(arr.size() , 0);

        int i , j =  arr.size() - 1;


        for(int m=0; m < arr.size(); m++) {
            
            if(arr[m] == x) {
                i = m;
                j = m;
                break;
            }

            if( arr[m] > x) {
                i = m-1;
                j=m;

                break;
            }
        }


        int cnt = 0;

        while (cnt < k)
        {
            if(i == j) {
                ans[i] = 1;
                i--;
                j++;
                cnt++;
            }

            else if( ( i >= 0 && j<= (arr.size()-1) && abs(arr[i] - x) <= abs(arr[j] - x) ) ) {
                ans[i] = 1;
                i--;
                cnt++;
            }

            else if( j<= (arr.size()-1) ) {
                ans[j] = 1;
                j++;
                cnt++;
            }

            else {
                ans[i] = 1;
                i--;
                cnt++;
            }
            
        }

        vector<int> v1;

        for(int i=0; i<ans.size(); i++) {
            if(ans[i] == 1) {
                v1.push_back(arr[i]);
            }
        }
        
        return v1;
    }
};
