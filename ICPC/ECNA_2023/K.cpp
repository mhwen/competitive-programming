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
	int n;
	cin >> n;
	vector<string> words(n);
	for(int i = 0; i < n; i++)
		cin >> words[i];
		
	map<string, int> seen;
	
	for(int i = 0; i < n; i++) {
		for(int j = i+1; j < n; j++) {
			if(words[i].length() != words[j].length())
				continue;
			int diff = 0;
			int firstDiff = -1;
			for(int id = 0; id < (int)words[i].length(); id++) {
				if(words[i][id] != words[j][id]) {
					diff++;
					if(firstDiff == -1)
						firstDiff = id;
				}
			}
			if(diff != 2)
				continue;
			if(words[i][firstDiff+1] == words[j][firstDiff+1])
				continue;
			string first = string(1, words[i][firstDiff])+string(1, words[i][firstDiff+1]);
			string second = string(1, words[j][firstDiff])+string(1, words[j][firstDiff+1]);
			if(first[0] > second[0])
				swap(first, second);
			int prefix = firstDiff;
			int totalLen = (int)words[i].length();
			string hash = to_string(prefix)+first+second+to_string(totalLen);
			seen[hash]++;
		}
	}
	ll ans = 0;
	for(auto key : seen)
		if(key.second == 1)
			ans++;
			
	cout << ans << "\n";
}