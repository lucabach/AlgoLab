
#include <iostream>
#include <vector>
#include <boost/graph/strong_components.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <limits>


typedef boost::adjacency_list<
boost::vecS,
boost::vecS,
boost::directedS,
boost::no_property, // no vertex property
boost::property<boost::edge_weight_t, int> // edge property (interior)
> graph;
typedef boost::graph_traits<graph>::vertex_descriptor vertex_desc;

using namespace std;

vector<int> dijkstra_dist(const graph &G, int s) {
int n = boost::num_vertices(G);
std::vector<int> dist_map(n); //exterior property
boost::dijkstra_shortest_paths(G, s,
boost::distance_map(boost::make_iterator_property_map(dist_map.begin(),
boost::get(boost::vertex_index, G))));
return dist_map;
}

vector<int> strong_connected_comp(const graph &G) {
int n = boost::num_vertices(G);
std::vector<int> scc_map(n); // exterior property map
int nscc = boost::strong_components(G,
boost::make_iterator_property_map(scc_map.begin(),
boost::get(boost::vertex_index, G)));
return scc_map; }


void solve(){
  int n, m, k, T; cin >> n >> m >> k >> T;
  vector<int>fastPlanets(T);
  vector<pair<int, int>> edgesLeavingWH;
  vector<pair<int, int>> edgesEnteringWH;
  
  for(int i=0; i<T; i++){
    int x; cin >> x;
    fastPlanets[i] = x;
  }
  
  graph G(2*n + 1);
  for(int i=0; i<m; i++){
    int x, y, c; cin >> x >> y >> c;
    boost::add_edge(y, x, c, G);
  }
  

  vector<int> component = strong_connected_comp(G);

  int scc = 0;
  for(int i=0; i<n; i++){
  scc = max(scc, component[i]);
  }
  scc += 1;
  
  //cout << "SCC: " << scc << "\n";
  vector<int> telenodes_in_scc(scc, 0);
  
  for(int i=0; i<T; i++){
    telenodes_in_scc[component[fastPlanets[i]]] += 1;
  }
  

  //cout << "\n";
  for(int telenode : fastPlanets){
    int curComp = component[telenode];
    if(telenodes_in_scc[curComp] > 1){
    boost::add_edge(telenode, n+curComp, telenodes_in_scc[curComp]-1, G);
    boost::add_edge(n+curComp, telenode, 0, G);
    //cout << "added edge " << telenode << " - " << n+curComp << " with cost " << telenodes_in_scc[curComp] << "\n";
    }
  }
  
  int min_dist = numeric_limits<int>::max();
  vector<int> dijkstra_vec = dijkstra_dist(G, n-1);
  for(int i=0; i<k; i++){
    min_dist = min(min_dist, dijkstra_vec[i]);
  }

  if(min_dist <= 1000000){
    cout << min_dist << "\n";
  }
  else{
    cout << "no\n";
  }
}

signed main(){
  int t; cin >> t;
  while(t--){
    solve();
  }
  return 0;
}