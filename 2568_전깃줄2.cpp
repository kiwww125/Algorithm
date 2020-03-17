//BOJ 2568 전깃줄 -2
//LIS 길이 및 실제 추적필요 LIS = Longest Increasing Subsequence;

//1. LIS 길이 찾기 : O(nlogn) 알고리즘 사용
// -> dp[i] = i 길이를 가진 IS의 마지막 수, ex) {1,4,5}인 경우 dp[3] = 5;
// dp[i]는 bottom-up 방식으로 채워나감. 
// 현재 최대 길이 k를 기준으로 현재 보고있는 arr[j]가 dp[k] 보다 큰 경우 -> dp[k+1] = arr[j] 
// 현재 최대 길이 k를 기준으로 현재 보고있는 arr[j]가 dp[k] 보다 작은 경우 -> arr[j]의 lower_bound dp[x] = arr[j]

//2. LIS 실제 추적 과정 : 여분의 배열 사용하여 추적
//pair<int,int> ans 배열을 사용해 arr[ind]가 실제 LIS에서 삽입될 수 있는 위치와 그 ind를 함께 저장한다.
//ans 배열의 first 에는 주어진 arr배열에서의 ind가 존재하며 second 에는  실제 LIS에서 삽입될 수 있는 위치가 존재한다.
//실제 추적 시, ans의 맨 뒤에서  

#include <iostream>
#include <vector>
#include <algorithm>

#define x first
#define y second

using namespace std;
using pii = pair<int, int>;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int lastind, n;
    cin >> n;

    vector<bool> out(n, true); 
    vector<pii> ans; //array index, dp index
    vector<pii> arr(n); //x, y
    vector<int> dp;

    for (int i = 0; i < n; i++) {
        int u, v;
        cin >> u >> v;
        arr[i] = pii(u, v);
    }

    sort(arr.begin(), arr.end());
    dp.emplace_back(arr[0].y);
    ans.emplace_back(pii(0, 0));
    lastind = 0;

    for (int ind = 1; ind < n; ind++) {
        if (dp.back() < arr[ind].y) {
            ans.emplace_back(pii(ind, dp.size()));
            dp.emplace_back(arr[ind].y);
            lastind = ind;
        } 
        else {
            int far = (lower_bound(dp.begin(), dp.end(), arr[ind].y)) - dp.begin();
            ans.emplace_back(pii(ind, far));
            *(dp.begin() + far) = arr[ind].y;
        }
    }

    cout << n - dp.size() << '\n';

    int cmp = dp.size() - 1;

    for (int i = n-1; i >=0; i--){
        if(cmp == ans[i].second){
            out[ans[i].first] = false;
            cmp--;
        }
    }

    for(int i=0;i<n;i++){
        if(out[i] == true){
            cout << arr[i].x << '\n';
        }
    }
      
    return 0;
}
