#include <iostream>
#include <vector>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>

typedef boost::adjacency_list_traits<boost::vecS, boost::vecS, boost::directedS> traits;
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS, boost::no_property,
boost::property<boost::edge_capacity_t, int,
boost::property<boost::edge_residual_capacity_t, int,
boost::property<boost::edge_reverse_t, traits::edge_descriptor>>>> graph;
typedef traits::vertex_descriptor vertex_desc;
typedef traits::edge_descriptor edge_desc;

using namespace std;

#define int long

class edge_adder {
  graph &G;
  public:
    explicit edge_adder(graph &G) : G(G) {}
  void add_edge(int from, int to, int capacity) {
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


void solve(){
  int n, m;
  cin >> n >> m;
  graph G(m+n);
  edge_adder adder(G);
  const vertex_desc v_source = boost::add_vertex(G);
  
  for(int i=0; i<m; i++){
    int a,b,c; cin >> a >> b >> c;
    adder.add_edge(v_source, i, 1);
    
    if(c==1){
      adder.add_edge(i, a+m, 1);
    }
    else if(c==2){
      adder.add_edge(i, b+m, 1);
    }
    else{
      adder.add_edge(i, b+m, 1);
      adder.add_edge(i, a+m, 1);
    }
  }
  
  const vertex_desc v_sink = boost::add_vertex(G);
  int scores_sum = 0;
  
  for(int i=0; i<n; i++){
    int final_score; cin >> final_score;
    scores_sum += final_score;
    adder.add_edge(i+m, v_sink, final_score);
  }
  
  if(scores_sum != m){
    cout << "no" << "\n";
    return;
  }
  int flow = boost::push_relabel_max_flow(G, v_source, v_sink);
  if(flow == m){
    cout << "yes" << "\n";
    return;
  }
  
  cout << "no" << "\n";
  return;
}


signed main(){
  int t; cin >> t;
  while(t--){
    solve();
  }
  return 0;
}