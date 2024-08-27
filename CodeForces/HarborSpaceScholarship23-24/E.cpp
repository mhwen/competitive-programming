#include <iostream>
#include <vector>

using namespace std;

typedef long long ll;

constexpr ll MOD = 998244353;

struct Node {
	Node* one;
	Node* zero;
	int size;
	Node() : one(0), zero(0), size(0) {}
};

ll pow(ll a, ll b) {
	if(b == 0)
		return 1;
	ll res = pow(a, b/2);
	res = res*res%MOD;
	if(b%2==1)
		res=res*a%MOD;
	return res;
}

ll modInv(ll a, ll p) {
	return pow(a, p-2);
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t;
	cin >> t;
	while(t-->0) {
		ll n;
		cin >> n;
		vector<int> nums(n);
		Node* root = new Node();
		for(int i = 0; i < n; i++) {
			cin >> nums[i];
			Node* curr = root;
			for(int b = 29; b >= 0; b--) {		
				if(nums[i]&(1<<b)) {
					if(curr->one == 0)
						curr->one = new Node();
					curr = curr->one;
				}
				else {
					if(curr->zero == 0)
						curr->zero = new Node();
					curr = curr->zero;
				}
				curr->size++;
			}
		}
		ll count = 0;
		for(int i = 0; i < n; i++) {
			int bits = 0;
			Node* curr = root;
			for(int b = 29; b >= 0; b--) {
				if(nums[i]&(1<<b)) {
					bits++;
					if(curr->zero != 0)
						count += (bits+1)*curr->zero->size;
					curr = curr->one;
				}
				else {
					if(curr->one != 0)
						count += (bits+1)*curr->one->size;
					curr = curr->zero;
				}
				count %= MOD;
			}
			count += (bits+1)*curr->size;
			count %= MOD;
			// cout << count << "\n";
		}
		// cout << count << "\n";
		cout << count*modInv(n*n%MOD, MOD)%MOD << "\n";
	}
}