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

void update(int p, vector<ll>& tree) {
	int n = (int)tree.size()/2;
	p += n;
	while(p > 0) {
		tree[p]++;
		p >>= 1;
	}
}

ll query(int l, int r, vector<ll>& tree) {
	int n = (int)tree.size()/2;
	l+=n; r+=n;
	ll res = 0;
	for(; l <= r; l>>=1, r>>=1) {
		if(l%2==1) {
			res += tree[l];
			l++;
		}
		if(r%2==0) {
			res += tree[r];
			r--;
		}
	}
	return res;
}

ll countInversions(vector<int>& nums) {
	int n = (int)nums.size();
	vector<ll> tree(2*n);
	ll count = 0;
	for(int i = 0; i < n; i++) {
		count += query(nums[i]-1, n-1, tree);
		update(nums[i]-1, tree);
	}
	return count;
}


//inversion in p -> contribute 1 (flip)
//regular in p -> contribute 0 or 2 (stay)

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t;
	cin >> t;
	while(t-->0) {
		int n;
		ll k;
		cin >> n >> k;
		vector<int> perm(n);
		for(int i = 0; i < n; i++) {
			int a;
			cin >> a;
			perm[a-1] = i;
		}
		
		ll inversions = 0;
		vector<ll> tree(2*n);
		vector<ll> inv(n);
		vector<ll> gain(n);
		for(int i = 0; i < n; i++) {
			inv[i] = query(perm[i], n-1, tree);
			gain[i] = i-inv[i];
			inversions += inv[i];
			update(perm[i], tree);
		}
		if(inversions > k || (k-inversions)%2==1 || k>(ll)n*(n-1)-inversions) {
			cout << "NO\n";
		}
		else {
			cout << "YES\n";
			vector<int> ans(n);
			vector<bool> used(n+1);
			int id = 1;
			for(int i = n-1; i >= 0; i--) {
				if(inversions+2*gain[i] <= k) {
					inversions += 2*gain[i];
					ans[i] = id;
					used[id] = true;
					id++;
				}
				else {
					int needed = (int)(k-inversions)/2;
					id = n;
					for(int j = i-1; j >= 0; j--) {
						if(needed == 0)
							break;
						if(perm[j] < perm[i]) {
							needed--;
						}
						id--;
					}
					ans[i] = id;
					used[id] = true;
					break;
				}
			}
			int usedId = 1;
			for(int i = 0; i < n; i++) {
				if(ans[i] != 0)
					continue;
				while(used[usedId])
					usedId++;
				ans[i] = usedId;
				usedId++;
			}
			for(int i : ans)
				cout << i << " ";
			cout << "\n";
			
			vector<int> moved(n);
			for(int i = 0; i < n; i++) {
				moved[perm[i]] = ans[i];
			}

			// cout <<  countInversions(ans) << " and " << countInversions(moved) << endl;
		}

	}
}