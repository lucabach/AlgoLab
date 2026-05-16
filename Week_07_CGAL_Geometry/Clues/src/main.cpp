
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Triangulation_face_base_with_info_2.h>
#include <CGAL/Triangulation_vertex_base_with_info_2.h>
#include <queue>
#include <unordered_map>
#include <utility>

using namespace std;

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Triangulation_vertex_base_with_info_2<pair<int, int>, K> Vb;
typedef CGAL::Triangulation_face_base_2<K> Fb;
typedef CGAL::Triangulation_data_structure_2<Vb,Fb> Tds;
typedef CGAL::Delaunay_triangulation_2<K,Tds> Triangulation;
typedef Triangulation::Vertex_handle V;
typedef K::Point_2 P;


Triangulation t;
unordered_map<V, int> vHandleIdx;
vector<pair<int, int>> vProperties;

bool has_interference(const Triangulation &tr, const long &r2){
  for(auto e = tr.finite_edges_begin(); e!=tr.finite_edges_end(); e++){
    if(tr.segment(*e).squared_length() <= r2){
      return true;
    }
  }
  return false;
}

pair<bool, int> checkInterference(const int &nstations, const long &r2){
  vHandleIdx.clear();
  vProperties.clear();
  vProperties.resize(nstations);
  int idx=0;
  for(auto v = t.finite_vertices_begin(); v != t.finite_vertices_end(); v++){
    vHandleIdx[v] = idx; idx++;
    v->info() = {-1, -1};
  }
  
  int curComponent = -1;
  for(auto v = t.finite_vertices_begin(); v != t.finite_vertices_end(); v++){
    queue<V> q;
    if(v->info().first == -1){
      //cout << "inspecting point " << vHandleIdx[v] << "\n";
      curComponent++;
      q.push(v);
      v->info() = {0, curComponent};
      vProperties[vHandleIdx[v]] = {0, curComponent};
      //cout << "vproperties point " << vHandleIdx[v] << ": color 0, component: " << curComponent << "\n";
    while(!q.empty()){
      V curVertex = q.front(); q.pop();
      //cout << "Popped point " << vHandleIdx[curVertex] << "\n";
      int curColor = curVertex->info().first;
      
      Triangulation::Vertex_circulator curNeighbor = t.incident_vertices(curVertex), done = curNeighbor;
      if(curNeighbor != 0){
      do {
      if(!t.is_infinite(curNeighbor)){
      long sqdist = CGAL::squared_distance(curVertex->point(), curNeighbor->point());
      if(sqdist <= r2){
        //cout << "found point " << vHandleIdx[curNeighbor] << " in range\n";
        if(curNeighbor->info().first == -1){
          curNeighbor->info() = {(curColor+1)%2, curComponent};
          vProperties[vHandleIdx[curNeighbor]] = {(curColor+1)%2, curComponent};
          q.push(curNeighbor);
          //cout << "vproperties point " << vHandleIdx[curNeighbor] << ": color " << (curColor+1)%2 << ", component: " << curComponent << "\n";
        }
      }
      }
      } while (++curNeighbor != done);
      }
    }
    }
  }
     Triangulation red, black;

  for (auto v = t.finite_vertices_begin(); v != t.finite_vertices_end(); ++v) {
    if (v->info().first == 0) {
      red.insert(v->point());
    } else {
      black.insert(v->point());
    }
  }

  // Check for same-color interference
  if (has_interference(red, r2) || has_interference(black, r2)) {
    return {true, 0};
  }

  return {false, curComponent + 1};
}
  


void solve(){
  //cout << "----------------------------\n";
  long n, m, r; cin >> n >> m >> r;
  vector<P> stations(n);
  
  for(int i=0; i<n; i++){
    long x, y; cin >> x >> y;
    stations[i] = P(x, y);
  }
  
  t.clear();
  t.insert(stations.begin(), stations.end());
  
  auto bigboy = checkInterference(n, r*r);
  bool network_has_interference = bigboy.first;
  //int nComponents = bigboy.second;
  
  for(int i=0; i<m; i++){
    //cout << "**********************\n";
    long a1, a2, a3, a4; cin >> a1 >> a2 >> a3 >> a4;
    
    if(network_has_interference){cout << "n"; continue;}
    
    P holmes(a1, a2);
    P watson(a3, a4);
    double sqdist1 = CGAL::squared_distance(holmes, watson);
    
    if(sqdist1 <= (double)r*r){ cout << "y"; continue; }
    
    auto nearestHolmes = t.nearest_vertex(holmes);
    auto nearestWatson = t.nearest_vertex(watson);
    
    double sqdist2 = CGAL::squared_distance(holmes, nearestHolmes->point());
    double sqdist3 = CGAL::squared_distance(watson, nearestWatson->point());
    
    if(sqdist2 > (double)r*r || sqdist3 > (double)r*r){ cout << "n"; continue; }
    
    if(vProperties[vHandleIdx[nearestHolmes]].second == vProperties[vHandleIdx[nearestWatson]].second){
         cout << "y";
    }
    else{ cout << "n";
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