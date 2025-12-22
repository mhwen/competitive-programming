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
typedef long double ld;
#define sz(x) (int)(x).size()
#define all(x) begin(x), end(x)

constexpr int INF = 1e9;

struct segtree {
    int n;
    vector<int> st, lazy;

    segtree(int _n) : n(_n), st(4 * _n, INF), lazy(4 * _n) {}

#define lc 2 * v
#define rc 2 * v + 1
#define m (l + r) / 2

    void push(int v, int l, int r) {
        if (l != r) {
            lazy[lc] += lazy[v];
            lazy[rc] += lazy[v];
        }

        st[v] += lazy[v];
        lazy[v] = 0;
    }

    void upd(int x, int y, int q) { return upd(1, 0, n-1, x, y, q); }
    void upd(int v, int l, int r, int x, int y, int q) {
        push(v, l, r);
        if (r < x || l > y) return;
        if (x <= l && r <= y) {
            lazy[v] += q;
            push(v, l, r);
        } else {
            upd(lc, l, m, x, y, q);
            upd(rc, m+1, r, x, y, q);
            st[v] = min(st[lc], st[rc]);
        }
    }

    void set(int x, int q) { set(1, 0, n-1, x, q); }
    void set(int v, int l, int r, int x, int q) {
        push(v, l, r);
        if (l == r) {
            st[v] = q;
        } else {
            if (x <= m) {
                set(lc, l, m, x, q);
            } else {
                set(rc, m+1, r, x, q);
            }
            st[v] = min(st[lc], st[rc]);
        }
    }

    int qry(int x, int y) { return qry(1, 0, n-1, x, y); }
    int qry(int v, int l, int r, int x, int y) {
        push(v, l, r);
        if (r < x || l > y) return INF;
        if (x <= l && r <= y) {
            return st[v];
        } else {
            return min(qry(lc, l, m, x, y), qry(rc, m+1, r, x, y));
        }
    }

#undef lc
#undef rc
#undef m
};

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n, me, k;
	cin >> n >> me >> k;
	me--;
	vector<int> heights(n);
	for(int i = 0; i < n; i++) {
		cin >> heights[i];
	}
	
	vector<int> coords{heights[me]};
	vector<int> buildings;
	for(int i = me+1; i < n; i++) {
		if(heights[i] > heights[me]) {
			coords.push_back(heights[i]);
			buildings.push_back(heights[i]);
		}
	}
	sort(all(coords));
	coords.erase(unique(all(coords)), coords.end());
	auto compress = [&](int h) {
		return (int)(lower_bound(all(coords), h) - coords.begin());
	};
	
	vector<segtree> dp(k, segtree(sz(coords)));
	dp[0].set(0, 0);

	for(int height : buildings) {
		int i = compress(height);
		//do queries
		for(int K = 1; K < k; K++) {
			int myBest = dp[K-1].qry(0, i-1);
			if(myBest < dp[K].qry(i, i))
				dp[K].set(i, myBest);
		}
		//do updates
		for(int K = 0; K < k; K++) {
			dp[K].upd(0, i-1, 1);
		}
	}
	
	int res = dp[k-1].qry(0, sz(coords));
	if(res < INF) {
		int left = 0;
		for(int i = 0; i < me; i++) {
			if(heights[i] >= heights[me])
				left++;
		}
		cout << res+left << "\n";
	}	
	else
		cout << -1 << "\n";
}