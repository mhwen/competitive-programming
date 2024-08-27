#include <iostream>
#include <vector>

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
		int stack = 0;
		int sorted = 1;
		bool notSorted = false;
		int notSortedId = 1e9;
		bool valid = true;
		for(char c : s) {
			if(c == '+')
				stack++;
			else if(c == '-') {
				if(stack == notSortedId) {
					notSorted = false;
					notSortedId = 1e9;
				}
				stack--;
				sorted = max(1, min(sorted, stack));
			}
			else if(c == '1') {
				if(notSorted) {
					valid = false;
					break;
				}
				sorted = max(1, stack);
			}
			else {
				if(stack <= sorted) {
					valid = false;
					break;
				}
				notSorted = true;
				notSortedId = min(notSortedId, stack);
			}
		}
		if(valid)
			cout << "YES\n";
		else
			cout << "NO\n";
	}
}