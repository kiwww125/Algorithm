#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

//이동 x, 상 우 하 좌
const int dr[] = { 0,-1, 0, 1, 0 };
const int dc[] = { 0, 0, 1, 0, -1 };

struct BC {
	int r, c;
	int bound;
	int power;
};

vector<int> moveInput(int movetime) {

	vector<int> ret;

	for (int j = 0; j < movetime; j++) {
		int t;
		cin >> t;
		ret.emplace_back(t);
	}

	return ret;
}

int getPower(int r, int c, BC target) {
	if ( abs(target.r - r) + abs(target.c - c) <= target.bound) {
		return target.power;
	}
	return 0;
}

int find_max(int fr, int fc, int sr, int sc, vector<BC> &bc) {
	int ret = 0;

	for (BC first : bc) {
		for (BC second : bc) {
			int fpow, spow;
			fpow = getPower(fr, fc, first);
			spow = getPower(sr, sc, second);
			//두 명이 같은 BC에 연결하는 경우는 2로 나눠주기
			if (first.r == second.r && first.c == second.c && fpow > 0 && spow > 0) {
				fpow /= 2;
				spow /= 2;
			}
			ret = max(ret, fpow + spow);
		}
	}

	return ret;
}

int main() {

	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	
	int tc;
	cin >> tc;

	for (int rescnt = 1; rescnt <= tc; rescnt++) {

		int movetime, BCsize;
		cin >> movetime >> BCsize;
		vector<BC> bc;
		vector<int> person[2];

		//움직이는 거 입력받기
		person[0] = moveInput(movetime);
		person[1] = moveInput(movetime);

		//BC 종류 입력받기
		for (int i = 0; i < BCsize; i++) {
			int r, c, bound, power;
			cin >> c >> r >> bound >> power;
			bc.emplace_back(BC{ r,c,bound ,power });
		}

		int ans = 0;
		int fr = 1, fc = 1, sr = 10, sc = 10;

		for (int i = 0; i <= movetime; i++) {
			ans += find_max(fr, fc, sr, sc, bc);
			fr += dr[person[0][i]];
			fc += dc[person[0][i]];
			sr += dr[person[1][i]];
			sc += dc[person[1][i]];
		}

		cout << "#" << rescnt << ' ' << ans << '\n';
	}

	return 0;
}
