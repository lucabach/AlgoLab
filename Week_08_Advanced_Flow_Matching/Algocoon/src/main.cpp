#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <climits>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>

using traits = boost::adjacency_list_traits<
boost::vecS, boost::vecS, boost::directedS>;
using graph = boost::adjacency_list<
boost::vecS, boost::vecS, boost::directedS, boost::no_property,
boost::property<boost::edge_capacity_t, int,
boost::property<boost::edge_residual_capacity_t, int,
boost::property<boost::edge_reverse_t, traits::edge_descriptor> > > >;
using edge_desc = boost::graph_traits<graph>::edge_descriptor;
// custom edge adder class
class edge_adder {
graph &G;
public:
explicit edge_adder(graph &G) : G(G) {}
void add_edge(int from, int to, long capacity) {
auto c_map = boost::get(boost::edge_capacity, G);
auto r_map = boost::get(boost::edge_reverse, G);
const edge_desc e = boost::add_edge(from, to, G).first;
const edge_desc rev_e = boost::add_edge(to, from, G).first;
c_map[e] = capacity;
c_map[rev_e] = 0; // reverse edge has no capacity!
r_map[e] = rev_e;
r_map[rev_e] = e;
}
};

using namespace std;

void solve(){
int n, m;
cin >> n >> m;
graph G(n); edge_adder adder(G);
for(int i=0; i<m; i++){
  int x, y, c; cin >> x >> y >> c;
  adder.add_edge(x, y, c);
}

int min_cut = numeric_limits<int>::max();
for(int i=0; i<n; i++){
  int j = (i+1)%n;
  int curmincut = boost::push_relabel_max_flow(G, i, j);
  min_cut = min(min_cut, curmincut);
 }
 cout << min_cut << "\n";
}

signed main(){
  ios_base::sync_with_stdio(false);
  int t; cin >> t;
  while(t--){
    solve();
  }
  return 0;
}