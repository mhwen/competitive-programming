#include "testlib.h"

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long ll;

struct Line {
    int A, B, C;
    Line(int a, int b, int c) : A(a), B(b), C(c) {}
};

int main(int argc, char* argv[]) {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	registerGen(argc, argv, 1);
	int n = opt<int>("n", 1e5);
    int r = opt<int>("r", 1e4);
    double minDist = opt<double>("min-dist", 0);
    int abBound = opt<int>("ab-bound", 1e4);
    int cBound = opt<int>("c-bound", 1e4);

	cout << n << " " << r << "\n";

    auto good = [&](Line l) {
        if(l.A == 0 && l.B == 0)
            return false;
        double d = abs(l.C)/sqrt(l.A*l.A+l.B*l.B);
        if(d < minDist || d >= r)
            return false;
        return true;
    };

    auto randLine = [&]() {
        return Line(rnd.next(-abBound, abBound), rnd.next(-abBound, abBound), rnd.next(-cBound, cBound));
    };

    Line l = randLine();
    while(!good(l))
        l = randLine();

    for(int i = 0; i < n; i++) {
        Line l2 = Line(l.A, l.B, rnd.next(-cBound, cBound));
        while(!good(l2))
            l2 = Line(l.A, l.B, rnd.next(-cBound, cBound));
        cout << l2.A << " " << l2.B << " " << l2.C << "\n";
    }
}