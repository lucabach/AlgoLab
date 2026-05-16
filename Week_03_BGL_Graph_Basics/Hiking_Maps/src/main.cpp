#include <iostream>
#include <vector>
#include <array>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/intersections.h>
#include <limits>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef K::Point_2 P;
typedef K::Line_2 L;
typedef K::Triangle_2 T;
typedef K::Segment_2 S;

using namespace std;

L create_line(P a1, P a2, P ref){
  if(CGAL::right_turn(a1, a2, ref)){
    swap(a1, a2);
  }
  return L(a1, a2);
}

void solve(){
  int m, n; cin >> m >> n;
  array<array<bool, 2000>, 2000> map_has_leg{};
  vector<pair<P, P>> leg(m-1);
  int a, b; cin >> a >> b;
  for(int i=0; i<m-1; i++){
    int c, d; cin >> c >> d;
    leg[i] = {P(a, b), P(c, d)};
    a=c; b=d;
  }
  
  for(int i=0; i<n; i++){
    int a1, a2, a3, a4, b1, b2, b3, b4, c1, c2, c3, c4; 
    cin >> a1 >> a2 >>  a3 >> a4 >> b1 >> b2 >> b3 >> b4 >> c1 >> c2 >> c3 >> c4;
    L l1 = create_line(P(a1, a2), P(a3, a4), P(b1, b2)); 
    L l2 = create_line(P(b1, b2), P(b3, b4), P(c1, c2));
    L l3 = create_line(P(c1,c2), P(c3, c4), P(a1, a2));
    
    for(int j=0; j<m-1; j++){
    if(!l1.has_on_negative_side(leg[j].first) && !l1.has_on_negative_side(leg[j].second) &&
      !l2.has_on_negative_side(leg[j].first) && !l2.has_on_negative_side(leg[j].second) &&
      !l3.has_on_negative_side(leg[j].first) && !l3.has_on_negative_side(leg[j].second)){
        
    
    //auto o1 = CGAL::intersection(l1,l2);
    //auto o2 = CGAL::intersection(l2,l3);
    //auto o3 = CGAL::intersection(l3,l1);
    //if (!o1 || !o2 || !o3) continue;

    //const P* i1 = boost::get<P>(&*o1);
    //const P* i2 = boost::get<P>(&*o2);
    //const P* i3 = boost::get<P>(&*o3);
    //if (!i1 || !i2 || !i3) continue;
    //T t1(*i1, *i2, *i3);
    
    //if (t1.is_degenerate()) continue;
    //for(int j=0; j<m-1; j++){
      //if(!t1.has_on_unbounded_side(leg[j].first) && !t1.has_on_unbounded_side(leg[j].second)){
        map_has_leg[i][j] = true;
      }
    }
  }
  
  array<int, 2000> legs_in_window{};
  int legs_needed = m-1;
  int wStart = 0; int wEnd=0;
  int minSize = numeric_limits<int>::max();
  
  while(true){
    if(legs_needed == 0){
        minSize = min(minSize, wEnd - wStart);
        for(int i=0; i<m-1; i++){
          if(map_has_leg[wStart][i] && --legs_in_window[i] == 0){
            legs_needed++;
          }
        }
        wStart++;
    }
    
    else{
    if(wEnd >= n){break;}
      for(int i=0; i<m-1; i++){
        if(map_has_leg[wEnd][i] && ++legs_in_window[i] == 1){
        legs_needed--;
      }
    }
    wEnd++;
    }
    if (legs_needed == 0) {
      minSize = std::min(minSize, wEnd-wStart);
    }
  }
  
  cout << minSize << "\n";
}

int main(){
  ios_base::sync_with_stdio(false);
  int t; cin >> t;
  while(t--){ solve();}
  return 0;
}