#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <string>
 
using namespace std;
 
vector<int> cand;
 
bool des(int a, int b) {
    return a > b;
}
 
int main() {
 
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
 
    int tc;
    cin >> tc;
    for (int tc_cnt = 1; tc_cnt <= tc; tc_cnt++) {
 
        int n, k;
        string input;
        cand.clear();
 
        cin >> n >> k >> input;
         
        int linenum = n / 4;
        //회전
        for (int rotate = 0; rotate < linenum; rotate++) {
            //계산 시작점
            for (int cnt = 0; cnt < 4; cnt++) {
                int calcbeg = (rotate + (cnt * linenum)) % n;
                int sum = 0;
 
                for (int bound = 0; bound < linenum; bound++) {
                    char hex = input[(calcbeg + bound) %n];
                    if (hex > '9') hex = hex -'A'+10;
                    else hex -= '0';
                    sum += (int)hex * pow(16, linenum - (bound +1));
                }
 
                bool isincand = false;
                for (int v : cand) {
                    if (v == sum) {
                        isincand = true;
                        break;
                    }
                }
 
                if (!isincand) cand.emplace_back(sum);
            }
        }
 
        //내림차순
        sort(cand.begin(), cand.end(), des);
        cout << '#' << tc_cnt << ' ' << cand.at(k-1) << '\n' ;
    }
 
    return 0;
}
