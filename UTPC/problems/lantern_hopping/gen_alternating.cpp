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
	int n = opt<int>("n", 2e5);
    int q = opt<int>("q", 2e5);
    int maxHeight = opt<int>("maxHeight", 1e9);
    double questionProb = opt<double>("p", 0.5);

    auto getHeight = [&]() {
        if(rnd.next(2)%2==0)
            return rnd.next(0, maxHeight/100);
        else
            return rnd.next(maxHeight/2, maxHeight);
    };

	cout << n << " " << q << "\n";
    for(int i = 0; i < n; i++) {
        cout << getHeight();
        if(i < n-1)
            cout << " ";
        else
            cout << "\n";
    }
    for(int i = 0; i < q; i++) {
        int p = rnd.next(1, n);
        if(rnd.next() <= questionProb)
            cout << 1 << " " << p << "\n";
        else
            cout << 2 << " " << p << " " << getHeight() << "\n";
    }
}