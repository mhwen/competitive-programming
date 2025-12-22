#include "testlib.h"
 
#include <iostream>
#include <vector>
#include <algorithm>
 
using namespace std;
constexpr int MAX_T = 1e5;
constexpr int MAX_N = 2e5;
constexpr int MAX_XY = 1e9;
 
int main(int argc, char *argv[]) {
    registerValidation(argc, argv);
    int t = inf.readInt(1, MAX_T, "t");
    inf.readEoln();
    int sumN = 0;
    for(int i = 0; i < t; i++) {
        int n = inf.readInt(1, MAX_N, "n");
        inf.readEoln();
        sumN += n;
        ensure(sumN <= MAX_N);
        for(int j = 0; j < n; j++) {
            inf.readInt(-MAX_XY, MAX_XY, "x");
            inf.readSpace();
            inf.readInt(-MAX_XY, MAX_XY, "y");
            inf.readEoln();
        }
    }
    inf.readEof();
}
