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
    int T = min(1e5, 2e5/N);
	cout << T << "\n";
	while(T-->0) {
        vector<int> xs = rnd.distinct(N, -MAX, MAX);
        vector<int> ys = rnd.distinct(N, -MAX, MAX);
        cout << N << "\n";
        for(int i = 0; i < N; i++) {
            cout << xs[i] << " " << ys[i] << "\n";
        }
    }
}