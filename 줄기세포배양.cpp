#include <iostream>
#include <queue>
#include <functional>
#include <vector>

using namespace std;

const int fix = 330;
const int dr[] = { 0,0,-1,1 };
const int dc[] = { 1,-1,0,0 };

struct cell {
	int timepassed, r, c;
};

struct cmp {
	bool operator()(const cell &a, const cell &b) {
		return a.timepassed < b.timepassed;
	}
};

int rsize, csize, totaltime;
int board[700][700];

int main() {

	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	int tc;
	cin >> tc;

	for(int tnum = 1; tnum <= tc; tnum++) {
		
		queue<cell> nonQ, remaining;  //비활성, 번식하고 난 활성세포
		priority_queue<cell, vector<cell> ,cmp> actQ; // 번식해야할 활성세포
	
		fill_n(board[0], 700 * 700, 0);

		cin >> rsize >> csize >> totaltime;
		
		for (int i = 0; i < rsize; i++) {
			for (int j = 0; j < csize; j++) {
				cin >> board[i + fix][j + fix];
				if (board[i + fix][j + fix]) nonQ.emplace(cell{ 0, i + fix, j + fix });
			}
		}

		while (totaltime--) {
			int nonloop = nonQ.size();
			
			while (actQ.size()) {
				cell now = actQ.top(); actQ.pop();
				remaining.emplace(cell{ 1, now.r, now.c });

				for (int d = 0; d < 4; d++) {
					int r = now.r + dr[d];
					int c = now.c + dc[d];

					if (board[r][c]) continue;
					board[r][c] = now.timepassed;
					nonQ.emplace(cell{ 0, r,c });
				}
			}

			int remainloop = remaining.size();
			while (remainloop--) {
				cell now = remaining.front(); remaining.pop();
				if (now.timepassed == board[now.r][now.c]) continue;
				remaining.emplace(cell{ now.timepassed + 1, now.r, now.c });
			}

			while (nonloop--) {
				cell now = nonQ.front(); nonQ.pop();
				int r = now.r, c = now.c ,timep = now.timepassed + 1;

				if (timep == board[r][c]) {
					actQ.emplace(cell{ timep, r, c });
				}
				else nonQ.emplace(cell{ timep, r, c });
			}
		}

		cout << "#" << tnum << ' ' << actQ.size() + nonQ.size() + remaining.size() << '\n';
	}

	return 0;
}
