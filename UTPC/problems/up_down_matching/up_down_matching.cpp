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
		map<int, int> sums;
		sums[0] = 0;
		int currSum = 0;
		int best = 0;
		for(int i = 1; i <= n; i++) {
			if(s[i-1] == 'U')
				currSum++;
			else
				currSum--;
				
			if(sums.count(currSum))
				best = max(best, i-sums[currSum]);
			else
				sums[currSum] = i;
		}
		cout << best << "\n";
	}


}