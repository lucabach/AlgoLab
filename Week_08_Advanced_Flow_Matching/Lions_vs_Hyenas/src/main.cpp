#include <iostream>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>

using namespace std;


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

void solve(){
  int n, b, simba, nala; cin >> n >> b >> simba >> nala;
  
  graph G1(n); edge_adder adder1(G1);
  graph G2(n); edge_adder adder2(G2);
  int affSimba = -1;
  int affNala = -1;
  int total = 0;
  
  for(int i=0; i<n; i++){
    int a; cin >> a;
    if(i==simba){
      affSimba = a;
    }
    else if(i==nala){
      affNala = a;
    }
    else{
      if(a!=0){
      if(a>0){
        adder1.add_edge(simba, i, a);
        adder2.add_edge(i, nala, a);
      }
      else{
        adder1.add_edge(i, nala, -a);
        adder2.add_edge(simba, i, -a);
      }
    }
    }
    total += abs(a);
  }

  for(int i=0; i<n; i++){
    for(int j=0; j<n; j++){
      int f; cin >> f;
      if(i!=j && f != 0){
        adder1.add_edge(i, j, f);
        adder2.add_edge(i, j, f);
      }
      if(i<j){
        total += f;
      }
    }
  }
  
  int mindis1 = boost::push_relabel_max_flow(G1, simba, nala);
  int mindis2 = boost::push_relabel_max_flow(G2, simba, nala);
  
  if(affSimba < 0){
    mindis1 -= affSimba;
  }
  else{
    mindis2 += affSimba; 
  }
  
  if(affNala < 0){
    mindis2 -= affNala;
  }
  else{
    mindis1 += affNala; 
  }
  
  int mindis = min(mindis1, mindis2);
  if(b==1){
    cout << mindis << "\n";
  }
  else{
    cout << total - 2*mindis << "\n";
  }
}

signed main(){
  int t; cin >> t;
  while(t--){
    solve();
  }
  return 0;
}