#include <iostream>
#include <vector>
#include <algorithm>

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
		int zero = 0, one = 0;
		vector<int> nums(n);
		vector<int> preXor(n+1);
		for(int i = 0; i < n; i++) {
			cin >> nums[i];
			preXor[i+1] = preXor[i]^nums[i];
		}
		string s;
		cin >> s;
		for(int i = 0; i < n; i++) {
			if(s[i] == '0')
				zero ^= nums[i];
			else
				one ^= nums[i];
		}
		int q;
		cin >> q;
		while(q-->0) {
			int type;
			cin >> type;
			if(type == 1) {
				int l, r;
				cin >> l >> r;
				zero ^= preXor[r]^preXor[l-1];
				one ^= preXor[r]^preXor[l-1];
			}
			else {
				int query;
				cin >> query;
				if(query == 0)
					cout << zero << " ";
				else
					cout << one << " ";
			}
		}
		cout << "\n";
	}
}