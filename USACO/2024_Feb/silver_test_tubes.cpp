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
		int n, p;
		cin >> n >> p;
		stack<char> a;
		stack<char> b;
		
		string s;
		cin >> s;
		char prev = s[0];
		for(char c : s) {
			if(c != prev)
				a.push(prev);
			prev = c;
		}
		a.push(prev);
		
		cin >> s;
		prev = s[0];
		for(char c : s) {
			if(c != prev)
				b.push(prev);
			prev = c;
		}
		b.push(prev);
		
		stack<char> beaker;
		vector<pair<int, int>> moves;
		while(a.size() > 1) {
			if(a.top() == b.top()) {
				moves.push_back({1, 2});
			}
			else {
				moves.push_back({1, 3});
				if(beaker.empty())
					beaker.push(a.top());
			}
			a.pop();
		}
		if(!beaker.empty() && a.top() == beaker.top()) {
			moves.push_back({1, 3});
			a.pop();
			a.push(b.top());
		}
		while(b.size() > 1) {
			if(b.top() == a.top()) {
				moves.push_back({2, 1});
			}
			else {
				moves.push_back({2, 3});
				if(beaker.empty())
					beaker.push(b.top());
			}
			b.pop();
		}
		if(a.top() == b.top()) {
			moves.push_back({2, 1});
			moves.push_back({3, 2});
		}
		else {
			if(!beaker.empty()) {
				if(beaker.top() == a.top())
					moves.push_back({3, 1});
				else
					moves.push_back({3, 2});
			}
		}
		cout << moves.size() << "\n";
		if(p > 1) {
			for(auto m : moves)
				cout << m.first << " " << m.second << "\n";
		}
	}
}