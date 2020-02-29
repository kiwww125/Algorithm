//boj 17406 배열 돌리기

#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>

using namespace std;

struct info {
	int r, c, s;
};

const int dr[] = { 0, 1, 0,-1 };
const int dc[] = { 1, 0, -1, 0 };

int row, col, t;
int ans = numeric_limits<int>::max();

bool used[6];
int ind[6];
int board[51][51];
info turn[6];

int calc(int temp[51][51]) {

	int ret = numeric_limits<int>::max();

	for (int i = 0; i < t; i++) {
		int r = turn[ind[i]].r, c = turn[ind[i]].c, s = turn[ind[i]].s;

		for (int tsize = 1; tsize <= s; tsize++) {
			int sr = r - tsize, sc = c - tsize;
			int mr = sr, mc = sc ;
			int d = 3;
			int mcnt = 0;
			int last = temp[mr][mc];

			while (1) {
				temp[mr][mc] = temp[mr - dr[d]][mc - dc[d]];
				mr -= dr[d], mc -= dc[d];
				mcnt++;
				if (mcnt == tsize * 2) d--, mcnt = 0;
				if (mr == sr && mc == sc) break;
			}
			temp[mr][mc+1] = last;
		}
	}

	for (int i = 1; i <= row; i++) {
		int tsum = 0;
		for (int j = 1; j <= col; j++) {
			tsum+= temp[i][j];
		}
		if (ret > tsum) ret = tsum;
	}

	return ret;
}

void back_track(int dep) {
	if (dep == t) {
		int temp[51][51];
		for (int i = 1; i <= row; i++) {
			for (int j = 1; j <= col; j++) temp[i][j] = board[i][j];
		}
		ans = min(ans, calc(temp));
	}
	else {
		for (int i = 0; i < t; i++) {
			if (used[i]) continue;
			used[i] = true;
			ind[dep] = i;
			back_track(dep + 1);
			used[i] = false;
		}
	}
}

int main() {

	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	cin >> row >> col >> t;

	for (int i = 1; i <= row; i++) {
		for (int j = 1; j <= col; j++) {
			cin >> board[i][j];
		}
	}

	for (int i = 0; i < t; i++) cin >> turn[i].r >> turn[i].c >> turn[i].s;

	back_track(0);

	cout << ans;
	return 0;
}
