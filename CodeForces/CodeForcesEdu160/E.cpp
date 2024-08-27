#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <map>
#include <set>
#include <functional>

using namespace std;

typedef long long ll;


//flow go brrr
struct Edge
{
    int from, to, capacity, cost;
};

vector<vector<int>> adj, cost, capacity;

const int INF = 1e9;

void shortest_paths(int n, int v0, vector<int>& d, vector<int>& p) {
    d.assign(n, INF);
    d[v0] = 0;
    vector<bool> inq(n, false);
    queue<int> q;
    q.push(v0);
    p.assign(n, -1);

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        inq[u] = false;
        for (int v : adj[u]) {
            if (capacity[u][v] > 0 && d[v] > d[u] + cost[u][v]) {
                d[v] = d[u] + cost[u][v];
                p[v] = u;
                if (!inq[v]) {
                    inq[v] = true;
                    q.push(v);
                }
            }
        }
    }
}

int min_cost_flow(int N, vector<Edge> edges, int K, int s, int t) {
    adj.assign(N, vector<int>());
    cost.assign(N, vector<int>(N, 0));
    capacity.assign(N, vector<int>(N, 0));
    for (Edge e : edges) {
        adj[e.from].push_back(e.to);
        adj[e.to].push_back(e.from);
        cost[e.from][e.to] = e.cost;
        cost[e.to][e.from] = -e.cost;
        capacity[e.from][e.to] = e.capacity;
    }

    int flow = 0;
    int Cost = 0;
    vector<int> d, p;
    while (flow < K) {
        shortest_paths(N, s, d, p);
        if (d[t] == INF)
            break;

        // find max flow on that path
        int f = K - flow;
        int cur = t;
        while (cur != s) {
            f = min(f, capacity[p[cur]][cur]);
            cur = p[cur];
        }

        // apply flow
        flow += f;
        Cost += f * d[t];
        cur = t;
        while (cur != s) {
            capacity[p[cur]][cur] -= f;
            capacity[cur][p[cur]] += f;
            cur = p[cur];
        }
    }

    if (flow < K)
        return -INF;
    else
        return Cost;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n, m;
	cin >> n >> m;
	vector<Edge> edges;
	
	int source = 0;
	//rows: 1 to n
	//cols: n+1 to n+m
	int sink = n+m+1;
	
	int myCost = 0;
	for(int r = 1; r <= n; r++) {
		for(int c = n+1; c <= n+m; c++) {
			int val;
			cin >> val;
			myCost += val;
			if(val == 0)
				edges.emplace_back(r, c, 1, 1);
			else
				edges.emplace_back(r, c, 1, -1);
		}
	}

	int rowWanted = 0;
	for(int r = 1; r <= n; r++) {
		int amt;
		cin >> amt;
		rowWanted += amt;
		edges.emplace_back(source, r, amt, 0);
	}
	int colWanted = 0;
	for(int c = n+1; c <= n+m; c++) {
		int amt;
		cin >> amt;
		colWanted += amt;
		edges.emplace_back(c, sink, amt, 0);
	}
	
	int res = min_cost_flow(sink+1, edges, colWanted, 0, sink);
	if(res == -INF || rowWanted != colWanted)
		cout << -1 << "\n";
	else
		cout << res+myCost << "\n";
	
}