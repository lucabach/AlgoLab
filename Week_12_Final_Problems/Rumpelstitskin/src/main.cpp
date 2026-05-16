#include <iostream>
#include <vector>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>
#include <boost/graph/cycle_canceling.hpp>
#include <unordered_map>
#include <boost/graph/successive_shortest_path_nonnegative_weights.hpp>

typedef boost::adjacency_list_traits<boost::vecS, boost::vecS, boost::directedS> traits;
// new: weightmap for costs
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS, boost::no_property,
boost::property<boost::edge_capacity_t, long,
boost::property<boost::edge_residual_capacity_t, long,
boost::property<boost::edge_reverse_t, traits::edge_descriptor,
boost::property<boost::edge_weight_t, long> > > > >
graph;
typedef boost::graph_traits<graph>::edge_descriptor edge_desc;
typedef boost::graph_traits<graph>::vertex_descriptor vertex_desc;
typedef boost::graph_traits<graph>::out_edge_iterator out_edge_it;

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
w_map[e] = cost; // new assign cost
w_map[rev_e] = -cost; // new negative cost
}
};

using namespace std;

void solve(){
  int n, pg, ph, eg, eh, fg, fh, sg, sh; 
  cin >> n >> pg >> ph >> eg >> eh >> fg >> fh >> sg >> sh;
  
  unordered_map<vertex_desc, int> vIdx;
  
  vector<int> p_score(n);
  for(int i=0; i<n; i++){
    int ps; cin >> ps;
    p_score[i] = ps;
  }
  
  vector<pair<bool, bool>> constraint(n);
  graph G(pg+ph+ 2*n);
  vertex_desc v_source = boost::add_vertex(G);
  vertex_desc v_sink = boost::add_vertex(G);
  edge_adder adder(G);
  
  adder.add_edge(v_source, 0, sg, 0);
  adder.add_edge(pg, v_sink, sh, 0);
  //cout << "added edge " << v_source << " - " << 0 << "with capacity " << sg << "\n";
  //cout << "added edge " << v_source << " - " << pg << "with capacity " << sh << "\n";
  
  for(int i=0; i<eg; i++){
    int u, v, c; cin >> u >> v >> c;
    adder.add_edge(u, v, c, 0);
    //cout << "added edge " << u << " - " << v << "with capacity " << c << "\n";
  }
  
  for(int i=0; i<eh; i++){
    int u, v, c; cin >> u >> v >> c;
    adder.add_edge(v+pg, u+pg, c, 0);
    //cout << "added edge " << u+pg << " - " << v+pg << "with capacity " << c << "\n";
  }
  
  for(int i=0; i<fg; i++){
    int u, v, c; cin >> u >> v >> c;
    adder.add_edge(u, 2*v +pg+ph, c, 0);
    //cout << "added edge " << u << " - " << v+pg+ph << "with capacity " << c << "\n";
  }
  
  int extra = pow(2, 10);
  for(int i=0; i<n; i++){
    adder.add_edge(2*i + pg + ph, 2*i + 1 + pg + ph, 1, -p_score[i] + extra);
  }
  
  for(int i=0; i<fh; i++){
    int u, v, c; cin >> u >> v >> c;
    adder.add_edge(2*v + 1 +pg+ph, u+pg, c, 0);
    //cout << "added edge " << u+pg << " - " << v+pg+ph << "with capacity " << c << "\n";
  }
  
  //int flow = boost::push_relabel_max_flow(G, v_source, v_sink);
  //boost::cycle_canceling(G);
  //int cost1 = - boost::find_flow_cost(G);
  //cout << flow << " " << cost1 << "\n";
  
  boost::successive_shortest_path_nonnegative_weights(G, v_source, v_sink);
  int cost2 = boost::find_flow_cost(G);
  
  int s_flow = 0;
  out_edge_it e, eend;
  auto c_map = get(boost::edge_capacity, G); 
  auto rc_map = get(boost::edge_residual_capacity, G);
  for (boost::tie(e, eend) = boost::out_edges(boost::vertex(v_source,G), G); e != eend; ++e){
    s_flow += c_map[*e] - rc_map[*e];
  }
  
  int cost2real = -(cost2 - s_flow*pow(2, 10));
  cout << s_flow << " " << cost2real << "\n";
}

signed main(){
  int t; cin >> t;
  while(t--){
    solve();
  }
  return 0;
}



