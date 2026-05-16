
#include <iostream>
#include <vector>
#include <queue>
#include <tuple>

using namespace std;

#define int long


void solve(){
  int n, m, k; cin >> n >> m >> k;
  vector<int> cumSum(n+1, 0);
  

  for(int i=1; i<=n; i++){
    int x; cin >> x;
    cumSum[i] = cumSum[i-1] + x;
  }
  
  vector<int> startIdx(n, -1);
  int i = 0; int j = 0;
  
  while(j<n){
    int windowSum = cumSum[j+1] - cumSum[i];
    
    if(windowSum == k){
      startIdx[j] = i;
    }
    
    if(windowSum < k){
      j++;
    }
    
    else{
      i++;
    }
    
    if(i>j){
      swap(i, j);
    }
  }

  vector<vector<int>> DP(m, vector<int>(n, 0));
  for(int j=0; j<n; j++){
    if(j>0){
      DP[0][j] = DP[0][j-1];
    }
    if(startIdx[j]>=0){
      int curLength = j-startIdx[j]+1;
      DP[0][j] = max(DP[0][j], curLength);
    }
  }
  
for (int i = 1; i < m; i++) {
    for (int j = 0; j < n; j++) {

        // Option 1: don't end an interval at j
        if (j > 0)
            DP[i][j] = DP[i][j-1];
        else
            DP[i][j] = 0; 

        // Option 2: end an interval at j
        if (startIdx[j] >= 0) {
            int len = j - startIdx[j] + 1;
            int prev = j - len;

            // Validity check: must have i intervals before this
            if (prev >= 0 && DP[i-1][prev] > 0) {
                DP[i][j] = max(DP[i][j],
                               DP[i-1][prev] + len);
            }
        }
    }
}

  
  /*cout << "startIdx: \n";
  for(int i=0; i<n; i++){
    cout << startIdx[i] << " ";
  }
  
  cout << "\nDP:\n";
  for(int i=0; i<m; i++){
    for(int j=0; j<n; j++){
      cout << DP[i][j] << " ";
    }
    cout << "\n";
  } 
*/

if (DP[m-1][n-1] == 0)
    cout << "fail\n";
else
    cout << DP[m-1][n-1] << "\n";
}


signed main(){
  ios_base::sync_with_stdio(false);
  int t; cin >> t;
  while(t--){
    solve();
  }
  return 0;
}