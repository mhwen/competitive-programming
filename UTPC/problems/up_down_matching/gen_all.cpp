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
	int N = atoi(argv[1]);
    vector<string> tests;
    for(int mask = 0; mask < (1<<N); mask++) {
        string s = "";
        for(int bit = 0; bit < N; bit++) {
            if(mask&(1<<bit))
                s += "U";
            else
                s += "D";
        }
        tests.push_back(s);
    }
    cout << tests.size() << "\n";
    for(string s : tests) {
        cout << s.length() << "\n";
        cout << s << "\n";
    }
}