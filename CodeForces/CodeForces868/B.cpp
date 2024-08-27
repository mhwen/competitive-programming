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
		vector<int> nums(n);
		for(int i = 0; i < n; i++) {
			cin >> nums[i];
		}
		int off = 0;
		for(int start = 0; start < k; start++) {
			for(int j = start; j < n; j+=k) {
				if((nums[j]-1)%k != start)
					off++;
			}
		}
		if(off == 0)
			cout << 0 << "\n";
		else if(off <= 2)
			cout << 1 << "\n";
		else
			cout << -1 << "\n";
	}
}