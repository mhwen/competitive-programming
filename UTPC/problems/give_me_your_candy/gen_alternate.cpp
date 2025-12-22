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
    double favProb = opt<double>("fav-prob", 0.1);
    double aProb = opt<double>("a-prob", 0.5);
    int A = opt<int>("a");
    int B = opt<int>("b");

	cout << n << "\n";
    for(int i = 0; i < n; i++) {
        if(i > 0)
            cout << " ";
        if(check(aProb))
            cout << A;
        else
            cout << B;
    }
    cout << "\n";
    for(int i = 0; i < n; i++) {
        if(i > 0)
            cout << " ";
        if(check(favProb))
            cout << 1;
        else
            cout << 0;
    }
    cout << "\n";
}