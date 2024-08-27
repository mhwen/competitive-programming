#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <map>
#include <set>
#include <stack>
#include <functional>
#include <cassert>

using namespace std;

typedef long long ll;
constexpr ll MOD = 998244353;

//ab
//cd
bool check1(int mask, int n, int m) {
    for(int r = 0; r < n-1; r++) {
        for(int c = 0; c < m-1; c++) {
            int A = (mask&(1<<(r*m+c))) != 0;
            int B = (mask&(1<<(r*m+c+1))) != 0;
            int C = (mask&(1<<((r+1)*m+c))) != 0;
            int D = (mask&(1<<((r+1)*m+c+1))) != 0;
            if((A+B+C+D)%2==1)
                return false;
        }
    }
    return true;
}

bool check2(int mask, int n, int m) {
    for(int r = 0; r < n-1; r++) {
        for(int c = 0; c < m-1; c++) {
            int A = (mask&(1<<(r*m+c))) != 0;
            int B = (mask&(1<<(r*m+c+1))) != 0;
            int C = (mask&(1<<((r+1)*m+c))) != 0;
            int D = (mask&(1<<((r+1)*m+c+1))) != 0;
            if((A+B+C+D)%2==1)
                return true;
        }
    }
    return false;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    ll count1 = 0, count2 = 0;
    for(int i = 0; i < (1<<(n*m)); i++) {
        if(check1(i, n, m))
            count1++;
        if(check2(i, n, m))
        	count2++;
        count1 %= MOD;
        count2 %= MOD;
    }
    ll pow = 1;
    for(int i = 0; i < n*m; i++)
    	pow = pow*2%MOD;
    assert(count2 == (pow-count1+MOD)%MOD);
    cout << count2 << "\n";
}