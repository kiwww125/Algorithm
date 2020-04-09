//KMP
//단순한 규칙 관찰로 beg이 답이 된다는 것을 알았음
// 찾아보니, 전광판 길이 - pi table의 최대값(공통 접미사, 접두사의 최대 길이)
// -> 왜? 왜냐면 그 접두, 접미사 사이의 string을 바로 뒤에 붙이는 것으로 생각할 수 있기 때문이당
//ex) aabaaa -> aa(ba)aa -> aa(ba)aa(ba)

#include <iostream>
#include <vector>
#include <string>

using namespace std;

int solve(const string& tar, const string &src){

	int beg = 1, match = 0, m = src.size();
	vector<int> pi(m, 0);
	string targ = tar + tar;

	while (beg + m <= targ.size()) {
		if (beg + match == tar.size()) break;
		
		if (targ[beg + match] == src[match]) {
			match++;
			pi[beg + match - 1] = match;
		}
		else {
			if (match == 0) beg++;
			else {
				beg += match - pi[match - 1];
				match = pi[match-1];
			}
		}
	}
	return beg;
}

int main() {
	
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	int n;
	string src;
	cin >> n;
	cin >> src;

	cout << solve(src, src);

	return 0;
}
