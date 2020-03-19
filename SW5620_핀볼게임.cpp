//SW 5650. 핀볼 게임
//90도 회전이 아니라면 지금까지의 경로를 그대로 따라간다 -> 점수는 *2 -1
//굳이 vis check 안해도댐.
//Simulation 

#include <iostream>
#include <algorithm>
#include <vector>

#define EAST 0
#define WEST 1
#define NORTH 2
#define SOUTH 3

using namespace std;
using pii = pair<int, int>;

const int dr[] = {0, 0, -1, 1};
const int dc[] = {1, -1, 0, 0};
int ans = 0;

//called only block is 1~5
int setdir(int block, int dir) {
    if (block == 1) {
        if (dir == SOUTH) return EAST;
        else if (dir == WEST) return NORTH;
    } else if (block == 2) {
        if (dir == NORTH) return EAST;
        else if (dir == WEST) return SOUTH;
    } else if (block == 3) {
        if (dir == EAST) return SOUTH;
        else if (dir == NORTH) return WEST;
    } else if (block == 4) {
        if (dir == EAST) return NORTH;
        else if (dir == SOUTH) return WEST;
    }
    //되돌아 나오는 경우
    return -1;
}

void simul(int r, int c, int d, int size, const vector<vector<int>> &board, const vector<pii> worm[5]) {

    int ret = 0;
    int nr = r, nc = c, dir = d;

    do {
        //튕기는 벽
        if (1 <= board[nr][nc] && board[nr][nc] <= 5) {
            ret++;
            dir = setdir(board[nr][nc], dir);
            if (dir == -1) break;
        }
        //wormhole
        else if (6 <= board[nr][nc] && board[nr][nc] <= 10) {
            pii a = worm[board[nr][nc] - 6][0];
            pii b = worm[board[nr][nc] - 6][1];
            if (nr == a.first && nc == a.second)
                nr = b.first, nc = b.second;
            else
                nr = a.first, nc = a.second;
            }
        //블랙홀에 빠진 경우
        else if (board[nr][nc] == -1) {
            ans = max(ret, ans);
            return;
        }
        nr += dr[dir], nc += dc[dir];
    } while (nr != r || nc != c);

    //반대 방향으로 되돌아 나온 경우
    if (nr != r && nc != c) ans = max(2 * ret - 1, ans);
    //자기 자리 돌아온경우
    else ans = max(ret, ans);
    return;
}

int main() {

    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int tc;
    cin >> tc;

    for (int c = 1; c <= tc; c++) {
        int n;
        cin >> n;
        ans = 0;
        vector<vector<int>> board;
        vector<pii> wormhole[5];
        //0, n+1 - > 5로 set
        board.assign(n + 2, vector<int>(n + 2));
        for (int i = 0; i < n + 2; i++) board[0][i] = board[i][0] = board[i][n + 1] = board[n + 1][i] = 5;

        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                cin >> board[i][j];
                //wormhole
                if (6 <= board[i][j] && board[i][j] <= 10)
                    wormhole[board[i][j] - 6].emplace_back(pii(i, j));
            }
        }

        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                if (board[i][j] == 0) {
                    for (int dir = 0; dir <= 3; dir++) {
                        simul(i,j,dir, n, board, wormhole);
                    }
                }
            }
        }

        cout << "#" << c << ' ' << ans << '\n';
    }

    return 0;
}
