#include "testlib.h"
 
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
constexpr int MAX_N = 2e5;
constexpr int MIN_A = -1e9;
constexpr int MAX_A = 1e9;
 
int main(int argc, char *argv[]) {
    registerValidation(argc, argv);
    int n = inf.readInt(1, MAX_N, "n");
    inf.readEoln();
    for(int i = 0; i < n; i++) {
        inf.readInt(MIN_A, MAX_A, "a_"+to_string(i+1));
        if(i < n-1)
            inf.readSpace();
        else
            inf.readEoln();
    }
    int ones = 0;
    for(int i = 0; i < n; i++) {
        ones += inf.readInt(0, 1, "b_"+to_string(i+1));
        if(i < n-1)
            inf.readSpace();
        else
            inf.readEoln();
    }
    inf.readEof();
    ensure(ones > 0);
}