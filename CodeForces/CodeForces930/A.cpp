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
	int t;
	cin >> t;
	while(t-->0) {
		int n;
		cin >> n;
		int mx = 0;
		for(int i = 1; i < n; i++) {
			cout << "? " << mx << " " << mx << " " << i << " " << i << endl;
			char res;
			cin >> res;
			if(res == '<') {
				mx = i;
			}
		}
		vector<int> candidates;
		candidates.push_back(mx);
		for(int i = 0; i < n; i++) {
			if(i == mx)
				continue;
			cout << "? " << mx << " " << candidates.front() << " " << mx << " " << i << endl;
			char res;
			cin >> res;
			if(res == '<') {
				candidates.clear();
				candidates.push_back(i);
			}
			else if(res == '=') {
				candidates.push_back(i);
			}
		}
		int minCandidate = candidates.front();
		for(int c : candidates) {
			cout << "? " << minCandidate << " " << minCandidate << " " << c << " " << c << endl;
			char res;
			cin >> res;
			if(res == '>') {
				minCandidate = c;
			}
		}
		cout << "! " << mx << " " << minCandidate << endl;
	}
	
}