#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <map>
#include <set>
#include <stack>
#include <functional>
#include <cmath>
#include <numeric>
#include <iomanip>

using namespace std;
typedef long long ll;
#define sz(x) (int)(x).size()

struct Node {
	int val = 0;
	Node* left = nullptr;
	Node* right = nullptr;
	
	Node(): val(0) {}
	Node(int V): val(V) {}

	Node* L() {
		if(left == nullptr)
			left = new Node();
		return left;
	}
	Node* R() {
		if(right == nullptr)
			right = new Node();
		return right;
	}
};

void update(Node* curr, int l, int r, int L, int R, int v) {
	if(r < L || l > R)
		return;
	if(L <= l && r <= R) {
		curr->val += v;
		return;
	}
	int mid = (l+r)/2;
	if(l != r) {
		update(curr->L(), l, mid, L, R, v);
		update(curr->R(), mid+1, r, L, R, v);
	}
}

int query(Node* curr, int l, int r, int P) {
	if(r < P || l > P)
		return 0;
	if(curr == nullptr)
		return 0;
	int mid = (l+r)/2;
	int res = curr->val;
	if(l != r)
		res += query(curr->left, l, mid, P) + query(curr->right, mid+1, r, P);
	return res;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n, q;
	cin >> n >> q;
	
	Node* root = new Node();
	auto Update = [&](int L, int R, int v) {
		update(root, 1, n, L, R, v);
	};
	auto Query = [&](int N) {
		return query(root, 1, n, N);
	};
	
	vector<set<pair<int, int>>> intervals(q+1);
	
	auto add = [&](int num, int l, int r) {
		auto& Int = intervals[num];
		int minL = l;
		int maxR = r;
		while(true) {
			auto it = Int.upper_bound({r, 1e9});
			//none to left of my right endpoint
			if(it == Int.begin())
				break;
			it--;
			int delL = it->first;
			int delR = it->second;
			//the closest doesn't touch me
			if(delR < l)
				break;
			Update(delL, delR, -1);
			Int.erase(it);
			minL = min(minL, delL);
			maxR = max(maxR, delR);
		}
		Update(minL, maxR, 1);
		Int.insert({minL, maxR});
	};
	
	auto del = [&](int num, int l, int r) {
		auto& Int = intervals[num];
		while(true) {
			auto it = Int.upper_bound({r, 1e9});
			//none to left of my right endpoint
			if(it == Int.begin())
				break;
			it--;
			int delL = it->first;
			int delR = it->second;
			//the closest doesn't touch me
			if(delR < l)
				break;
			Update(delL, delR, -1);
			Int.erase(it);
			if(delL < l) {
				Update(delL, l-1, 1);
				Int.insert({delL, l-1});
			}
			if(delR > r) {
				Update(r+1, delR, 1);
				Int.insert({r+1, delR});
			}
		}
	};
	
	for(int i = 0; i < q; i++) {
		char type;
		cin >> type;
		if(type == '?') {
			int N;
			cin >> N;
			cout << Query(N) << endl;
		}
		else if(type == '+') {
			int l, r, x;
			cin >> l >> r >> x;
			add(x, l, r);
		}
		else {
			int l, r, x;
			cin >> l >> r >> x;
			del(x, l, r);
		}
	}
}