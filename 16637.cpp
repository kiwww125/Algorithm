#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int n;
char expr[22];

int calc(int a, int b, char exp) {
	if (exp == '+') {
		return a + b;
	}
	if (exp == '-') {
		return a - b;
	}
	if (exp == '*') {
		return a * b;
	}
}

int calcv(vector<int> v) {

	int ret = v[0];
	int d = 1;

	while (d < v.size()) {
		ret = calc(ret, v[d + 1], v[d]);
		d += 2;
	}

	return ret;
}

//start는 항상 숫자 indexing
int solve(int start, vector<int> v) {
	
	if (start >= n) {
		if(start == n) v.emplace_back(expr[n]);
		return calcv(v);
	}

	int ret = 0;

	//괄호 안사용
		v.emplace_back(expr[start]);
		v.emplace_back(expr[start + 1]);
		ret = solve(start + 2, v);
		v.pop_back();
		v.pop_back();
	
	//괄호 사용
		v.emplace_back(calc(expr[start], expr[start + 2], expr[start + 1]));
		if(start + 3 < n ) 
			v.emplace_back(expr[start + 3]);
		ret = max(ret, solve(start + 4, v));
	
	return ret;
}

int main(){


	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> expr[i];
		if (i % 2 == 1) expr[i] -= '0';
	}

	vector<int> v;
	v.clear();

	cout << solve(1, v);

	return 0;

}