#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int expectNumber(vector<int>& scores) {
    sort(scores.begin(), scores.end());

    int cnt = scores.size(), tmp = socres[0];
    vector<int> v;
    int num = 1, same_cnt = 0;
    for (int i = 1; i < cnt; i++) {
        if (scores[i] == scores[i - 1]) {
            num++;
        } else {
            if (num == 1) {
                same_cnt++;
            } else {
                v.push_back(num);
                num = 1;
            }
        }
    }
    if (num == 1) {
        same_cnt++;
    } else {
        v.push_back(num);
        num = 1;
    }
}

int main()
{
    int n, a[10005] = {2, 1, 1};
    vector<int> v;
    for (int i = 0; i < 3; i++) {
        v.push_back(a[i]);
    }
    expectNumber(v);
    return 0;
}











class Solution {
public:
int kPart(vector<int>& arr, int start,int end, int k){
        if(k == 1){
            int sum = 0;
            for(int i = start; i <= end; i++){
                sum += arr[i];
            }
            return sum;
        }
        if((end - start + 1) == k){
            int maxn = -1;
            for(int i = start; i <= end; i++){
                if(arr[i] > maxn){
                    maxn = arr[i];

                }
            }
            return maxn;
        }
        int minn = 1000000005;
        for(int i = start; i <= end  + 1 - k; i++){
            int sum = 0;
            for(int j = start; j <= i; j++){
                sum += arr[j];
            }
            int larger = sum > kPart(arr,i + 1, end,k - 1) ? sum : kPart(arr,i + 1, end,k - 1);
            if(larger < minn){
                minn = larger;

            }
        }
        return minn;
}


    int minTime(vector<int>& time, int m) {
        int cnt = time.size();
        if (m >= cnt) {
            return 0;
        }
        vector<int> v(time);
        int vis[10005] = {0};
        sort(time.begin(), time.end());

        for (int i = 1; i <= m; i++) {
            vis[time[cnt - i]] = 1;
        }

        int sum = 0;
        vector<int> tmp;
        for (int i : v) {
            if (vis[i] == 1) {
                tmp.push_back(sum);
                sum = 0;
            } else {
                sum += i;
            }
        }
        int n = tmp.size();
        return kPart(tmp, 0, n - 1, m);
    }
};
