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
	int N = atoi(argv[1]);
    int SKIP_PROB = atoi(argv[2]);
    int MAX_WIDTH = atoi(argv[3]);
    vector<pair<int, int>> donuts(N);
    int rad = 1;
    for(int i = 0; i < N; i++) {
        int jump = rnd.next(SKIP_PROB);
        if(jump == 0)
            rad++;
        int width = rnd.next(1, MAX_WIDTH);
        donuts[i] = {rad, rad+width};
        rad++;
    }
    shuffle(donuts.begin(), donuts.end());
	cout << N << "\n";
    for(auto donut : donuts) {
        cout << donut.first << " " << donut.second << "\n";
    }
}