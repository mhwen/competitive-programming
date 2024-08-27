#include <iostream>
#include <vector>
#include <stack>
#include <queue>

using namespace std;

typedef long long ll;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t;
	cin >> t;
	while(t-->0) {
		int k;
		cin >> k;
		ll cost = 0;
		string s;
		cin >> s;
		stack<int> brackets;
		priority_queue<int> segments;
		for(int i = 0; i < (int)s.length(); i++) {
			if(s[i] == '(') {
				brackets.push(i);
			}
			else {
				cost += (i-brackets.top())/2;
				segments.push((i-brackets.top())/2);
				brackets.pop();
			}
		}
		// cout << cost << "\n";
		while(!segments.empty() && k > 0) {
			cost -= segments.top();
			segments.pop();
			k--;
		}
		cout << cost << "\n";
	}
}