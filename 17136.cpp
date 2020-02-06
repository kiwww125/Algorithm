#include <iostream>
#include <algorithm>

using namespace std;

bool FOUND;
int ans = 9999;
int used[6];
int board[10][10];

bool CanCover(int ,int ,int);
void cover(int, int ,int );
void undo(int ,int ,int );
void FindNext(int&, int&);
void BackTrack(int, int, int);

int main() {

	int left = 0;

	for (int i = 0; i < 10; i++){
		for (int j = 0; j < 10; j++) {
			cin >> board[i][j];
			if (board[i][j] == 1) left++;
		}
	}

	int r = 0, c = 0;

	if(left > 0 ) FindNext(r, c);
	
	BackTrack(r, c,left);

	if (FOUND)cout << ans;
	else cout << -1;

	return 0;
}

//cover 가능성 check 함수
bool CanCover(int r, int c, int size) {
	//boundary
	if (r + size > 10 || c + size > 10) return false;
	//cancover from r, c by size
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if (board[r + i][c + j] != 1) return false;
		}
	}

	return true;
}

//undo와 짝을 이룸, size를 키우면서 탐색하기때문에, row, col 마지막 줄만 갱신.
void cover(int r, int c , int size) {

	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			board[r + i][c + j] = 2;
		}
	}
	return;
}

void undo(int r, int c, int size) {
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			board[r + i][c + j] = 1;
		}
	}
	return;
}

//Next 1이 있는 경우만호출 -> 따로 out bound 처리 X
void FindNext(int& r, int& c) {
	while (board[r][c] != 1) {
		c++;
		r += (c / 10);
		c %= 10;
	}
	return;
}

//(r,c)는 항상 1임.
void BackTrack(int r, int c, int left) {
	if (left == 0) {
		int temp = 0;
		for (int i = 1; i <= 5; i++) {
			temp += used[i];
		}
		ans = min(ans, temp);
		FOUND = true;
		return;
	}
	else {
 		for (int size = 1; size <= 5; size++) {
			if (CanCover(r, c, size) && used[size] < 5) {
				cover(r, c, size);
				used[size]++;
				
				int nr = r, nc = c, nleft = left - size*size;
				//남은 1이 있는 경우만 다음 위치 찾기
				if (nleft > 0) FindNext(nr, nc);
				BackTrack(nr, nc, nleft);
				
				undo(r, c, size);
				used[size]--;
			}
		}
	}
	return;
}

