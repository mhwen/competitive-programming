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
typedef pair<int, int> pii;
typedef vector<int> vi;
#define sz(x) (int)(x).size()
#define all(x) begin(x), end(x)
#define rep(i, a, b) for(int i = a; i < (b); i++)

constexpr int INF = 1e9;

struct SuffixArray {
	vi sa, lcp;
	SuffixArray(string& s, int lim=256) { // or basic_string<int>
		int n = sz(s) + 1, k = 0, a, b;
		vi x(all(s)+1), y(n), ws(max(n, lim)), rank(n);
		sa = lcp = y, iota(all(sa), 0);
		for (int j = 0, p = 0; p < n; j = max(1, j * 2), lim = p) {
			p = j, iota(all(y), n - j);
			rep(i,0,n) if (sa[i] >= j) y[p++] = sa[i] - j;
			fill(all(ws), 0);
			rep(i,0,n) ws[x[i]]++;
			rep(i,1,lim) ws[i] += ws[i - 1];
			for (int i = n; i--;) sa[--ws[x[y[i]]]] = y[i];
			swap(x, y), p = 1, x[sa[0]] = 0;
			rep(i,1,n) a = sa[i - 1], b = sa[i], x[b] =
				(y[a] == y[b] && y[a + j] == y[b + j]) ? p - 1 : p++;
		}
		rep(i,1,n) rank[sa[i]] = i;
		for (int i = 0, j; i < n - 1; lcp[rank[i++]] = k)
			for (k && k--, j = sa[rank[i] - 1];
					s[i + k] == s[j + k]; k++);
	}
};

template<class T>
struct RMQ {
	vector<vector<T>> jmp;
	RMQ(const vector<T>& V) : jmp(1, V) {
		for (int pw = 1, k = 1; pw * 2 <= sz(V); pw *= 2, ++k) {
			jmp.emplace_back(sz(V) - pw * 2 + 1);
			rep(j,0,sz(jmp[k]))
				jmp[k][j] = min(jmp[k - 1][j], jmp[k - 1][j + pw]);
		}
	}
	//[a, b)
	T query(int a, int b) {
		// assert(a < b); // or return inf if a == b
		int dep = 31 - __builtin_clz(b - a);
		return min(jmp[dep][a], jmp[dep][b - (1 << dep)]);
	}
};

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	string line;
	getline(cin, line);
	int n = sz(line);
	SuffixArray SA(line);
	RMQ lcp(SA.lcp);
	vector<int> saPos(n);
	for(int i = 1; i <= n; i++) {
		saPos[SA.sa[i]] = i;
	}
	
	set<int> seen;
	auto query = [&](int i) {
		auto it = seen.upper_bound(i);
		int len = 0;
		if(it != seen.end()) {
			int above = *it;
			len = max(len, lcp.query(i+1, above+1));
		}
		if(it != seen.begin()) {
			it--;
			int below = *it;
			len = max(len, lcp.query(below+1, i+1));
		}
		seen.insert(i);
		return len;
	};
	
	
	vector<int> dp(n+1, INF);
	dp[0] = 0;
	for(int i = 0; i < n; i++) {
		dp[i+1] = min(dp[i+1], dp[i]+1);
		int len = query(saPos[i]);
		dp[i+len] = min(dp[i+len], dp[i]+3);
	}
	cout << dp[n] << "\n";
}