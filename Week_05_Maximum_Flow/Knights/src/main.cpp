#include <iostream>
#include<vector>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>
#include <utility>

typedef boost::adjacency_list_traits<boost::vecS, boost::vecS, boost::directedS> traits;
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS, boost::no_property,
boost::property<boost::edge_capacity_t, long,
boost::property<boost::edge_residual_capacity_t, long,
boost::property<boost::edge_reverse_t, traits::edge_descriptor>>>> graph;
typedef traits::vertex_descriptor vertex_desc;
typedef traits::edge_descriptor edge_desc;

using namespace std;

inline int IN(int i, int j, int n){ return 2*(i*n + j);}
inline int OUT(int i, int j, int n){ return 2*(i*n + j)+1;}

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
  int n, m, k, c; cin >> n >> m >> k >> c;
  vector<int> knight(k);
  for(int i=0; i<k; i++){
    int a, b; cin >> a >> b;
    knight[i] = IN(b, a, n);
  }
  
  graph G(2*m*n + 2);
  edge_adder adder(G);
  int v_sink = 2*m*n + 1;
  int v_source = 2*m*n;
  
  for(int i=0; i<m; i++){
    for(int j=0; j<n; j++){
      
      adder.add_edge(IN(i, j, n), OUT(i, j, n), c);
      if(j==0 || i==0 || j== n-1 || i == m-1){
        int ways = 1;
        if((i==0 || i==m-1) && (j ==0 || j==n-1)){
          ways = 2;
        }
        adder.add_edge(OUT(i, j, n), v_sink, ways);
      }
      
      if(j != n-1){
        adder.add_edge(OUT(i, j, n), IN(i, j+1, n), 1);
        adder.add_edge(OUT(i, j+1, n), IN(i, j, n), 1);
      }

      if(i != m-1){
        adder.add_edge(OUT(i, j, n), IN(i+1, j, n), 1);
        adder.add_edge(OUT(i+1, j, n), IN(i, j, n), 1);
      }
    }
  }
  
  for(int i=0; i<k; i++){
    adder.add_edge(v_source, knight[i], 1);
  }
  
  long flow = boost::push_relabel_max_flow(G, v_source, v_sink);
  cout << flow << "\n";
  return;
}

signed main(){
  ios_base::sync_with_stdio(false);
  int t; cin >> t;
  while(t--){
    solve();
  }
  return 0;
}