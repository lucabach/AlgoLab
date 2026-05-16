///1
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <boost/graph/max_cardinality_matching.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <vector>
#include <iostream>

using namespace std;

typedef boost::adjacency_list<
boost::vecS,
boost::vecS,
boost::directedS,
boost::no_property, // no vertex property
boost::property<boost::edge_weight_t, int> // edge property (interior)
> graph;

typedef boost::adjacency_list<boost::vecS,
boost::vecS,
boost::undirectedS> undirected_graph;

typedef boost::graph_traits<undirected_graph>::vertex_descriptor vertex_desc;

int maximum_matching(const undirected_graph &G) {
int n = boost::num_vertices(G);
std::vector<vertex_desc> mate_map(n); // exterior property map
boost::edmonds_maximum_cardinality_matching(G,
boost::make_iterator_property_map(mate_map.begin(),
boost::get(boost::vertex_index, G)));
int matching_size = boost::matching_size(G,
boost::make_iterator_property_map(mate_map.begin(),
boost::get(boost::vertex_index, G)));
return matching_size; }


vector<int> dijkstra_dist(const graph &G, int s) {
int n = boost::num_vertices(G);
std::vector<int> dist_map(n); //exterior property
boost::dijkstra_shortest_paths(G, s,
boost::distance_map(boost::make_iterator_property_map(dist_map.begin(),
boost::get(boost::vertex_index, G))));
return dist_map;
}


void solve(){
  //cout << "***********************\n";
  int n, m, b, p, d; cin >> n >> m >> b >> p >> d;
  
  vector<int> barracks(b);
  for(int i=0; i<b; i++){
    int bi; cin >> bi;
    barracks[i] = bi;
  }
  
  vector<bool> isPlaza(n);
  for(int i=0; i<p; i++){
    int pi; cin >> pi;
    isPlaza[pi] = true;
  }
  
  graph G1(n);
  vector<vector<int>> neighbors(n);
  for(int i=0; i<m; i++){
    int x, y, l; cin >> x >> y >> l;
    boost::add_edge(x, y, l, G1); boost::add_edge(y, x, l, G1);
    neighbors[x].push_back(y);
    neighbors[y].push_back(x);
  }
  
  vector<bool> isReachable(n, false);
  for(int i=0; i<b; i++){
    vector<int> dist_map = dijkstra_dist(G1, barracks[i]);
    for(int j=0; j<n; j++){
      if(dist_map[j] <= d){
        isReachable[j] = true;
      }
    }
  }
  
  undirected_graph G(2*n);
  for(int i=0; i<n; i++){
    if(isReachable[i]){
      for(int j : neighbors[i]){
        if(isReachable[j]){
        boost::add_edge(i, j, G);
        //cout << "add edge "  << i << " - " << j << "\n";   
        if(isPlaza[i]){
          boost::add_edge(i + 2*n, j, G);
          //cout << "add edge "  << i+2*n << " - " << j << "\n";        
        }
        if(isPlaza[j]){
          boost::add_edge(i, j+2*n, G);
          //cout << "add edge "  << i << " - " << j+2*n << "\n"; 
        }
        }
      }
    }
  }
  
  cout << maximum_matching(G) << "\n";
}

signed main(){
  int t; cin >> t;
  while(t--){
    solve();
  }
  return 0;
}