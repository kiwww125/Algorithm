#include <iostream>
#include <string>
#include <functional>
using namespace std;

int n;
bool visited[1001];
int clkind[1001]; //12�� ������ �ε���
string tire[1001]; //1�� ���� tire�� ��

int find_left(int i) {
	return (i + 6) % 8;
}

int find_right(int i) {
	return (i + 2) % 8;
}

//dir =1 -> �ð����  , dir =-1 �ݽð� ����
void turn(int dir, int k) {
	//���� �ƿ�
	if (k < 1 || k > n) return;
	visited[k] = true;

	char nowl = tire[k][find_left(clkind[k])];
	char nowr = tire[k][find_right(clkind[k])];

	//������ �Ѿ�� ��� ���̻� �Լ� ȣ�� X
	char befr = k - 1 == 0 ? nowl : tire[k - 1][find_right(clkind[k - 1])];
	char nexl = k + 1 == (n + 1) ? nowr : tire[k + 1][find_left(clkind[k + 1])];

	//������ �ִ� ��츸 �Լ�ȣ��
	if (befr != nowl && !visited[k - 1]) {
		turn(-dir, k - 1);
	}

	if (nowr != nexl && !visited[k + 1]) {
		turn(-dir, k + 1);
	}

	//���� ������
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