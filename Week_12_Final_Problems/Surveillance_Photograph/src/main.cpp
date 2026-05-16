#include <iostream>
#include <vector>
// BGL include
#include <boost/graph/adjacency_list.hpp>
// BGL flow include *NEW*
#include <boost/graph/push_relabel_max_flow.hpp>
#include <limits>

// Graph Type with nested interior edge properties for flow algorithms
typedef boost::adjacency_list_traits<boost::vecS, boost::vecS, boost::directedS> traits;
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS, boost::no_property,
boost::property<boost::edge_capacity_t, long,
boost::property<boost::edge_residual_capacity_t, long,
boost::property<boost::edge_reverse_t, traits::edge_descriptor>>>> graph;
typedef traits::vertex_descriptor vertex_desc;
typedef traits::edge_descriptor edge_desc;

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

using namespace std;

void solve(){
  int n, m, nstations, nphotos; cin >> n >> m >> nstations >> nphotos;
  graph G(2*n);
  const vertex_desc v_source = boost::add_vertex(G);
  const vertex_desc v_sink = boost::add_vertex(G);
  edge_adder adder(G);
  vector<int> station(n);
  vector<int> photo(n);
  int intMax = numeric_limits<int>::max();
  for(int i=0; i<nstations; i++){
    int idx; cin >> idx;
    station[idx] += 1;
  }
  for(int i=0; i<nphotos; i++){
    int idx; cin >> idx;
    photo[idx] += 1;
  }
  for(int i=0; i<n; i++){
    if(station[i]){
      adder.add_edge(v_source, 2*i, station[i]);
      adder.add_edge(2*i + 1, v_sink,  station[i]);
    }
  }
  
  for(int i=0; i<n; i++){
    if(photo[i]){
      adder.add_edge(2*i, 2*i + 1, photo[i]);
    }
  }
  
  for(int i=0; i<m; i++){
    int x, y; cin >> x >> y;
    adder.add_edge(2*x, 2*y, intMax);
    adder.add_edge(2*x + 1, 2*y + 1, 1);
  }
  
  long flow = boost::push_relabel_max_flow(G, v_source, v_sink);
  cout << flow << "\n";
}


signed main(){
  ios_base::sync_with_stdio(false);
  int t; cin >> t;
  while(t--){
    solve();
  }
  return 0;
}