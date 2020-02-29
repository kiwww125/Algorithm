//sw expert 2382 미생물 격리

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cstring>

using namespace std;
using pii = pair<int, int>;

const int dr[] = { -1,1,0,0 };
const int dc[] = { 0,0,-1,1 };

struct info {
	int r, c, num, dir;
};

struct cmp {
	bool operator()(info& a, info& b) {
		return a.num < b.num;
	}
};

bool vis[101][101];
int board[101][101];

int turn(int dir) {
	dir++;
	if (dir == 2) return 0;
	else if (dir == 4) return 2;
	return dir;
}

int main() {

	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	int tc;
	cin >> tc;

	for (int tcnt = 1; tcnt <= tc; tcnt++) {

		int n, m, k;
		cin >> n >> m >> k;

		memset(board, 0, sizeof(board));
		memset(vis, false, sizeof(vis));
		priority_queue<info, vector<info>, cmp> pq; //save all except sum
		queue<info> q;

		for (int i = 0; i < k; i++) {
			int r, c, num, dir;
			cin >> r >> c >> num >> dir;
			pq.emplace(info{ r,c,num,dir - 1 });
			board[r][c] = num;
		}

		while (m--) {
			int loopsize = pq.size();

			while (loopsize--) {
				info now = pq.top(); pq.pop();
				int r = now.r, c = now.c, num = now.num, d = now.dir;
				int nr = r + dr[d], nc = c + dc[d];
				board[r][c] -= num;

				//가장자리 닿는 경우
				if (nr == 0 || nr == n - 1 || nc == 0 || nc == n - 1) {
					if (num >= 2) {
						board[nr][nc] += num / 2;
						q.emplace(info{ nr,nc, 0, turn(d) });
					}
				}
				else {
					if (!vis[nr][nc]) {
						vis[nr][nc] = true;
						q.emplace(info{ nr,nc, 0, d });
					}
					board[nr][nc] += num;
				}
			}

			while (q.size()) {
				info n = q.front(); q.pop();
				int r = n.r, c = n.c, d = n.dir;
				pq.emplace(info{ r,c, board[r][c], d });
				vis[r][c] = false;
			}
		}

		long long ans = 0;

		while (pq.size()) {
			ans += board[pq.top().r][pq.top().c];
			pq.pop();
		}

		cout << '#' << tcnt << ' ' << ans << '\n';
	}

	return 0;
}
