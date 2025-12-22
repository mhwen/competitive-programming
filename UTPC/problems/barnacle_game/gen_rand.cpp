#include "testlib.h"

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()

vector<pii> pruefer_decode(const vi &code) {
	int n = sz(code) + 2;
	vi degree(n, 1);
	for (int i : code)
		degree[i]++;

	set<int> leaves;
	rep(i, 0, n)
		if (degree[i] == 1)
			leaves.insert(i);

	vector<pii> edges;
	for (int v : code) {
		int leaf = *leaves.begin();
		leaves.erase(leaves.begin());

		edges.emplace_back(leaf, v);
		if (--degree[v] == 1)
			leaves.insert(v);
	}
	edges.emplace_back(*leaves.begin(), n-1);
	return edges;
}

int main(int argc, char* argv[]) {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	registerGen(argc, argv, 1);
	int n = opt<int>("n", 5000);

	cout << n << "\n";

    vector<int> parents = rnd.perm(n-1);
    parents.pop_back();
    vector<pii> edges = pruefer_decode(parents);
    shuffle(all(edges));
    for(auto [u,v] : edges) {
        if(rnd.next(2) == 0)
            swap(u, v);
        cout << u+1 << " " << v+1 << "\n";
    }
}