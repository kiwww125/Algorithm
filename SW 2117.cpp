#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
using pii = pair<int, int>;

int main() {

	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	int tc; cin >> tc;
	for (int tcnt = 1; tcnt <= tc; tcnt++) {

		int ans = 0;
		int n, m; cin >> n >> m;
		vector<pii> house;

		//집만 받기
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				int in; cin >> in;
				if (in == 1) house.emplace_back(pii(i, j));
			}
		}

		//brute force로 전부 확인
		for (int k = 0; k < 2 * n; k++) {
			for (int r = 0; r < n; r++) {
				for (int c = 0; c < n; c++) {
					int safecnt = 0;
					for (pii nowh : house) {
						if (nowh.first > r + k) break;
						if (abs(nowh.first - r) + abs(nowh.second - c) <= k) safecnt++;
					}

					if (safecnt) {
						ans = (safecnt * m) - (k + 1) * (k + 1) - (k * k) >= 0 ? max(safecnt, ans) : ans;
					}
				}
			}
		}

		cout << "#" << tcnt << ' ' << ans << '\n';
	}

	return 0;
}
