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
    int parent = rnd.next(n);
    vector<int> children;
    for(int i = 0; i < n; i++)
        if(i != parent)
            children.push_back(i);
    shuffle(all(children));
    for(auto c : children) {
        int u = parent;
        int v = c;
        if(rnd.next(2) == 0)
            swap(u, v);
        cout << u+1 << " " << v+1 << "\n";
    }
}