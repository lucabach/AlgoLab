
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Triangulation_face_base_with_info_2.h>
#include <CGAL/Triangulation_vertex_base_with_info_2.h>
#include <queue>
#include <iostream>
#include <vector>
#include<tuple>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Triangulation_vertex_base_with_info_2<int, K> Vb;
typedef CGAL::Triangulation_face_base_2<K> Fb;
typedef CGAL::Triangulation_data_structure_2<Vb,Fb> Tds;
typedef CGAL::Delaunay_triangulation_2<K,Tds> Triangulation;
typedef K::Point_2 P;
typedef Triangulation::Face_handle F;
typedef Triangulation::Vertex_handle V;

using namespace std;

Triangulation t;
priority_queue <tuple<double, int, int, int>> edges;

void clear(priority_queue <tuple<double, int, int, int>> &pq){
  priority_queue <tuple<double, int, int, int>> pqnew;
  swap(pq, pqnew);
}

int assign_connected_components(const long &s){
  for(auto v = t.all_vertices_begin(); v != t.all_vertices_end(); v++){
    v->info() = -1;
  }
  
  int curComponent = -1;
  for(auto v = t.all_vertices_begin(); v != t.all_vertices_end(); v++){
    queue<V> q;
    if(!t.is_infinite(v)){
      if(v->info() == -1){
        curComponent++;
        v->info() = curComponent;
        q.push(v);
        
        
      while(!q.empty()){
        V curVertex = q.front(); q.pop();

        Triangulation::Vertex_circulator curNeighbor = t.incident_vertices(curVertex), done = curNeighbor;
        if(curNeighbor != 0){
        do {
          //cout << "inspecting neighbor..\n";
        if (!t.is_infinite(curNeighbor)) {
          long sqdist = CGAL::squared_distance(curVertex->point(), curNeighbor->point());
          //cout << "sqdist is " << sqdist << "\n";
          if(sqdist <= s && curNeighbor->info() == -1){
            curNeighbor->info() = curComponent;
            q.push(curNeighbor);
          }
          else if(curNeighbor->info() != -1){
            edges.emplace(-sqdist, 0, curNeighbor->info(), curComponent);
          }
        }
 } while (++curNeighbor != done);
}
}
}
}
}
return curComponent + 1;
}

void solve(){
  //cout << "-------------------------\n";
  long n, m, s, k; cin >> n >> m >> s >> k;
  vector<P> trees(n);
  for(int i=0; i<n; i++){
    long x, y; cin >> x >> y;
    trees[i] = P(x, y);
  }
  
  clear(edges);
  t.clear();
  t.insert(trees.begin(), trees.end());
  int components = assign_connected_components(s);
  
  
  vector<P> bones(m);
  vector<int> bonesInComponent(components, 0);
  
  for(int i=0; i<m; i++){
    long x, y; cin >> x >> y;
    bones[i] = P(x, y);
  }
  
  for(int i=0; i<m; i++){
    P curBone = bones[i];
    V nearestPoint = t.nearest_vertex(curBone);
    int curComponent = nearestPoint->info();
    double sqd = CGAL::squared_distance(curBone, nearestPoint->point());
    if(sqd <= (double)((double)s/4)){
      if(curComponent != -1){
      bonesInComponent[curComponent]++;
      //cout << "bones in component " << curComponent << " increased to " << bonesInComponent[curComponent] << "\n";
      }
    }
    else{
      if(curComponent != -1){
        edges.emplace(-sqd, 1, curComponent, -1);
    }
  }
  }
  
  int longest_path = 0;
  for(int i=0; i<components; i++){
    longest_path = max(longest_path, bonesInComponent[i]);
  }
  
  //long b = 4*s;
  if(longest_path >= k){
    cout << longest_path << " " << s << "\n"; return;
  }
  
  vector<int> jointcomponent(components);
  for(int i=0; i<components; i++){
    jointcomponent[i] = i;
  }
  double curLen = 0;
  vector<vector<bool>> unitedComponents(components, vector<bool>(components, false));
  while(!edges.empty()){
    auto curEdge = edges.top(); edges.pop();
    double curLen = -(get<0>(curEdge));
    if(get<1>(curEdge)){
      int curComp = get<2>(curEdge);
      if(++bonesInComponent[curComp] >= k){
        cout << longest_path << " " << 4*curLen << "\n"; return; 
      }
    }
    else{
      int comp1 = get<2>(curEdge); int comp2 = get<3>(curEdge);
      if(comp2 < comp1){
        swap(comp1, comp2);
      }
      if(!unitedComponents[comp1][comp2]){
        unitedComponents[comp1][comp2] = unitedComponents[comp2][comp1] = true;
        int fatherComponent = jointcomponent[comp1];
        jointcomponent[comp1] = jointcomponent[comp2] = fatherComponent;
        bonesInComponent[fatherComponent] = bonesInComponent[fatherComponent] + bonesInComponent[comp2];
        if (bonesInComponent[fatherComponent] >= k){
          cout << longest_path << " " << curLen << "\n"; return; 
        }
      }
    }
  }
  cout << longest_path << " " << curLen << "\n";
}

signed main(){
  ios_base::sync_with_stdio(false);
  int t; cin>>t;
  while(t--){
    solve();
  }
  return 0;
}