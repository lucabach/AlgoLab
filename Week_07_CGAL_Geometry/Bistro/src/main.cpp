///1
#include <iostream>
#include <vector>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef K::Point_2 P;
typedef CGAL::Delaunay_triangulation_2<K> Triangulation;
typedef Triangulation::Finite_faces_iterator Face_iterator;


using namespace std;


void solve(const int &n){
  vector<P> oldlocations(n);
  for(int i=0; i<n; i++){
    int a, b; cin >> a >> b;
    oldlocations[i] = P(a, b);
  }
  
  int m; cin >> m;
  vector<P> newlocations(m);
  for(int i=0; i<m; i++){
    int a, b; cin >> a >> b;
    newlocations[i] = P(a, b);
  }
  
  Triangulation t;
  t.insert(oldlocations.begin(), oldlocations.end());
  
  for(int i=0; i<m; i++){
    auto npAuto = t.nearest_vertex(newlocations[i]);
    P nearestPoint = npAuto->point();
    double d = CGAL::squared_distance(newlocations[i], nearestPoint);
    cout << (long long)d << "\n";
  }
  return;
}

signed main(){
  ios_base::sync_with_stdio(false);
  while(true){
    int n; cin >> n;
    if(n==0){ break;}
    solve(n);
  }
  return 0;
}