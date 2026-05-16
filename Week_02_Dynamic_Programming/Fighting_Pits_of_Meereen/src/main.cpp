#include <iostream>
#include <vector>
#include <cmath>
#include <limits>


using namespace std;
#define int long

typedef vector<int> S;
typedef vector<S> P;
typedef vector<P> Q;
typedef vector <Q> M;

M memo;
int n, k, m;

int score(int gate, int q, int fighter){
  if(q==1) return 1000;
  if(q==2) return 1000 + 1000*(fighter != gate % k);
  return 1000 + 1000*((gate/k != gate%k) && (gate/k != fighter)) + 1000*(gate%k != fighter);
}


int updateGate(int gate, int fighter, int q){
  if(q<2) return fighter;
  return fighter + (gate%k)*k;
}


int dp(const vector<int> &fighters, int p, int q, int north, int south){
  
  if(abs(p-q) > 11) return -1;
  if(p+q == n) return 0; 
  
  if(memo[p+q][p-q+11][north][south] != -2)  return memo[p+q][p-q+11][north][south];
  
  int fighter = fighters[p+q];
  
  int northScore = score(north, min(p+1, m), fighter) -pow(2, abs(p-q+1));
  int southScore = score(south, min(q+1, m), fighter) -pow(2, abs(p-q-1));
  
  int northScoreNext = dp(fighters, p+1, q, updateGate(north, fighter, min(p+1, m)), south);
  int southScoreNext = dp(fighters, p, q+1, north, updateGate(south, fighter, min(q+1, m)));
  
  int northScoreTotal = northScoreNext >= 0? northScore + northScoreNext : -1;
  int southScoreTotal = southScoreNext >= 0? southScore + southScoreNext : -1;
  
  memo[p+q][p-q+11][north][south] = max(northScoreTotal, southScoreTotal);
  return memo[p+q][p-q+11][north][south];
}



void solve(){
  cin >> n >> k >> m;
  
  vector<int> fighters(n);
  for(int i=0; i<n; i++){
    int t; cin >> t;
    fighters[i] = t;
  }
  
 
  int MAX_STATE = k*k + 1;
  memo = M(n, Q(24, P(MAX_STATE, S(MAX_STATE, -2))));
  int res = dp(fighters, 0, 0, 0, 0);
  cout << res << "\n";
}



signed main(){
  int t; cin >> t;
  while(t--){
    solve();
  }
  return 0;
}