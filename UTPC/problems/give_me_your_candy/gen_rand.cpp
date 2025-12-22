#include "testlib.h"

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long ll;

bool check(double prob) {
    double p = rnd.next();
    return p <= prob;
}

int main(int argc, char* argv[]) {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	registerGen(argc, argv, 1);
	int n = opt<int>("n");
    double oneProb = opt<double>("fav-prob");
    double negProb = opt<double>("neg-prob", 0.5);
    int LO = opt<int>("lo", -1e9);
    int HI = opt<int>("hi", 1e9);

	cout << n << "\n";
    for(int i = 0; i < n; i++) {
        if(i > 0)
            cout << " ";
        if(check(negProb))
            cout << rnd.next(LO, 0);
        else
            cout << rnd.next(0, HI);
    }
    cout << "\n";
    for(int i = 0; i < n; i++) {
        if(i > 0)
            cout << " ";
        if(check(oneProb))
            cout << 1;
        else
            cout << 0;
    }
    cout << "\n";
}