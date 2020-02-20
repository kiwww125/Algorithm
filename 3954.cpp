#include <iostream>
#include <vector>

using namespace std;
using pii = pair<int, int>;

int memsize, opsize, inputsize;
int loop[10000];

void addone(vector<int> &memory, int memp) {
	memory[memp] = memory[memp] == 255 ? 0 : memory[memp] + 1;
}

void minusone(vector<int> &memory, int memp) {
	memory[memp] = memory[memp] == 0 ? 255 : memory[memp] - 1;
}

void moveright(int &memp) {
	memp = memp == memsize - 1 ? 0 : memp + 1;
}

void moveleft(int &memp) {
	memp = memp == 0 ? memsize - 1 : memp - 1;
}

void read(vector<int> &memory, const vector<char> input, int memp, int& inp) {

	if (inp == inputsize) {
		memory[memp] = 255;
	}
	else memory[memp] = input[inp++];
}

int main() {

	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	int tc;
	cin >> tc;

	while (tc--) {

		cin >> memsize >> opsize >> inputsize;

		vector<int> memory(memsize, 0);
		vector<char> opcode(opsize);
		vector<char> input(inputsize);
		vector<int> stack;
		vector<pii> loopset;

		int memp = 0, opp = 0, inp = 0, maxind = 0;

		for (int i = 0; i < opsize; i++) {
			cin >> opcode[i];
			if (opcode[i] == '[') stack.emplace_back(i);
			else if (opcode[i] == ']') {
				int start = stack.back();
				stack.pop_back();
				loop[start] = i;
				loop[i] = start;
			}
		}

		for (int i = 0; i < inputsize; i++) cin >> input[i];

		int cnt = 0;

		while (cnt <= 50000000 && opp != opsize) {

			if (maxind < opp) maxind = opp;

			if (opcode[opp] == '[') {
				if (memory[memp] == 0) {
					opp = loop[opp];
				}
			}
			else if (opcode[opp] == ']') {
				if (memory[memp] != 0)
					opp = loop[opp];
			}
			else if (opcode[opp] == '-') minusone(memory, memp);
			else if (opcode[opp] == '+') addone(memory, memp);
			else if (opcode[opp] == '<') moveleft(memp);
			else if (opcode[opp] == '>') moveright(memp);
			else if (opcode[opp] == ',') read(memory, input, memp, inp);

			opp++;
			cnt++;
		}

		if (opp == opsize) cout << "Terminates\n";
		else cout << "Loops " << loop[maxind] << ' ' << maxind << '\n';
	}

	return 0;
}
