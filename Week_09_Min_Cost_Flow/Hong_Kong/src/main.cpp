///2
#include <iostream>
#include <queue>
#include <CGAL/Exact_predicates_exact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Triangulation_face_base_with_info_2.h>
#include <vector>
#include <algorithm>
#include <limits>
#include <CGAL/squared_distance_2.h> 

#include <utility>
#include <CGAL/utils.h>

using namespace std;

typedef CGAL::Exact_predicates_exact_constructions_kernel K;
typedef CGAL::Triangulation_vertex_base_2<K> Vb;
typedef CGAL::Triangulation_face_base_with_info_2<K::FT,K> Fb;
typedef CGAL::Triangulation_data_structure_2<Vb,Fb> Tds;
typedef CGAL::Delaunay_triangulation_2<K,Tds> Triangulation;
typedef K::Point_2 P;
typedef Triangulation::Face_handle F;
typedef Triangulation::Vertex_handle V;

Triangulation t;


void insert_max_reachable_circumradius(){
  priority_queue<pair<K::FT, F>> q;
  K::FT lmax = K::FT(int64_t(1)<<53) * K::FT(int64_t(1)<<53);
  
  for(auto f = t.all_faces_begin(); f!= t.all_faces_end(); f++){
    if(t.is_infinite(f)){
      q.emplace(lmax, f);
    }
    else{
      K::FT sq_circumradius = CGAL::squared_radius(f->vertex(0)->point(), f->vertex(1)->point(), f->vertex(2)->point());
      q.emplace(sq_circumradius, f);
    }
    f->info() = 0;
  }
  
  while(!q.empty()){
    auto curElem = q.top(); q.pop();
    K::FT proposedcost = curElem.first;
    F curFace = curElem.second;
    if(curFace->info() >= proposedcost){continue;}
    curFace->info() = proposedcost;
    for(int i=0; i<3; i++){
      F curNeighbor = curFace->neighbor(i);
      V v1 = curFace->vertex((i+1)%3);
      V v2 = curFace->vertex((i+2)%3);
      K::FT sqdist = CGAL::squared_distance(v1->point(), v2->point());
      K::FT minDiameter = min(proposedcost, sqdist);
      q.emplace(minDiameter, curNeighbor);
    }
  }
}

void solve(){
  long n, m, r; cin >> n >> m >> r;
  vector<P> trees(n);
  
  for(int i=0; i<n; i++){
    long x, y; cin >> x >> y;
    trees[i] = P(x, y);
  }
  
  t.clear();
  t.insert(trees.begin(), trees.end());
  insert_max_reachable_circumradius();
  

  for(int i=0; i<m; i++){
    long x, y, s; cin >> x >> y >> s;
    P curBalloon(x, y);
    V nearestTree = t.nearest_vertex(curBalloon);
    F curFace = t.locate(curBalloon);
    
    K::FT sqdist = CGAL::squared_distance(curBalloon, nearestTree->point());
    K::FT puncture_limit = K::FT(r) + K::FT(s);
    
    if(sqdist < puncture_limit*puncture_limit){
      cout << "n"; continue;
    }
    
    if(t.is_infinite(curFace)){
      cout << "y"; continue;
    }
    
    //cout << "\nballoon: (" << curBalloon.x() << ", " << curBalloon.y() << "),";
    //cout << "clearance diameter: " << (double) sq_clearance_diameter << ", ";
    K::FT path_limit = K::FT(2) * (K::FT(r) + K::FT(s));
    if(curFace->info()  < path_limit*path_limit){
      cout << "n";
    }
    else{
      cout << "y";
    }
  }
  cout << "\n";
}


signed main(){
  ios_base::sync_with_stdio(false);
  int T; cin >> T;
  while(T--){
    solve();
  }
  return 0;
}