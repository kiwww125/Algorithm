#include <iostream>
#include <string>
#include <functional>
using namespace std;

int n;
bool visited[1001];
int clkind[1001]; //12시 방향의 인덱스
string tire[1001]; //1번 부터 tire의 값

int find_left(int i) {
	return (i + 6) % 8;
}

int find_right(int i) {
	return (i + 2) % 8;
}

//dir =1 -> 시계방향  , dir =-1 반시계 방향
void turn(int dir, int k) {
	//범위 아웃
	if (k < 1 || k > n) return;
	visited[k] = true;

	char nowl = tire[k][find_left(clkind[k])];
	char nowr = tire[k][find_right(clkind[k])];

	//범위가 넘어가는 경우 더이상 함수 호출 X
	char befr = k - 1 == 0 ? nowl : tire[k - 1][find_right(clkind[k - 1])];
	char nexl = k + 1 == (n + 1) ? nowr : tire[k + 1][find_left(clkind[k + 1])];

	//돌릴수 있는 경우만 함수호츌
	if (befr != nowl && !visited[k - 1]) {
		turn(-dir, k - 1);
	}

	if (nowr != nexl && !visited[k + 1]) {
		turn(-dir, k + 1);
	}

	//방향 돌리기
	clkind[k] -= dir;
	if (clkind[k] < 0) clkind[k] = 7;
	if (clkind[k] > 7) clkind[k] = 0;

	return;
}

int main() {

	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	cin >> n;

	fill_n(clkind, 1001, 0);

	for (int i = 1; i <= n; i++) {
		cin >> tire[i];
	}

	int tc;
	cin >> tc;
	while (tc--) {
		fill_n(visited, 1001, false);
		int now, dir;
		cin >> now >> dir;
		turn(dir, now);
	}

	int ans = 0;
	for (int i = 1; i <= n; i++) {
		if (tire[i][clkind[i]] == '1') ans++;
	}

	cout << ans;
	return 0;
}