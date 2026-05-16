
#include <iostream>
#include <vector>

using namespace std;
#define int long

void solve(){
  //cout << "___________________________________\n";
  int n, m; cin >> n >> m;
  
  vector<vector<int>> M(n, vector<int>(m));
  vector<vector<int>> verticalsum(n, vector<int>(m));
  vector<vector<int>> horizontalsum(n, vector<int>(m));

  
  for(int i=0; i<n; i++){
    for(int j=0; j<m; j++){
    int x; cin >> x;
    M[i][j] = x;
   }
  }
  

  //cout << "M:";
  /*
  for(int i=0; i<n; i++){
    cout << "\n";
    for(int j=0; j<m; j++){
      cout << M[i][j] << " ";
    } 
  }
  
  cout << "\n";*/
  
  for(int i=0; i<n; i++){
    horizontalsum[i][0] = M[i][0];
    int accsum = M[i][0];
    for(int j=1; j<m; j++){
      accsum += M[i][j];
      horizontalsum[i][j] = horizontalsum[i][j-1] + accsum;
    }
  }
  
  for(int j=0; j<m; j++){
    verticalsum[0][j] = M[0][j];
    int accsum = M[0][j];
    for(int i=1; i<n; i++){
      accsum += M[i][j];
      verticalsum[i][j] = verticalsum[i-1][j] + accsum;
    }
  }
  
  
  /*cout << "hsum:";
  for(int i=0; i<n; i++){
    cout << "\n";
    for(int j=0; j<m; j++){
      cout << horizontalsum[i][j] << " ";
    } 
  }
  
  cout << "\nvsum:";
  for(int i=0; i<n; i++){
    cout << "\n";
    for(int j=0; j<m; j++){
      cout << verticalsum[i][j] << " ";
    }
  }*/
  
  
  
  M.clear();
  vector<vector<int>> DP(n, vector<int>(m));
  
  for(int i=0; i<n; i++){
    for(int j=0; j<m; j++){
      if(i==0 || j==0){
        DP[i][j] == 0;
      }
      else{
        DP[i][j] = min(DP[i][j-1] + verticalsum[i-1][j], DP[i-1][j] + horizontalsum[i][j-1]);
      }    
    }
  }
  
  cout << DP[n-1][m-1] << "\n";
}
  
signed main(){
  ios_base::sync_with_stdio(false);
  int t; cin >> t;
  while(t--){
    solve();
  }
  return 0;
}
