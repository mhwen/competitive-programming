#include "testlib.h"
 
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
constexpr int MAX_T = 1e4;
constexpr int MAX_N = 2e5;
constexpr int MAX_SIZE = 1e9;
 
int main(int argc, char *argv[]) {
    registerValidation(argc, argv);
    int t = inf.readInt(1, MAX_T, "t");
    inf.readEoln();
    int sum = 0;
    for(int test = 1; test <= t; test++) {
        setTestCase(test);
        int n = inf.readInt(1, MAX_N, "n");
        inf.readEoln();
        sum += n;
        ensure(sum <= MAX_N);
        for(int i = 0; i < n; i++) {
            inf.readInt(1, MAX_SIZE, "a_"+to_string(i+1));
            if(i < n-1)
                inf.readSpace();
            else
                inf.readEoln();
        }   
    }
    inf.readEof();
}