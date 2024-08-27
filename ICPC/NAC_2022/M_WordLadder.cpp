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
#define sz(x) (int)(x).size()

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n;
	cin >> n;
	string curr = "aaaaaaaaaa";
	vector<string> ladder{curr};
	
	auto check = [&](string s) {
		for(int i = 0; i < sz(ladder)-1; i++) {
			int diff = 0;
			for(int j = 0; j < 10; j++) {
				if(ladder[i][j] != s[j])
					diff++;
			}
			if(diff <= 1)
				return false;
		}
		return true;
	};
	
	for(int i = 1; i < n; i++) {
		bool found = false;
		while(!found) {
			int id = rand()%10;
			char ch = (char)(rand()%26+'a');
			if(ch == curr[id])
				continue;
			string hold = curr;
			hold[id] = ch;
			if(check(hold)) {
				found = true;
				curr = hold;
				ladder.push_back(curr);
			}
		}
	}
	for(string s : ladder)
		cout << s << "\n";
}