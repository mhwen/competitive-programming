#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <map>
#include <set>
#include <stack>
#include <functional>
#include <cmath>
#include <numeric>
#include <iomanip>

using namespace std;
typedef long long ll;
typedef long double ld;
#define sz(x) (int)(x).size()
#define all(x) begin(x), end(x)

int dx[4] = {0, 1, 0, -1};
int dy[4] = {1, 0, -1, 0};

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int tx, ty;
	cin >> tx >> ty;
	int n;
	cin >> n;
	vector<string> ins(n);
	for(string& s : ins)
		cin >> s;
	
	auto simulate = [&]() {
		int d = 0;
		int x = 0, y = 0;
		for(string& s : ins) {
			if(s == "Forward") {
				x += dx[d];
				y += dy[d];
			}
			else if(s == "Left") {
				d--;
				d = (d+4)%4;
			}
			else {
				d++;
				d = (d+4)%4;
			}
		}
		return x == tx && y == ty;
	};
	int id = -1;
	string ans;
	string com[3] = {"Forward", "Left", "Right"};
	for(int i = 0; i < n; i++) {
		string old = ins[i];
		bool found = false;
		for(string c : com) {
			ins[i] = c;
			if(simulate()) {
				id = i+1;
				ans = c;
				found = true;
				break;
			}
		}
		ins[i] = old;
		if(found)
			break;
	}
	cout << id << " " << ans << "\n";
}