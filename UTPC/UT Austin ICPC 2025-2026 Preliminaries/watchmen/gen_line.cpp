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
    int DX = opt<int>("dx", 1);
    int DY = opt<int>("dy", 1);
    int T = min(1e5, 2e5/N);
	cout << T << "\n";
	while(T-->0) {
        cout << N << "\n";
        int dx = rnd.next(-DX, DX);
        int dy = rnd.next(-DY, DY);
        int lim;
        if(dx == 0 && dy == 0)
            lim = 1;
        else
            lim = 1e9/max(abs(dx), abs(dy));
        for(int i = 0; i < N; i++) {
            int c = rnd.next(-lim, lim);
            cout << c*dx << " " << c*dy << "\n";
        }
    }
}