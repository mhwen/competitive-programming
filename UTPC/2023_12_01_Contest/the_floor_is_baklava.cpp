#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <map>
#include <set>
#include <functional>

using namespace std;

typedef long long ll;
constexpr ll INF = 1e9;


//Hehe flow go brrr
struct FlowEdge {
    int v, u;
    ll cap, flow = 0;
    FlowEdge(int V, int U, ll c) : v(V), u(U), cap(c) {}
};

struct Dinic {
    const long long flow_inf = 1e18;
    vector<FlowEdge> edges;
    vector<vector<int>> adj;
    int n, m = 0;
    int s, t;
    vector<int> level, ptr;
    queue<int> q;

    Dinic(int N, int S, int T) : n(N), s(S), t(T) {
        adj.resize(n);
        level.resize(n);
        ptr.resize(n);
    }

    void add_edge(int v, int u, ll cap) {
        edges.emplace_back(v, u, cap);
        edges.emplace_back(u, v, 0);
        adj[v].push_back(m);
        adj[u].push_back(m + 1);
        m += 2;
    }

    bool bfs() {
        while (!q.empty()) {
            int v = q.front();
            q.pop();
            for (int id : adj[v]) {
                if (edges[id].cap - edges[id].flow < 1)
                    continue;
                if (level[edges[id].u] != -1)
                    continue;
                level[edges[id].u] = level[v] + 1;
                q.push(edges[id].u);
            }
        }
        return level[t] != -1;
    }

    long long dfs(int v, long long pushed) {
        if (pushed == 0)
            return 0;
        if (v == t)
            return pushed;
        for (int& cid = ptr[v]; cid < (int)adj[v].size(); cid++) {
            int id = adj[v][cid];
            int u = edges[id].u;
            if (level[v] + 1 != level[u] || edges[id].cap - edges[id].flow < 1)
                continue;
            long long tr = dfs(u, min(pushed, edges[id].cap - edges[id].flow));
            if (tr == 0)
                continue;
            edges[id].flow += tr;
            edges[id ^ 1].flow -= tr;
            return tr;
        }
        return 0;
    }

    long long flow() {
        ll f = 0;
        while (true) {
            fill(level.begin(), level.end(), -1);
            level[s] = 0;
            q.push(s);
            if (!bfs())
                break;
            fill(ptr.begin(), ptr.end(), 0);
            while (long long pushed = dfs(s, flow_inf)) {
                f += pushed;
            }
        }
        return f;
    }
};

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n, m;
	cin >> n >> m;
	vector<vector<int>> inId(n, vector<int>(m));
	vector<vector<int>> outId(n, vector<int>(m));
	vector<vector<pair<int, ll>>> con(n*m*2+2);
	vector<vector<ll>> weight(n, vector<ll>(m));
	
	Dinic d(n*m*2, 1, n*m*2-2);
	
	int id = 0;
	for(int r = 0; r < n; r++) {
		for(int c = 0; c < m; c++) {
			cin >> weight[r][c];
			inId[r][c] = id++;
			outId[r][c] = id++;
		}
	}
	for(int r = 0; r < n; r++) {
		for(int c = 0; c < m; c++) {
			d.add_edge(inId[r][c], outId[r][c], weight[r][c]);
			con[inId[r][c]].push_back({outId[r][c], weight[r][c]});
			if(r > 0) {
				d.add_edge(outId[r][c], inId[r-1][c], INF);
				con[outId[r][c]].push_back({inId[r-1][c], INF});
			}
			if(c > 0) {
				d.add_edge(outId[r][c], inId[r][c-1], INF);
				con[outId[r][c]].push_back({inId[r][c-1], INF});
			}
			if(r < n-1) {
				d.add_edge(outId[r][c], inId[r+1][c], INF);
				con[outId[r][c]].push_back({inId[r+1][c], INF});
			}
			if(c < m-1) {
				d.add_edge(outId[r][c], inId[r][c+1], INF);
				con[outId[r][c]].push_back({inId[r][c+1], INF});
			}
		}
	}
	
	cout << d.flow() << "\n";
	
}