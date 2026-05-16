
#include <iostream>
#include <vector>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Triangulation_vertex_base_with_info_2.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <queue>
#include <limits>
#include <CGAL/squared_distance_2.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Triangulation_vertex_base_with_info_2<bool, K> Vb;
typedef CGAL::Triangulation_data_structure_2<Vb> Tds;
typedef CGAL::Delaunay_triangulation_2<K,Tds> Triangulation;
typedef Triangulation::Vertex_circulator Vertex_circulator;
typedef Triangulation::Finite_vertices_iterator Finite_vertices_iterator;
typedef Triangulation::Finite_faces_iterator Face_iterator;
typedef Triangulation::Vertex_handle V;
typedef K::Point_2 P;

using namespace std;
Triangulation t;

int biggest_connected_component(const long &r2){
  //cout << "entered\n";
  for(auto v = t.finite_vertices_begin(); v!=t.finite_vertices_end(); v++){
    v->info() = false;
  }
  int biggest_component = 0;
  for(auto v = t.finite_vertices_begin(); v!=t.finite_vertices_end(); v++){
    queue<V>q;
    if(!v->info()){
      q.push(v);
      int curSize = 0;
      while(!q.empty()){
        V curVertex = q.front(); q.pop();
        if(!curVertex->info()){
          curVertex->info() = true;
          curSize += 1;
          
          Triangulation::Vertex_circulator curNeighbor = t.incident_vertices(curVertex), done = curNeighbor;
          do{
            if(!t.is_infinite(curNeighbor) && curNeighbor != 0 && !curNeighbor->info()){
              //cout << "inspecting neighbor...";
              long sqdist = CGAL::squared_distance(curVertex->point(), curNeighbor->point());
              if(sqdist <= r2){
                //cout << "pushed neighbor";
                q.push(curNeighbor);
              }
              //cout << "\n";
            }
          } while (++curNeighbor != done);
        } 
      }
      biggest_component = max(biggest_component, curSize);
    }
  }
  return biggest_component;
}

void solve(){
  int n, r; cin >> n >> r;
  vector<P> planets(n);
  for(int i=0; i<n; i++){
    int x, y; cin >> x >> y;
    planets[i] = P(x, y);
  }
  
  int start = 0;
  int end = n/2;
  int best_candidate = 0;
  long r2 = long(r) * long(r);
  while(start<=end){
    int K = (end+start)/2;
    t.clear();
    t.insert(planets.begin() + K, planets.end());
    int C = biggest_connected_component(r2);
    //cout << "biggest connected component for k = " << K << " is " << C << "\n";
    best_candidate = max(best_candidate, min(K, C));
    if(K==C){
      best_candidate = K;
      break;
    }
    else if(K < C){
      start = K+1;
    }
    else if (K > C){
      end = K-1;
    }
  }
  cout << best_candidate << "\n";
}


signed main(){
  int T; cin >> T;
  while(T--){
    solve();
  }
  return 0;
}