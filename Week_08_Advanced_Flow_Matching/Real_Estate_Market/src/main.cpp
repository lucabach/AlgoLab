#include <vector>
#include <iostream>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/cycle_canceling.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>
#include <boost/graph/successive_shortest_path_nonnegative_weights.hpp>
#include <boost/graph/find_flow_cost.hpp>

// graph Type with nested interior edge properties for Cost Flow Algorithms
typedef boost::adjacency_list_traits<boost::vecS, boost::vecS, boost::directedS> traits;
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS, boost::no_property,
    boost::property<boost::edge_capacity_t, long,
        boost::property<boost::edge_residual_capacity_t, long,
            boost::property<boost::edge_reverse_t, traits::edge_descriptor,
                boost::property <boost::edge_weight_t, long> > > > > graph; // new! weightmap corresponds to costs

typedef boost::graph_traits<graph>::edge_descriptor             edge_desc;
typedef boost::graph_traits<graph>::out_edge_iterator           out_edge_it; // Iterator
typedef traits::vertex_descriptor vertex_desc;
typedef traits::edge_descriptor edge_desc;

// custom edge adder class
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
    c_map[rev_e] = 0; // reverse edge has no capacity!
    r_map[e] = rev_e;
    r_map[rev_e] = e;
    w_map[e] = cost;   // new assign cost
    w_map[rev_e] = -cost;   // new negative cost
  }
};

using namespace std;


void solve(){
  int n, m, s; cin >> n >> m >> s;
  graph G(n+m+s);
  const vertex_desc v_source = boost::add_vertex(G);
  const vertex_desc v_sink = boost::add_vertex(G);
  edge_adder adder(G);
  for(int i=0; i<s; i++){
    int si; cin >> si;
    adder.add_edge(n+m+i, v_sink, si, 0);
  }
  for(int i=0; i<m; i++){
    int si; cin >> si;
    adder.add_edge(n+i, n+m+si-1, 1, 0);
  }
  for(int i=0; i<n; i++){
    for(int j=0; j<m; j++){
      int bid; cin >> bid;
      adder.add_edge(i, n+j, 1, -bid + 100);
    }
  }
  
  for(int i=0; i<n; i++){
    adder.add_edge(v_source, i, 1, 0);
  }
  
  int flow = boost::push_relabel_max_flow(G, v_source, v_sink);
  
  boost::successive_shortest_path_nonnegative_weights(G, v_source, v_sink);
  int cost = boost::find_flow_cost(G);
  cout << flow << " " << -cost + flow*100 << "\n";
}

signed main(){
  int t; cin >> t;
  while(t--){
    solve();
  }
  return 0;
}