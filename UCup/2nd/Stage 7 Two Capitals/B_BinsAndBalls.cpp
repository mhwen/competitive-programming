#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
  ll n, k;
  cin >> n >> k;
  vector<ll> arr(n);
  for (int i = 0; i < n; i++) {
    cin >> arr[i];
  }
  __int128 l = 0;
  __int128 r = 3e14;
  while (l <= r) {
    __int128 mid = (l+r)/2;
    __int128 needed = mid*k;
    for (int i = 0; i < n; i++) {
    	needed -= min(mid, (__int128)arr[i]);
    }
    if (needed <= 0) {
      l = mid+1;
    } else {
      r = mid-1;
    }
  }
  cout << (ll)r << endl;
}