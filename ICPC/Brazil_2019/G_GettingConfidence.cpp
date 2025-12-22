#include <bits/stdc++.h>
#include <bits/extc++.h>

using namespace std;
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef long double ld;

const ll INF = 1e18;

struct MCMF {
	struct edge {
		int from, to, rev;
		ll cap;
		ld cost;
		ll flow;
	};
	int N;
	vector<vector<edge>> ed;
	vi seen;
	vector<ld> dist, pi;

	MCMF(int xN) : N(xN), ed(xN), seen(xN), dist(xN), pi(xN), par(xN) {}

	void addEdge(int from, int to, ll cap, ld cost) {
		if (from == to) return;
		ed[from].push_back(edge{ from,to,sz(ed[to]),cap,cost,0 });
		ed[to].push_back(edge{ to,from,sz(ed[from])-1,0,-cost,0 });
	}

	void path(int s) {
		fill(all(seen), 0);
		fill(all(dist), INF);
		dist[s] = 0; ld di;

		__gnu_pbds::priority_queue<pair<ll, int>> q;
		vector<decltype(q)::point_iterator> its(N);
		q.push({ 0, s });

		while (!q.empty()) {
			s = q.top().second; q.pop();
			seen[s] = 1; di = dist[s] + pi[s];
			for (edge& e : ed[s]) if (!seen[e.to]) {
				ld val = di - pi[e.to] + e.cost;
				if (e.cap - e.flow > 0 && val < dist[e.to]) {
					dist[e.to] = val;
					par[e.to] = &e;
					if (its[e.to] == q.end())
						its[e.to] = q.push({ -dist[e.to], e.to });
					else
						q.modify(its[e.to], { -dist[e.to], e.to });
				}
			}
		}
		rep(i,0,N) pi[i] = min(pi[i] + dist[i], (ld)INF);
	}

	pair<vector<pair<int, int>>, pair<ll, ld>> maxflow(int s, int t) {
		ll totflow = 0;
		ld totcost = 0;
		vector<pair<int, int>> taken;
		while (path(s), seen[t]) {
			ll fl = INF;
			for (edge* x = par[t]; x; x = par[x->from])
				fl = min(fl, x->cap - x->flow);

			totflow += fl;
			for (edge* x = par[t]; x; x = par[x->from]) {
				x->flow += fl;
				ed[x->to][x->rev].flow -= fl;
			}
		}
		rep(i,0,N) for(edge& e : ed[i]) {
			totcost += e.cost * e.flow;
			if(e.flow > 0)
				taken.push_back({e.from, e.to});
		}
		return {taken, {totflow, totcost/2}};
	}

	// If some costs can be negative, call this before maxflow:
	void setpi(int s) { // (otherwise, leave this out)
		fill(all(pi), INF); pi[s] = 0;
		int it = N, ch = 1; ld v;
		while (ch-- && it--)
			rep(i,0,N) if (pi[i] != INF)
			  for (edge& e : ed[i]) if (e.cap)
				  if ((v = pi[i] + e.cost) < pi[e.to])
					  pi[e.to] = v, ch = 1;
		assert(it >= 0); // negative cost cycle
	}
};

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n;
	cin >> n;
	//0..n-1, n...2n-1, 2n source, 2n+1 sink
	MCMF flow(2*n+2);
	int source = 2*n;
	int sink = 2*n+1;
	for(int i = 0; i < n; i++) {
		for(int j = n; j < 2*n; j++) {
			ll v;
			cin >> v;
			flow.addEdge(i, j, 1, -log(v)*100);
		}
		flow.addEdge(source, i, 1, 0);
	}
	for(int j = n; j < 2*n; j++) {
		flow.addEdge(j, sink, 1, 0);
	}
	flow.setpi(source);
	auto res = flow.maxflow(source, sink);
	// cout << exp(-res.second.second) << " " << res.second.first << " " << res.second.second << endl;
	vector<int> ans(n);
	for(auto a : res.first) {
		if(a.first != source && a.second != sink) {
			int from = a.first;
			int to = a.second-n;
			ans[to] = from+1;
		}
	}
	for(auto i : ans)
		cout << i << " ";
	cout << "\n";
}