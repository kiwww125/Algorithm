//boj 17472 
//dfs for grouping, simulation for finding edge, kruskal for MST

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
using pii = pair<int, int>;
using pip = pair<int, pii>; //edge cost, u,v;

const int dr[] = { 0,0,1,-1 };
const int dc[] = { 1,-1,0,0 };

int row, col;

bool bound(int r, int c) {
	return (0 <= r && r < row && 0 <= c && c < col);
}

void group(int r, int c, int g, vector<vector<int>> &board, vector<vector<bool>> &vis) {
	
	if (!bound(r, c)) return;
	if (vis[r][c]) return;
	if (board[r][c] != 1) return;

	vis[r][c] = true;
	board[r][c] = g;

	for (int d = 0; d < 4; d++) {
		int nr = r + dr[d];
		int nc = c + dc[d];
		group(nr, nc, g, board, vis);
	}
}

int find(int u, vector<int> &par) {
	if (par[u] == u) return u;
	return par[u] = find(par[u], par);
}

int main() {

	int ans = 0;
	int groupsz = 1;

	cin >> row >> col;
	vector<vector<int>> board(row, vector<int>(col, 0));
	vector<vector<bool>> vis(row, vector<bool>(col, false));

	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) cin >> board[i][j];
	}
	
	//grouping
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			if (board[i][j] == 1 && !vis[i][j]) {
				group(i, j, groupsz, board, vis);
				groupsz++;
			}
		}
	}

	//make graph for kruskal
	vector<pip> graph;
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			//if island
			if (board[i][j] != 0) {
				for (int d = 0; d < 4; d++) {
					int ni = i + dr[d], nj = j + dc[d];
					while(bound(ni,nj) && board[ni][nj] == 0) ni += dr[d], nj += dc[d];
					if (bound(ni, nj) && abs((ni - i) + (nj - j)) > 2 ) graph.emplace_back(abs(ni - i + nj - j) - 1, pii(board[i][j], board[ni][nj]));
				}
			}
		}
	}

	sort(graph.begin(), graph.end());

	vector<int> par(7);
	for (int i = 0; i < 7; i++) par[i] = i;

	for (pip edge : graph) {
		int u = edge.second.first, v = edge.second.second;
		int cost = edge.first;

		u = find(u, par), v = find(v, par);
		if (u != v) {
			par[u] = v;
			ans += cost;
		}
	}

	for (int i = 2; i < groupsz; i++) {
		if (find(1, par) != find(i,par)) ans = -1;
	}

	cout << ans;
	return 0;
}
