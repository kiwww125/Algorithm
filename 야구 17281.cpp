#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

bool used[10];
//hitorder -> 타석 별 타자 번호
int n, ans, hitorder[10], hitRes[51][10];

int move(int step, bool board[4]) {
	
	int ret = 0;
	board[0] = true;

	for (int i = 3; i >= 0; i--) {
		if (board[i] == true) {
			board[i] = false;
			if (i + step >= 4) ret++;
			else board[i + step] = true;
		}
	}

	return ret;
}

int simulate() {

	int now = 1, inning = 1, outcnt = 0, point = 0;
	//0 = 홈, 1루 2루 3루
	bool board[4] = { false, false, false, false};
	
	while (inning <= n) {
		
		point += move(hitRes[inning][hitorder[now]], board); 

		if (hitRes[inning][hitorder[now]] == 0) {
			outcnt++;
		}
		if (outcnt == 3) {
			inning++;
			outcnt = 0;
      //clear 시켜줘야 함..!!
			memset(board, false, sizeof(board));
		}
		now = (now == 9 ? 1 : (now + 1));
	}

	return point;
}

void backtrack(int depth) {
	if (depth == 10) {
		ans = max(ans, simulate());
		return;
	}
	else if (depth == 4) backtrack(depth + 1);
	else {
		for (int hitnum = 2; hitnum <= 9; hitnum++) {
			if (used[hitnum]) continue;
			hitorder[depth] = hitnum;
			used[hitnum] = true;
			backtrack(depth + 1);
			used[hitnum] = false;
		}
	}
	return;
}

int main() {

	hitorder[4] = 1;
	used[1] = true;

	cin >> n;

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j < 10; j++) {
			cin >> hitRes[i][j];
		}
	}

	backtrack(1);

	cout << ans;

	return 0;
}
