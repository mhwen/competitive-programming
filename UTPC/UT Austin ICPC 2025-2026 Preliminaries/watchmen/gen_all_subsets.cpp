#include "testlib.h"

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long ll;

int main(int argc, char* argv[]) {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	registerGen(argc, argv, 1);
	int N = opt<int>("n", 2e5);
    int MAX = opt<int>("max", 1e9);
    vector<vector<pair<int, int>>> tests;
    vector<int> xs = rnd.distinct(N, -MAX, MAX);
    vector<int> ys = rnd.distinct(N, -MAX, MAX);
    for(int x = 0; x < (1<<N); x++) {
        for(int y = 0; y < (1<<N); y++) {
            if(x == 0 || y == 0)
                continue;
            tests.emplace_back();
            for(int bx = 0; bx < N; bx++) {
                for(int by = 0; by < N; by++) {
                    if((1<<bx)&x) {
                        if((1<<by)&y) {
                            tests.back().push_back({xs[bx], ys[by]});
                        }
                    }
                }
            }
        }
    }
	cout << tests.size() << "\n";
	for(int t = 0; t < tests.size(); t++) {
        cout << tests[t].size() << "\n";
        for(auto [x, y] : tests[t])
            cout << x << " " << y << "\n";
    }
}