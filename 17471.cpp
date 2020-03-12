//BOJ 17471
// 게리멘더링 , 기초 dfs, backtracking 

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <cstring>

using namespace std;

int n, ans = 100000;
bool visited[11];
int set[11];
int people[11];
vector<int> graph[11];

void dfs(int u) {
	if (visited[u]) return;
	visited[u] = true;
	for (int next : graph[u]) {
		if (set[next] == set[u]) dfs(next);
	}
	return;
}

void find_ans() {
	int ind;
	for (ind = 2; ind <= n; ind++) if (set[ind] != set[1]) break;
	//전부 같은 경우
	if (ind == n + 1) return;

	memset(visited, false, sizeof(visited));
	dfs(1); dfs(ind);

	for (int i = 1; i <= n; i++) if (!visited[i]) return;

	int set1 = 0, set2 = 0, temp = 0;
	
	for (int i = 1; i <= n; i++) {
		if (set[i] == 1) set1 += people[i];
		else set2 += people[i];
	}

	temp = abs(set1 - set2);
	ans = min(temp, ans);

	return;
}


void backtrack(int dep) {
	if (dep == n + 1) {
		find_ans();
	}
	else {
		for (int s = 1; s <= 2; s++) {
			set[dep] = s;
			backtrack(dep + 1);
		}
	}
	return;
}

void input() {
	cin >> n;
	for (int i = 1; i <= n; i++) cin >> people[i];
	for (int u = 1; u <= n; u++) {
		int cnt; cin >> cnt;
		while (cnt--) {
			int v; cin >> v;
			graph[u].emplace_back(v);
			graph[v].emplace_back(u);
		}
	}
}

int main() {

	input();
	backtrack(1);

	if (ans == 100000) ans = -1;
	cout << ans;
	return 0;
}
