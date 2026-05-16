
#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <unordered_map>
#include <CGAL/Gmpq.h>

using namespace std;

CGAL::Gmpq get_slope(const tuple<long, long, long, int> &t){
  return CGAL::Gmpq(get<2>(t) - get<0>(t), get<1>(t));
}


struct SumLessThan {
bool operator() (const tuple<long, long, long, int> & p1, const tuple<long, long, long, int>& p2) const {
return get<0>(p1) > get<0>(p2);
}
};

void solve(){
  int n; cin >> n;
  vector<tuple<long, long, long, int>> biker;
  
  for(int i=0; i<n; i++){
    long y0, x0, y1; cin >> y0 >> x0 >> y1;
    biker.emplace_back(y0, x0, y1, i);
  }
  
  
  sort(biker.begin(), biker.end(), SumLessThan());
  vector<int> ridesforever;
  CGAL::Gmpq best_slope = get_slope(biker[n-1]);
  vector<bool>candidate(n, true);
  //cout << "--------------------------\n";
  
  for(int i=n-2; i>=0; i--){
  //cout << "inspecting biker " << startPos[biker[i].first] << ": startPos " << biker[i].first << ", m = " << biker[i].second << "\n";

  CGAL::Gmpq cur = get_slope(biker[i]);
  if (CGAL::abs(cur) < CGAL::abs(best_slope) || (CGAL::abs(cur) == CGAL::abs(best_slope) && cur > best_slope)) {
    best_slope = cur;
  }
  else if (cur < best_slope){
    candidate[get<3>(biker[i])] = false;}
  }
  
  best_slope = get_slope(biker[0]);
  
  for(int i=1; i<n; i++){
  //cout << "inspecting biker " << startPos[biker[i].first] << ": startPos " << biker[i].first << ", m = " << biker[i].second << "\n";

  CGAL::Gmpq cur = get_slope(biker[i]);
  if (CGAL::abs(cur) <= CGAL::abs(best_slope)) {
    best_slope = cur;
  }
  else if(cur > best_slope){
    candidate[get<3>(biker[i])] = false;
  }
  }
  
  vector<int> res;
  for(int i=0; i<n; i++){
    if(candidate[i]){
      cout << i << " ";
    }
  }
  cout << "\n";
}

signed main(){
  int t; cin >> t;
  while(t--){
    solve();
  }
  return 0;
}