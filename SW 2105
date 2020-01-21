#include <iostream>
#include <algorithm>

using namespace std;

const int dr[] = { 1, 1, -1, -1 };
const int dc[] = { 1, -1, -1 ,1 };

bool visited[21][21];
bool used[101];
int board[21][21];
int ans;
int n;

//사각형을 찾아 ans 갱신
void solve(int r, int c, int dir, const int& targetr, const int& targetc) {
	//base case -> 사각형을 찾은 경우
	if (r == targetr && c == targetc && dir == 3) {
		int t = 0;
		for (int i = 1; i <= 100; i++) {
			if (used[i]) t++;
		}

		//가장 최소가 4개 , 이외의 경우는 규칙 위반
		if(t >= 4) ans = max(t, ans);
		return;
	}
	
	visited[r][c] = true;
	used[board[r][c]] = true;

	for (int next = dir; next < 4; next++) {
		int mr = r + dr[next];
		int mc = c + dc[next];

		//돌아오는 경우 check
		if (mr == targetr && mc == targetc && next == 3) solve(mr, mc, next, targetr, targetc);
		if (mr < 1 || mr > n || mc < 1 || mc > n) continue;
		if (visited[mr][mc]) continue;
		if (used[board[mr][mc]]) continue;

		solve(mr, mc, next, targetr, targetc);
	}

	visited[r][c] = false;
	used[board[r][c]] = false;

 	return;
}

int main() {

	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	int tc;
	cin >> tc;

	for (int cnt = 1; cnt <= tc; cnt++) {

		ans = -1;
		cin >> n;

		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++) {
				cin >> board[i][j];
			}
		}

		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++) {
				solve(i, j, 0, i, j);
			}
		}

		cout << "#" << cnt << ' ' << ans << '\n';
	}

	return 0;
}
