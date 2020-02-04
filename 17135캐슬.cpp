#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <cstring>

using namespace std;
using pii = pair<int, int>;

//좌, 상, 우
const int dr[] = { 0,-1,0 };
const int dc[] = { -1,0,1 };

int row, col, dist, ans;
int board[16][16];
int tempb[16][16];

void move_enemy() {

	for (int cind = 1; cind <= col; cind++) {
		for (int rind = row; rind > 1; rind--) {
			board[rind][cind] = board[rind - 1][cind];
		}
		board[1][cind] = 0;
	}
	return;
}

bool isfinish() {

	for (int i = 1; i <= row; i++) {
		for (int j = 1; j <= col; j++) {
			if (board[i][j] == 1) return false;
		}
	}
	return true;
}

bool isbound(int r, int c) {
	return (r > 0 && r <= row && c > 0 && c <= col);
}

pii find_closest(int col) {

	bool visited[16][16];
	memset(visited, false, sizeof(visited));
	queue<pii> q;
	int absdist = 1;

	q.emplace(pii(row, col));

	while (q.size() && absdist <= dist) {
		absdist++;
		int loopsize = q.size();
		while (loopsize--) {
			int r = q.front().first;
			int c = q.front().second;
			q.pop();

			if (board[r][c] == 1) {
				return pii(r, c);
			}

			for (int d = 0; d < 3; d++) {
				int nr = r + dr[d];
				int nc = c + dc[d];

				if (!isbound(nr, nc) || visited[nr][nc]) continue;
				q.emplace(pii(nr, nc));
				visited[nr][nc] = true;
			}
		}
	}

	return pii(-1, -1);
}

void start_game(int fir, int sec, int thi) {

	int cnt = 0;

	copy(&tempb[0][0], &tempb[0][0]+ 16 * 16, &board[0][0]);

	while (!isfinish()) {

		//죽일 적 찾기
		vector<pii> save;
		save.emplace_back(find_closest(fir));
		save.emplace_back(find_closest(sec));
		save.emplace_back(find_closest(thi));
		//죽이기
 		for (pii w : save) {
			int r = w.first, c = w.second;
			if (r == -1) continue;
			if (board[r][c] == 0) continue;
			board[r][c] = 0;
			cnt++;
		}
		//움직이기
		move_enemy();
	}

	ans = max(ans, cnt);
	return;
}

void input() {

	cin >> row >> col >> dist;

	for (int i = 1; i <= row; i++) {
		for (int j = 1; j <= col; j++) {
			cin >> board[i][j];
			tempb[i][j] = board[i][j];
		}
	}
	return;
}

int main() {

	input();

	for (int i = 1; i <= col - 2; i++) {
		for (int j = i + 1; j <= col - 1; j++) {
			for (int k = j + 1; k <= col; k++) {
				start_game(i, j, k);
			}
		}
	}

	cout << ans;
	return 0;
}
