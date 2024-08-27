#include <vector>
#include <iostream>
#include <set>
#include <queue>
#include <map>
#include <algorithm>

using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    
    int t;
    cin >> t;
    while(t-->0) {
        int n;
        cin >> n;
        if(n > 5)
            cout << 0 << "\n";
        else {
            int res = 1;
            for(int i = 1; i <= n; i++)
                res *= i;
            cout << res%10 << "\n";
        }
    }
}