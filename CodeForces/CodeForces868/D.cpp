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
		int n, k;
		cin >> n >> k;
		vector<int> lengths(k);
		for(int i = 0; i < k; i++) {
			cin >> lengths[i];
		}
		vector<int> counts(k);
		for(int i = 0; i < k; i++) {
			cin >> counts[i];
		}
		int count = 3;
		int len = 3;
		bool bad = false;
		string ans = "abc";
		int counter = 0;
		for(int i = 0; i < k ; i++) {
			if(lengths[i]-len < counts[i]-count) {
				bad = true;
				break;
			}
			for(int j = 0; j < counts[i]-count; j++) {
				ans += (char)('a'+i+3);
			}
			for(int j = counts[i]-count; j < lengths[i]-len; j++) {
				ans += (char)('a'+(counter%3));
				counter++;
			}
			count = counts[i];
			len = lengths[i];
		}
		if(bad)
			cout << "NO\n";
		else {
			cout << "YES\n";
			cout << ans << "\n";
		}
	}
}