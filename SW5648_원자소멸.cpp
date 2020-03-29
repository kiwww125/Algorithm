//5648 원자 소멸
//이것 저것 생각해보았으나 그냥 구현이 답이었다.
//근데 구현이 좀 빡센듯하다
//*****vector, list 등 random access가 가능한 컨테이너는 순회하면서 erase 하면 절대 XXXXXX
//move / bomb sequence 를 나누었다.

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
using pii = pair<int, int>;

//상, 하 , 좌, 우
const float dy[] = { 1, -1, 0, 0 };
const float dx[] = { 0, 0, -1, 1};

struct atom {
	int x, y, e;
	int dir;
};

int ans = 0;
int cnt[4002][4002];
vector<atom> atoms;

bool bound(int x, int y) {
	return (0 <= x && x<= 4000 && 0 <= y && y <= 4000);
}

void move() {
	vector<int> era;
	for (int i = 0; i < atoms.size(); i++) {
		atom now = atoms[i];
		cnt[now.x][now.y] = 0;

		now.x += dx[now.dir];
		now.y += dy[now.dir];

		if (bound(now.x, now.y)) {
			atoms[i] = now;
			cnt[now.x][now.y]++;
		}
		else era.emplace_back(i);
	}
	for (int i = era.size() - 1; i >= 0; i--) atoms.erase(atoms.begin() + era[i]);
}

void bomb() {
	vector<int> era;
	for (int i = 0; i < atoms.size(); i++) {
		atom now = atoms[i];
		if (cnt[now.x][now.y] > 1) {
			ans += now.e;
			era.emplace_back(i);
		}
	}
	for (int i = era.size() - 1; i >= 0; i--) {
		cnt[atoms[era[i]].x][atoms[era[i]].y] = 0;
		atoms.erase(atoms.begin() + era[i]);
	}
}


int main() {

	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	int tc; cin >> tc;
	for (int tcnt = 1; tcnt <= tc; tcnt++) {
		ans = 0;
		int n; cin >> n;
		atoms.clear();
		atoms.resize(n);
		for (int i = 0; i < n; i++) {
			cin >> atoms[i].x >> atoms[i].y >> atoms[i].dir >> atoms[i].e;
			atoms[i].x = 2000 + 2 * atoms[i].x;
			atoms[i].y = 2000 + 2 * atoms[i].y;
		}

		for (int time = 0; time < 4001; time++) {
			move();
			bomb();
		}

		cout << "#" << tcnt << ' ' << ans << '\n';
	}

	return 0;
}

