#include "testlib.h"

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
#define all(x) begin(x), end(x)

int main(int argc, char* argv[]) {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	registerGen(argc, argv, 1);
	int n = opt<int>("n", 2e5);
    int q = opt<int>("q", 2e5);
    int abBound = opt<int>("ab-bound", 1e9);
    int cBound = opt<int>("c-bound", 1e9);
	cout << n << " " << q << "\n";
    int dx = rnd.next(-1e9/n, 1e9/n);
    int dy = rnd.next(-1e9/n, 1e9/n);
    int x = rnd.next(-100, 100);
    int y = rnd.next(-100, 100);
    vector<pair<int, int>> p;
    for(int i = 0; i < n; i++) {
        p.emplace_back(x+dx*(i-n/2), y+dy*(i-n/2));
    }
    shuffle(all(p));
    for(auto [x,y]: p)
        cout << x << " " << y << "\n";
    for(int i = 0; i < q; i++) {
        int A = rnd.next(-abBound, abBound);
        int B = rnd.next(-abBound, abBound);
        while(A == 0 && B == 0) {
            A = rnd.next(-abBound, abBound);
            B = rnd.next(-abBound, abBound);
        }
        int C = rnd.next(-cBound, cBound);
        cout << A << " " << B << " " << C << "\n";
    }
}