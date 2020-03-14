//BOJ 1005 ACM CRAFT
//위상정렬 기본문제
//Ctrl + alt + n -> run code

#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;
using pii = pair<int, int>;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int tc;
    cin >> tc;
    while (tc--) {
        int n, m, target;
        cin >> n >> m;

        vector<vector<int> > graph(n + 1);
        vector<int> taken(n + 1);
        vector<int> indegree(n + 1, 0);
        priority_queue<pii, vector<pii>, greater<pii> > pq;  //taken time, node index

        for (int i = 1; i <= n; i++)
            cin >> taken[i];

        for (int i = 0; i < m; i++) {
            int u, v;
            cin >> u >> v;
            indegree[v]++;
            graph[u].emplace_back(v);
        }
        cin >> target;

        for (int i = 1; i <= n; i++)
            if (!indegree[i])
                pq.emplace(pii(taken[i], i));

        //topological sort
        while (pq.size()) {
            pii now = pq.top();
            pq.pop();
            int time = now.first, node = now.second;

            if (node == target) {
                cout << time << '\n';
                break;
            } 
            else {
                for (int next : graph[node]) {
                    indegree[next]--;
                    if (!indegree[next]) {
                        pq.emplace(pii(time + taken[next], next));
                    }
                }
            }
        }
    }

    return 0;
}
