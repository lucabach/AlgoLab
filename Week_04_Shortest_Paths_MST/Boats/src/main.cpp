#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
#include <limits>

#define int long long

using namespace std;
typedef pair<int, int> PII;

void solve(){
  int n; cin >> n;
  vector<PII> boat(n);
  for(int i=0; i<n; i++){
    int l, p; cin >> l >> p;
    boat[i] = make_pair(p, l);
  }
  sort(boat.begin(), boat.end());
  
  int numBoats = 0;
  int r = numeric_limits<int>::min();
  int r_prev = numeric_limits<int>::min();
  for(int i=0; i<n; i++){
    if(boat[i].first < r){
      int newR = max(r_prev + boat[i].second, boat[i].first);
      r = min(r, newR);
    }
    else{
      r_prev = r;
      r = max(boat[i].first, r+boat[i].second);
      numBoats++;
    }
  }
  cout << numBoats << "\n";
}



signed main(){
  int t;
  cin>>t;
  while(t--){
    solve();
  }
  return 0;
}