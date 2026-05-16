#include <iostream>
#include <vector>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Triangulation_face_base_with_info_2.h>
#include <CGAL/squared_distance_2.h> 
#include <utility>
#include <limits>
#include <queue>


typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Triangulation_vertex_base_2<K> Vb;
typedef CGAL::Triangulation_face_base_with_info_2<double, K> Fb;
typedef CGAL::Triangulation_data_structure_2<Vb,Fb> Tds;
typedef CGAL::Delaunay_triangulation_2<K,Tds> Triangulation;
typedef Triangulation::Face_handle F;
typedef Triangulation::Vertex_handle V;
typedef K::Point_2 P;

#define int long

using namespace std;

Triangulation t;


void assign_max_escape_diameters(){
  double doublemax = numeric_limits<double>::max();
  priority_queue<pair<double, F>> q;
  for (auto f = t.all_faces_begin(); f != t.all_faces_end(); ++f){
    if(t.is_infinite(f)){
      q.emplace(doublemax, f);
    }
      f->info() = 0;
  }
  
  while(!q.empty()){
    auto curElem = q.top(); q.pop();
    double curMaxDiameter = curElem.first;
    F curFace = curElem.second;
    if(curFace->info() >= curMaxDiameter){ continue; }
    curFace->info() = curMaxDiameter;
    
    for(int i=0; i<3; i++){
      F curNeighbor = curFace->neighbor(i);
      if(t.is_infinite(curNeighbor) || curNeighbor->info() != 0){
        continue;
      }
      auto v1 = curFace->vertex((i+1) % 3);
      auto v2 = curFace->vertex((i+2) % 3);
      double squaredDiameter = CGAL::squared_distance(v1->point(), v2->point());
      double min_cost = min(squaredDiameter, curMaxDiameter);
      q.emplace(min_cost, curNeighbor);
    }
  }
}

void solve(const int &n){
  vector<P> infected(n);
  for(int i=0; i<n; i++){
    int x, y; cin >> x >> y;
    infected[i] = P(x, y);
  }
  
  t.clear();
  t.insert(infected.begin(), infected.end());
  assign_max_escape_diameters();
  
  int m; cin >> m;
  for(int i=0; i<m; i++){
    int x, y, d; cin >> x >> y >> d;
    P curPoint(x, y);
    if(CGAL::squared_distance(curPoint, (t.nearest_vertex(curPoint)->point())) < (double)d){
      cout << "n"; continue;
    }
    F curFace = t.locate(curPoint);
    if(t.is_infinite(curFace)){ cout << "y"; continue; }
    double cursquaredDiameter = curFace->info();
    if(cursquaredDiameter >= 4*d){
      cout << "y";
    }
    else {
      cout << "n";
    }
  }
  cout << "\n";
}

signed main(){
  while(true){
    int n; cin >> n;
    if(n==0){
      break;
    }
    else{
      solve(n);
    }
  }
}