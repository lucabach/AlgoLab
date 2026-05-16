#include <iostream>
#include <algorithm>
#include <vector>
#include <utility>
using namespace std;

struct SumLessThan {
bool operator() (const pair<int, bool> &p1, const pair<int, bool> &p2) const {
return p1.first < p2.first || (p1.first == p2.first && (int)p1.second < (int)p2.second);
}
};

void solve(){
  int n; cin >> n;
  vector<pair<int, bool>> intervals(2*n);
  for(int i=0; i<n; i++){
    int l, r; cin >> l >> r;
    intervals[2*i] = make_pair(l, false);
    intervals[2*i + 1] = make_pair(r, true);
  }
  
  //cout << "*********************************\n";
  sort(intervals.begin(), intervals.end(), SumLessThan());
  int curIntervals = 0;
  int maxIntervals = -1;
  for(int i=0; i<2*n; i++){
    auto curInterval = intervals[i];
    //cout << "inspecting close? = " << curInterval.second << " on index " << curInterval.first << "\n";
    if(!curInterval.second){
      curIntervals++;
    }
    else{
      curIntervals--;
    }
    maxIntervals = max(curIntervals, maxIntervals);
  }
  
  cout << maxIntervals << "\n";
}

int main(){
  std::ios_base::sync_with_stdio(false);
  int t;
  cin >> t;
  for(int i=0; i<t; i++){
    solve();
  }
  
  return 0;
}