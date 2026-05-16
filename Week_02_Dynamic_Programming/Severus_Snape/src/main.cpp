#include <bits/stdc++.h>
#include <limits>
#include <algorithm>

#define int long

using namespace std;

  


void solve() {
  int n,m,a,b,P,H,W;
  cin >> n >> m >> a >> b >> P >> H >> W;
  
  //int minInt = numeric_limts<int>::min();
  vector<vector<vector<int>>> DPA(n+1, vector<vector<int>>(n+1, vector<int>(H+1, -1)));
  
  vector<pair<int, int>> A(n+1);
  for(int i=1; i<=n; i++){
    int p, h; cin >> p >> h;
    A[i] = {p, h};
  }
  
  //BASE CASE 1: max power we can achive if out of the first i we select 0 potions is 0
  for (int i = 0; i <= n; i++) {
    DPA[i][0][0] = 0;
  }
  
  //BASE CASE 2: max power we can achieve if out of the first i potions we select exactly 1
  for(int h=0; h<=H; h++){
    for(int i=1; i<=n; i++){
      pair<int, int> curPotion = A[i];
      int curPower = curPotion.first;
      int curHappiness = curPotion.second;
      DPA[i][1][h] = DPA[i-1][1][h];
      
      if(curHappiness >= h){
      DPA[i][1][h] = max(DPA[i][1][h], curPower);
      }
    }
  }
  
  for(int j=2; j<=n; j++){
    for(int h=0; h<=H; h++){
      for(int i=j; i<=n; i++){
        
        DPA[i][j][h] = DPA[i-1][j][h];
        
        pair<int, int> curPotion = A[i];
        int curPower = curPotion.first;
        int curHappiness = curPotion.second;
        int prev_h = max(0L, h-curHappiness);
        
        if(DPA[i-1][j-1][prev_h] >= 0){
        DPA[i][j][h] = max(DPA[i][j][h], DPA[i-1][j-1][prev_h] + curPower);
        }
      }
    }
  }
  
  vector<int> B(m+1);
  for(int i=1; i<=m; i++){
    int w; cin >> w;
    B[i] = w;
  }


  sort(B.begin()+1, B.end(), greater<int>());
  int min_potions = numeric_limits<int>::max();
  int curBPotions = 0;
  int totalBwit = 0;
  
  while(curBPotions <= m){
    int curWit = B[curBPotions];
    totalBwit += curWit;
    if(totalBwit >= W){
      int curApotions = 1;
      while(curApotions <= n){
        int curMaxPower = DPA[n][curApotions][H];
        if(curMaxPower - b*curBPotions >= P && totalBwit - a*curApotions >= W){
          min_potions = min(min_potions, curApotions + curBPotions);
          break;
        }
        if(totalBwit - a*curApotions < W){
          break;
        }
        curApotions++;
      }
    }
    curBPotions++;
  }
  
  if(min_potions == numeric_limits<int>::max()){
    cout << "-1\n";
  }
  else{
  cout << min_potions << "\n";
  }
}


signed main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  
  int t;
  cin >> t;
  
  while(t--)
    solve();
  
  return 0;
}