#include "testlib.h"
 
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
constexpr int MAX_T = 1e4;
constexpr int MAX_N = 2e5;
 
int main(int argc, char *argv[]) {
    registerValidation(argc, argv);
    int t = inf.readInt(1, MAX_T, "t");
    inf.readEoln();
    int nSum = 0;
    for(int test = 1; test <= t; test++) {
        setTestCase(test);
        int n = inf.readInt(1, MAX_N, "n");
        inf.readEoln();
        nSum += n;
        inf.readString("[UD]{"+to_string(n)+"}", "s");
    }
    inf.readEof();
}