#include "testlib.h"

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main(int argc, char* argv[]) {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	registerGen(argc, argv, 1);
	int n = opt<int>("n", 2e5);
    int q = opt<int>("q", 2e5);
    int xyBound = opt<int>("xy-bound", 1e9);
    int abBound = opt<int>("ab-bound", 1e9);
    int cBound = opt<int>("c-bound", 1e9);
    bool sameSlopeQuery = opt<bool>("same-slope-query", false);
	cout << n << " " << q << "\n";
    set<pair<int, int>> p;
    for(int i = 0; i < n; i++) {
        pair<int, int> point;
        do {
            point = {rnd.next(-xyBound, xyBound), rnd.next(-xyBound, xyBound)};
        } while(p.count(point));
        cout << point.first << " " << point.second << "\n";
        p.insert(point);
    }

    int A = rnd.next(-abBound, abBound);
    int B = rnd.next(-abBound, abBound);
    while(A == 0 && B == 0) {
        A = rnd.next(-abBound, abBound);
        B = rnd.next(-abBound, abBound);
    }
    for(int i = 0; i < q; i++) {
        if(!sameSlopeQuery) {
            A = rnd.next(-abBound, abBound);
            B = rnd.next(-abBound, abBound);
            while(A == 0 && B == 0) {
                A = rnd.next(-abBound, abBound);
                B = rnd.next(-abBound, abBound);
            }
        }
        int C = rnd.next(-cBound, cBound);
        cout << A << " " << B << " " << C << "\n";
    }
}