#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); i++)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

constexpr int INF = 1e9;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t;
    cin >> t;
    while(t-->0) {

        int n;
        cin >> n;

        vector<vector<int>> heaps;
        multiset<pair<int, int>> available;
        int heapCount = 0;
        for(int i = 0; i < n; i++) {
            int a;
            cin >> a;
            auto take = available.upper_bound({a, INF});
            if(take == available.begin()) {
                //add new heap
                heaps.push_back({i});
                available.insert({a, heapCount});
                available.insert({a, heapCount});
                heapCount++;
            }
            else {
                take--;
                int heap = take->second;
                heaps[heap].push_back(i);
                available.erase(take);
                available.insert({a, heap});
                available.insert({a, heap});
            }
        }
        cout << heapCount << "\n";
        for(int i = 0; i < heapCount; i++) {
            cout << sz(heaps[i]);
            for(int num : heaps[i])
                cout << " " << num+1;
            cout << "\n";
        }
    }
}