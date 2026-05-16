#include <iostream>
// BGL include
#include <boost/graph/adjacency_list.hpp>
// BGL flow include *NEW*
#include <boost/graph/push_relabel_max_flow.hpp>
#include <vector>

// Graph Type with nested interior edge properties for flow algorithms
typedef boost::adjacency_list_traits<boost::vecS, boost::vecS, boost::directedS> traits;
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS, boost::no_property,
boost::property<boost::edge_capacity_t, long,
boost::property<boost::edge_residual_capacity_t, long,
boost::property<boost::edge_reverse_t, traits::edge_descriptor>>>> graph;
typedef traits::vertex_descriptor vertex_desc;
typedef traits::edge_descriptor edge_desc;

using namespace std;

#define int long

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

bool solve(){
  int l, p; cin >> l >> p;
  graph G(l);
  edge_adder adder(G);
  vertex_desc v_source = boost::add_vertex(G);
  vertex_desc v_sink = boost::add_vertex(G);
  long totalarmies = 0;
  long requiredSum = 0;
  vector<int>demand(l, 0);
  
  for(int i=0; i<l; i++){
    int g, d; cin >> g >> d;
    totalarmies += (long)g;
    requiredSum += (long)d;
    demand[i] = d-g;
  }
  
  for(int i=0; i<p; i++){
    int from, to, minflow, maxflow; cin >> from >> to >> minflow >> maxflow;
    int dif = maxflow-minflow;
    if(dif){
    adder.add_edge(from, to, dif);
    }
    demand[from] += minflow;
    demand[to] -= minflow;
  }
  
  
  long totaldemand = 0;
  for(int i=0; i<l; i++){
    if(demand[i] > 0){
      adder.add_edge(i, v_sink, demand[i]);
      totaldemand += demand[i];
    }
    else{
      adder.add_edge(v_source, i, -demand[i]);
    }
  }
  
  long flow = boost::push_relabel_max_flow(G, v_source, v_sink);
  if(flow == totaldemand){
    return true;
  }
  else{
    return false;
  }
}

signed main(){
  int t; cin >> t;
  while(t--){ 
    if(solve()){
      cout << "yes\n";
    }
    else{
      cout << "no\n";
    }
  }
  return 0;
}

