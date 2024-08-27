#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <map>
#include <set>
#include <functional>

using namespace std;

typedef long long ll;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t;
	cin >> t;
	while(t-->0) {
		string s;
		cin >> s;
		int zeros = 0, ones = 0;
		for(char c : s) {
			if(c=='1')
				ones++;
			else
				zeros++;
		}
		int best = 0;
		int currZ = 0, currO = 0;
		for(int i = 0; i < (int)s.length(); i++) {
			if(s[i]=='1')
				currO++;
			else
				currZ++;
			if(currO <= zeros && currZ <= ones)
				best = i+1;
		}
		cout << s.length()-best << "\n";
	}
}