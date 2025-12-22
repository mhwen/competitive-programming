#include "testlib.h"
 
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
constexpr int MAX_D = 2e5;
constexpr int MAX_T = 2e5;
 
int main(int argc, char *argv[]) {
    registerValidation(argc, argv);
    int d = inf.readInt(1, MAX_D, "d");
    inf.readSpace();
    int t = inf.readInt(1, MAX_T, "t");
    inf.readEoln();
    inf.readEof();
}