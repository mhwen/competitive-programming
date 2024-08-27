#include <iostream>
#include <vector>

using namespace std;

typedef long long ll;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n, q;
	cin >> n >> q;
	vector<int> nums(n);
	vector<int> count(n+1);
	int prev = -1;
	int curr = 0;
	bool down = false;
	for(int i = 0; i < n; i++) {
		cin >> nums[i];
		if(nums[i] > prev) {
			curr++;
			down = false;
		}
		else {
			if(!down) {
				curr++;
				down = true;
			}
		}
		prev = nums[i];
		count[i+1] = curr;
	}
	// for(auto i : count)
		// cout << i << " ";
	// cout << endl;
	for(int i = 0; i < q; i++) {
		int a, b;
		cin >> a >> b;
		int fix = 0;
		if(b-a > 0 && a > 1 && nums[a-2] >= nums[a-1] && nums[a-1] >= nums[a])
			fix = 1;
		cout << count[b]-count[a]+1+fix << "\n";
	}
}