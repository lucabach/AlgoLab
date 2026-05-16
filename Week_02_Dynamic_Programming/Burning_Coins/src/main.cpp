///1
#include <vector>
#include <iostream>

using namespace std;

#define int long

void solve(){
  int n; cin >> n; 
  vector<vector<int>> DP(n, vector<int>(n, 0));
  vector<int> coins(n);
  
  
  
  for(int i=0; i<n; i++){
    int x; cin >> x;
    coins[i] = x;
  }
  
  if(n==1){
    cout << coins[0] << "\n";
    return;
  }
  
  if(n%2 == 1){
    for(int i=0; i<n; i++){
      DP[i][i] = coins[i];
    }
  }
  
  int intervalLength = 1;
  bool turnOpponent = n%2 == 1;
  while(intervalLength < n){
  for(int i=n-2; i>=0; i--){
    if(i+intervalLength < n){
      if(turnOpponent){
        DP[i][i+intervalLength] = min(DP[i][i+intervalLength-1], DP[i+1][i+intervalLength]);
      }
      else{
        DP[i][i+intervalLength] = max(DP[i][i+intervalLength-1] + coins[i+intervalLength], DP[i+1][i+intervalLength] + coins[i]);
      }
      if (i==0 && intervalLength == n-1){
        cout << DP[i][intervalLength] << "\n";
      }
    }
  }
  turnOpponent = !turnOpponent;
  intervalLength++;
}

/*cout << "TABLE: \n";
for(int i=0; i<n; i++){
  for(int j=0; j<n; j++){
    cout << DP[i][j] << " ";
  }
  cout << "\n";
} */

}
  
  

signed main(){
  std::ios_base::sync_with_stdio(false);
  int t;
  cin >> t;
  for(int i=0; i<t; i++){
    solve();
  }
  return 0;
}