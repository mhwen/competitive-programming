#include "testlib.h"

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long ll;
constexpr int MAX_RADIUS = 1e9;

int main(int argc, char* argv[]) {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	registerGen(argc, argv, 1);
	int N = atoi(argv[1]);
    int SHRINK = 0;
    int LEFT = rnd.next(1, MAX_RADIUS/3);
    int RIGHT = rnd.next(2*MAX_RADIUS/3, MAX_RADIUS);
    int DIST = (RIGHT-LEFT)/2;
    vector<pair<int, int>> donuts(N);
    for(int i = 0; i < N; i++) {
        int innerRadius = LEFT+SHRINK;
        int outerRadius = RIGHT-SHRINK;
        donuts[i] = {innerRadius, outerRadius};
        SHRINK = rnd.next(SHRINK+1, SHRINK+1+DIST/N);
    }
    shuffle(donuts.begin(), donuts.end());
    cout << N << "\n";
    for(auto donut : donuts) {
        cout << donut.first << " " << donut.second << "\n";
    }
}