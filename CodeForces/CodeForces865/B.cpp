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
		int n;
		cin >> n;
		cout << "+ " << (n+1) << endl;
		int a;
		cin >> a;
		if(a == -1)
			return 0;
		cout << "+ " << n << endl;
		cin >> a;
		if(a == -1)
			return 0;
		vector<int> nodes;
		int curr = n;
		for(int i = 0; i < n; i++) {
			nodes.push_back(curr);
			curr = n-(curr-1);
			if(i%2==1)
				curr--;
		}
		// for(int i : nodes)
			// cout << i << " ";
		// cout << endl;
		int maxDist = 0;
		int index = -1;
		for(int i = 2; i <= n; i++) {
			cout << "? 1 " << i << endl;
			int res;
			cin >> res;
			if(res == -2)
				return 0;
			if(res > maxDist) {
				maxDist = res;
				index = i;
			}
		}
		vector<int> indices(n);
		indices[index-1] = 0;
		for(int i = 1; i <= n; i++) {
			if(i == index)
				continue;
			cout << "? " << index << " " << i << endl;
			int res;
			cin >> res;
			if(res == -2)
				return 0;
			indices[i-1] = res;
		}
		// for(int i : indices)
			// cout << i << " ";
		// cout << endl;
		string ans = "!";
		for(int& i : indices) {
			ans += (" " + to_string(nodes[i]));
		}
		for(int& i : indices) {
			ans += (" " + to_string(nodes[n-i-1]));
		}
		cout << ans << endl;
		int res;
		cin >> res;
		if(res == -2)
			return 0;
	}

	
}