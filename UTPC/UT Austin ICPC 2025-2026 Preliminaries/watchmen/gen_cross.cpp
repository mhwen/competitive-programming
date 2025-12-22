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
    int X = rnd.next(-MAX, MAX);
    int Y = rnd.next(-MAX, MAX);
    int T = min(1e5, 2e5/N);
	cout << T << "\n";
	while(T-->0) {
        cout << N << "\n";
        for(int i = 0; i < N; i++) {
            if(rnd.next(2) == 0)
                cout << X << " " << rnd.next(-MAX, MAX) << "\n";
            else
                cout << rnd.next(-MAX, MAX) << " " << Y << "\n";
        }
    }
}