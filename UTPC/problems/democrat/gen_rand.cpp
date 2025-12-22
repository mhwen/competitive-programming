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
	int n = opt<int>("n", 2e3);
    int r = opt<int>("r", 1e6);
    int bound = opt<int>("bound", 1e6);
	cout << n << " " << r << "\n";

    auto randPoint = [&]() {
        return pair{rnd.next(-bound, bound), rnd.next(-bound, bound)};
    };
    set<pair<int, int>> seen;
    for(int i = 0; i < n; i++) {
        pair<int, int> p = randPoint();
        while(seen.count(p))
            p = randPoint();
        seen.insert(p);
        cout << p.first << " " << p.second << "\n";
    }
}