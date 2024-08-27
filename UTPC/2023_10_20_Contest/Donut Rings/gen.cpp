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
    int MAX_RADIUS = atoi(argv[2]);
    int MAX_WIDTH = atoi(argv[3]);
	cout << N << "\n";
    for(int i = 0; i < N; i++) {
        int innerRadius = rnd.next(1, MAX_RADIUS-1);
        int outerRadius = innerRadius+rnd.next(1, min(MAX_WIDTH, MAX_RADIUS-innerRadius));
        cout << innerRadius << " " << outerRadius << "\n";
    }
}