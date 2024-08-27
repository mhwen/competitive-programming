#include <iostream>
#include <vector>

using namespace std;

typedef long long ll;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	vector<int> minNeeded(2e5+1);
	minNeeded[0] = 0;
	
	for(int i = 1; i < (int)minNeeded.size(); i++) {
		minNeeded[i] = minNeeded[i/2]+1;
	}
	int t;
	cin >> t;
	while(t-->0) {
		string s;
		cin >> s;
		int best = 2e5+1;
		for(char c = 'a'; c <= 'z'; c++) {
			int needed = 0;
			int curr = 0;
			for(char ch : s) {
				if(ch != c) {
					curr++;
				}
				else {
					needed = max(needed, minNeeded[curr]);
					curr = 0;
				}
			}
			needed = max(needed, minNeeded[curr]);
			best = min(best, needed);
		}
		cout << best << "\n";
	}
}