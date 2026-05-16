#include <iostream>
#include <vector>
#include <utility>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>

typedef boost::adjacency_list_traits<boost::vecS, boost::vecS, boost::directedS> traits;
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS, boost::no_property,
boost::property<boost::edge_capacity_t, long,
boost::property<boost::edge_residual_capacity_t, long,
boost::property<boost::edge_reverse_t, traits::edge_descriptor>>>> graph;
typedef traits::vertex_descriptor vertex_desc;
typedef traits::edge_descriptor edge_desc;

using namespace std;

class edge_adder {
graph &G;
public:
explicit edge_adder(graph &G) : G(G) {}
void add_edge(int from, int to, long capacity) {
auto c_map = boost::get(boost::edge_capacity, G);
auto r_map = boost::get(boost::edge_reverse, G);
const auto e = boost::add_edge(from, to, G).first;
const auto rev_e = boost::add_edge(to, from, G).first;
c_map[e] = capacity;
c_map[rev_e] = 0; // reverse edge has no capacity!
r_map[e] = rev_e;
r_map[rev_e] = e;
}
};

bool is_inside(int x, int y, int n){
  return x<n && x>=0 && y<n && y>=0;
}

vector<pair<int, int>> neighbors(int i, int j, int n, const vector<vector<bool>> &is_present){
  vector<pair<int, int>> neighbors;
  if(is_inside(i-1, j-2,n)&& is_present[i-1][j-2]){neighbors.push_back({i-1, j-2});}
  if(is_inside(i-1, j+2,n)&& is_present[i-1][j+2]){neighbors.push_back({i-1, j+2});}
  if(is_inside(i+1, j-2,n)&& is_present[i+1][j-2]){neighbors.push_back({i+1, j-2});}
  if(is_inside(i+1, j+2,n)&& is_present[i+1][j+2]){neighbors.push_back({i+1, j+2});}
  if(is_inside(i-2, j-1,n)&& is_present[i-2][j-1]){neighbors.push_back({i-2, j-1});}
  if(is_inside(i-2, j+1,n)&& is_present[i-2][j+1]){neighbors.push_back({i-2, j+1});}
  if(is_inside(i+2, j-1,n)&& is_present[i+2][j-1]){neighbors.push_back({i+2, j-1});}
  if(is_inside(i+2, j+1,n)&& is_present[i+2][j+1]){neighbors.push_back({i+2, j+1});}
  return neighbors;
}

void solve(){
  int n; cin >> n;
  vector<vector<bool>> is_present(n, vector<bool>(n));
  int holes = 0;
  for(int i=0; i<n; i++){
    for(int j=0; j<n; j++){
      bool h; cin >> h;
      is_present[i][j] = h;
      if(!h){
        holes += 1;
      }
    }
  }
  
  graph G(n*n);
  edge_adder adder(G);
  for(int i=0; i<n; i++){
    for(int j=0; j<n; j++){
      if((i+j) % 2 == 0 && is_present[i][j]){
        vector<pair<int, int>> neighborVec = neighbors(i, j, n, is_present);
        for(size_t k = 0; k<neighborVec.size(); k++){
          adder.add_edge(i*n + j, neighborVec[k].first*n + neighborVec[k].second, 1);
        }
      }
    }
  }
  
  const vertex_desc v_source = boost::add_vertex(G);
  const vertex_desc v_sink = boost::add_vertex(G);
  for(int i=0; i<n; i++){
    for(int j=0; j<n; j++){
      if(is_present[i][j]){
      if((i+j) % 2 == 0){
        adder.add_edge(v_source, i*n + j, 1);
      }
      else{
        adder.add_edge(i*n+j, v_sink, 1);
      }
      }
    }
  }
  
  long flow = boost::push_relabel_max_flow(G, v_source, v_sink);
  long result = n*n - holes - flow;
  cout << result << "\n";
  return;
}

signed main(){
  int t; cin >> t;
  while(t--){
    solve();
  }
  return 0;
}