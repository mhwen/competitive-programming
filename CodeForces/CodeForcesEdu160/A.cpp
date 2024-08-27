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
		bool found = false;
		for(int i = 0; i < (int)s.length()-1; i++) {
			if(s[i+1] != '0') {
				string left = s.substr(0, i+1);
				string right = s.substr(i+1, s.length()-i-1);
				if(stoi(left) < stoi(right)) {
					cout << left << " " << right << "\n";
					found = true;
					break;
				}
			}
		}
		if(!found)
			cout << "-1\n";
	}
}