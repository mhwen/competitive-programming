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

void update(int curr, int pos, int currL, int currR, int val, vector<int>& tree) {
	if(pos > currR || pos < currL)
		return;
	if(currL == currR) {
		tree[curr] = val;
		return;
	}
	int mid = (currL+currR)/2;
	update(curr*2, pos, currL, mid, val, tree);
	update(curr*2+1, pos, mid+1, currR, val, tree);
	tree[curr] = max(tree[curr*2], tree[curr*2+1]);
}

int query(int curr, int currL, int currR, int maxId, int threshold, vector<int>& tree) {
	if(tree[curr] < threshold || currL >= maxId)
		return -1;
	if(currL == currR)
		return currL;
	int mid = (currL+currR)/2;
	int rightQ = query(curr*2+1, mid+1, currR, maxId, threshold, tree);
	if(rightQ != -1)
		return rightQ;
	return query(curr*2, currL, mid, maxId, threshold, tree);
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int q;
	cin >> q;
	vector<int> tree(4*(q+1));
	for(int id = 1; id <= q; id++) {
		int type;
		cin >> type;
		if(type == 1) {
			int x;
			cin >> x;
			update(1, id, 0, q, x, tree);
		}
		else {
			int y, k;
			cin >> y >> k;
			vector<int> ans;
			int index = id;
			for(int i = 0; i < k; i++) {
				index = query(1, 0, q, index, y, tree);
				if(index == -1)
					break;
				ans.push_back(index);
			}
			cout << ans.size() << "\n";
			for(int i : ans)
				cout << i << " ";
			cout << "\n";
		}
	}
}