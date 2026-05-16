#include <iostream>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <vector>


typedef boost::adjacency_list_traits<boost::vecS, boost::vecS, boost::directedS> traits;
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS, boost::no_property,
boost::property<boost::edge_capacity_t, long,
boost::property<boost::edge_residual_capacity_t, long,
boost::property<boost::edge_reverse_t, traits::edge_descriptor,
boost::property <boost::edge_weight_t, long>>>>> graph;
typedef boost::graph_traits<graph>::vertex_descriptor vertex_desc;
typedef boost::graph_traits<graph>::edge_descriptor edge_desc;
typedef boost::graph_traits<graph>::edge_iterator edge_it;

#define int long
using namespace std;

class edge_adder {
graph &G;
public:
explicit edge_adder(graph &G) : G(G) {}
void add_edge(int from, int to, long capacity, long cost) {
auto c_map = boost::get(boost::edge_capacity, G);
auto r_map = boost::get(boost::edge_reverse, G);
auto w_map = boost::get(boost::edge_weight, G); // new!
const edge_desc e = boost::add_edge(from, to, G).first;
const edge_desc rev_e = boost::add_edge(to, from, G).first;
c_map[e] = capacity;
c_map[rev_e] = capacity; // reverse edge has no capacity!
r_map[e] = rev_e;
r_map[rev_e] = e;
w_map[e] = cost; // new assign cost
w_map[rev_e] = cost; // new negative cost
}
};


vector<int> dijkstra_dist(const graph &G, int s) {
int n = boost::num_vertices(G);
std::vector<int> dist_map(n); //exterior property
boost::dijkstra_shortest_paths(G, s,
boost::distance_map(boost::make_iterator_property_map(dist_map.begin(),
boost::get(boost::vertex_index, G))));
return dist_map;}
  
void solve(){
  int n, m, s, f; cin >> n >> m >> s >> f;
  graph G(n);
  edge_adder adder(G);
  for(int i=0; i<m; i++){
    int a, b, c, d; cin >> a >> b >> c >> d;
    adder.add_edge(a, b, c, d);
  }
  
  vector<int> start_map = dijkstra_dist(G, s);
  int min_dist = start_map[f];
  
  vector<int> finish_map = dijkstra_dist(G, f);
  
  auto c_map = boost::get(boost::edge_capacity, G);
  auto w_map = boost::get(boost::edge_weight, G);
  edge_it e_beg, e_end;
  for (boost::tie(e_beg, e_end) = boost::edges(G); e_beg != e_end; ++e_beg) {
    int u = boost::source(*e_beg, G);
    int v = boost::target(*e_beg, G);
    int edgeCost = w_map[*e_beg];
    if(start_map[u] + edgeCost + min_dist - start_map[v] != min_dist){
      c_map[*e_beg] = 0;
    }
  }
  
  long flow = boost::push_relabel_max_flow(G, s, f);
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
