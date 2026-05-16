#include <iostream>
#include <vector>
#include <map>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Exact_predicates_exact_constructions_kernel_with_sqrt.h>
#include <CGAL/Delaunay_triangulation_2.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef K::Point_2 P;
typedef CGAL::Delaunay_triangulation_2<K> Triangulation;
typedef Triangulation::Finite_faces_iterator Face_iterator;

using namespace std;

void solve(const int &n){
  int l, b, r, top; cin >> l >> b >> r >> top;
  vector<P> center(n);
  for(int i=0; i<n; i++){
    int a,b; cin >> a >> b;
    center[i] = P(a, b);
  }
  
  map<P, int> idxmap;
  for(int i=0; i<n; i++){
    idxmap[center[i]] = i;
  }
  
  vector<K::FT> bordercollision(n);
  for(int i=0; i<n; i++){
    int x = center[i].x();
    int y = center[i].y();
    int dx = min(abs(x-l), abs(r-x));
    int dy = min(abs(y-b), abs(top-y));
    int d = min(dx, dy);
    K::FT tt = d - 0.5;
    bordercollision[i] = tt;
  }
  
  Triangulation t;
  t.insert(center.begin(), center.end());
  vector<K::FT> circlecollision(n);
  
  for(auto v = t.finite_vertices_begin(); v != t.finite_vertices_end(); v++){
    int i = idxmap[v->point()];
    Triangulation::Edge_circulator c = t.incident_edges(v);
    
    K::FT min_sqd = 1e18;
    if(c!=0){
      do{
        if(!t.is_infinite(c)){
          K::FT sqd = t.segment(c).squared_length();
          min_sqd = min(min_sqd, sqd);
        }
      } while(++c != t.incident_edges(v));
    }
    
    K::FT min_d = min_sqd;
    if(min_d >= 1.0){
      K::FT tt = (sqrt(min_d) - 1.00) / 2.00;
      circlecollision[i] = tt;
    }
    else{
      circlecollision[i] = 0;
    }
  }
  
  vector<K::FT> collision(n);
  for(int i=0; i<n; i++){
    collision[i] = min(bordercollision[i], circlecollision[i]);
  }
  sort(collision.begin(), collision.end());
  cout << ceil(sqrt(collision[0])) << " " << ceil(sqrt(collision[floor(n/2)])) << " " << ceil(sqrt(collision[n-1])) << "\n";
  return;
}

signed main(){
  ios_base::sync_with_stdio(false);
  while(true){
    int n; cin >> n;
    if(n==0){
      break;
    }
    solve(n);
  }
  return 0;
}