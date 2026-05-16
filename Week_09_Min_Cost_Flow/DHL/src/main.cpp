#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

#define int long

using namespace std;

void solve() {
    int n;
    std::cin >> n; 
    
    
    vector<int> a(n, 0);
    vector<int> b(n, 0);
    
    for(int i=0; i<n; i++){
      int a1; cin >> a1;
      a[i] = a1;
    }
    
    for(int i=0; i<n; i++){
      int b1; cin >> b1;
      b[i] = b1;
    }
    
    
    vector<vector<int>> dp(n+1, vector<int>(n+1, numeric_limits<int>::max()));
    dp[0][0] = 0;
    for(int i=1; i<=n; i++){
      for(int j=1; j<=n; j++){
        dp[i][j] = (a[i-1]-1)*(b[j-1]-1) + min(dp[i-1][j-1], min(dp[i-1][j], dp[i][j-1]));
        }
    }

    
    cout << dp[n][n] << "\n";
}

signed main() {
    int t;
    cin >> t;
    while (t--) solve();
    return 0;
}