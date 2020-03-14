//BOJ 1766 문제집
//위상정렬 기본문제
//priority queue + min heap 활용

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int main(){

    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<vector<int> > graph(n + 1);
    vector<int> indegree(n + 1, 0), ans;
    priority_queue<int, vector<int>, greater<int> > pq;

    for (int i = 0; i < m; i++){
        int u, v;
        cin >> u >> v;
        indegree[v]++;
        graph[u].emplace_back(v);
    }

    for (int i = 1; i <= n; i++)
        if (!indegree[i])
            pq.emplace(i);

    while (pq.size()){
        int now = pq.top(); pq.pop();
        cout << now << ' ';
        for (int next : graph[now]){
            indegree[next]--;
            if (!indegree[next]){
                pq.emplace(next);
            }
        }
    }

    return 0;
}
