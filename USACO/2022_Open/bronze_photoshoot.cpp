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
	string s;
	cin >> s;
	int count = 0;
	int prev = 0;
	for(int i = 0; i < n; i+=2) {
		if(s[i] == 'G' && s[i+1] == 'H') {
			if(prev == 1)
				count+=2;
			else if(prev == 0)
				count++;
			prev = -1;
		}
		else if(s[i] == 'H' && s[i+1] == 'G') {
			prev = 1;
		}
	}
	cout << count << "\n";
}