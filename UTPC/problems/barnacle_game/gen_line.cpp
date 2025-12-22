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

int main(int argc, char* argv[]) {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	registerGen(argc, argv, 1);
	int n = opt<int>("n", 5000);

	cout << n << "\n";
    vector<int> perm = rnd.perm(n);
    vector<pair<int, int>> edges;
    for(int i = 0; i < n-1; i++) {
        int u = perm[i];
        int v = perm[i+1];
        if(rnd.next(2) == 0)
            swap(u, v);
        edges.push_back({u, v});
    }
    shuffle(all(edges));
    for(auto [u,v] : edges)
        cout << u+1 << " " << v+1 << "\n";
}