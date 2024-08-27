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
		string s;
		cin >> s;
		int plus = 0, minus = 0;
		for(char c : s) {
			if(c == '+')
				plus++;
			else
				minus++;
		}
		cout << max(plus, minus)-min(plus, minus) << "\n";
	}
}