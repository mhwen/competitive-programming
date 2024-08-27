#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <map>
#include <set>
#include <stack>
#include <functional>

using namespace std;

typedef long long ll;
constexpr ll INF = 1e9;

bool isVowel(char c) {
	return c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U' || c == 'Y';
}

int check(int mask, string& s, int amt) {
	if(amt > (int)s.length())
		return -1;
	int newMask = mask;
	newMask <<= amt;
	int sMask = 0;
	for(int i = 0; i < amt; i++) {
		sMask *= 2;
		if(!isVowel(s[i]))
			sMask++;
	}
	newMask += sMask;
	int hold = newMask;
	while(hold > 0) {
		if((hold & 7) == 7)
			return -1;
		hold /= 2;
	}
	return newMask & 3;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n;
	cin >> n;
	vector<string> words(n);
	for(int i = 0; i < n; i++) {
		cin >> words[i];
	}
	vector<vector<ll>> best(n+1, vector<ll>(4, INF));
	
	//0 - vv
	//1 - vc
	//2 - cv
	//3 - cc
	
	best[0][0] = 0;
	for(int i = 0; i < n; i++) {
		for(int before = 0; before < 4; before++) {
			for(int amt = 1; amt <= 3; amt++) {
				int res = check(before, words[i], amt);
				if(res != -1) {
					best[i+1][res] = min(best[i+1][res], best[i][before]+amt);
				}
			}
		}
	}
	ll ans = INF;
	for(int i = 0; i < 4; i++) {
		ans = min(ans, best[n][i]);
	}
	if(ans == INF)
		cout << "*";
	else
		cout << ans << "\n";
	
}