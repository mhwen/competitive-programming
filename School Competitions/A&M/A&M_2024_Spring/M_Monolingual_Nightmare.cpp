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

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n, l, q;
	cin >> n >> l >> q;
	map<string, string> dict;
	set<string> eng;
	for(int i = 0; i < n; i++) {
		string s, t, h;
		cin >> s >> h >> t;
		dict[t] = s;
		eng.insert(s);
	}
	vector<string> convo(l);
	for(int i = 0; i < l; i++) {
		cin >> convo[i];
	}
	while(q-->0) {
		bool good = true;
		for(int i = 0; i < l; i++) {
			string word;
			cin >> word;
			if(convo[i] == "???") {
				if(eng.count(word))
					good = false;
			}
			else {
				if(word != dict[convo[i]])
					good = false;
			}
		}
		if(good)
			cout << "YES\n";
		else
			cout << "NO\n";
	}
}