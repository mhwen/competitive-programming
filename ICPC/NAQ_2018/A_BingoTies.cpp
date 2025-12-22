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

typedef vector<vector<int>> board;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n;
	cin >> n;
	vector<board> b(n);
	for(int i = 0; i < n; i++) {
		board B(5, vector<int>(5));
		for(int r = 0; r < 5; r++) {
			for(int c = 0; c < 5; c++) {
				cin >> B[r][c];
			}
		}
		b[i] = B;
	}
	vector<bool> seen(3001);
	auto check = [&]() {
		for(board& B : b) {
			for(auto& v : B) {
				int cnt = 0;
				for(auto& num : v) {
					if(seen[num])
						cnt++;
				}
				if(cnt == 5)
					return false;
			}
		}
		return true;
	};
	pair<int, int> ans{-1, -1};
	for(int i = 0; i < n; i++) {
		for(int j = i+1; j < n; j++) {
			for(auto& v : b[i]) {
				for(auto& u : b[j]) {
					vector<int> both;
					both.insert(both.end(), all(v));
					both.insert(both.end(), all(u));
					sort(all(both));
					for(auto val : both)
						seen[val] = true;
					for(int I = 0; I < sz(both)-1; I++) {
						if(both[I] == both[I+1]) {
							seen[both[I]] = false;
							if(check()) {
								ans = {i+1, j+1};
								goto A;
							}
							seen[both[I]] = true;
						}
					}
					for(auto val : both)
						seen[val] = false;
				}
			}
		}
	}
	A:
	if(ans == pair{-1, -1})
		cout << "no ties\n";
	else
		cout << ans.first << " " << ans.second << "\n";
}