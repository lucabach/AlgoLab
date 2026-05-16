#include <iostream>
#include <vector>

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <boost/graph/kruskal_min_spanning_tree.hpp>

using namespace std;

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS, 
                              boost::no_property, boost::property<boost::edge_weight_t, int>> graph;

typedef boost::graph_traits<graph>::edge_descriptor edge_desc;

vector<edge_desc> kruskal(const graph &G){
  vector<edge_desc> mst;
  
  boost::kruskal_minimum_spanning_tree(G, back_inserter(mst));
  return mst;
}

vector<int> dijkstra_dist(const graph &G, int s){
  int n = boost::num_vertices(G);
  vector<int> dist_map(n);
  
  boost::dijkstra_shortest_paths(G, s, boost::distance_map(boost::make_iterator_property_map(dist_map.begin(), boost::get(boost::vertex_index, G))));
  
  return dist_map;
}





void solve(){
  int n, m;
  cin >> n >> m;
  graph G(n);
  for(int i=0; i<m; i++){
    int u,v, c;
    cin >> u >> v >> c;
    boost::add_edge(u, v, c, G);
  }
  vector<int> dist_map = dijkstra_dist(G, 0);
  int maxdist = *max_element(begin(dist_map), end(dist_map));
  vector<edge_desc> mst = kruskal(G);
  int weight = 0;
  for(edge_desc edge : mst){
    weight += get(boost::edge_weight_t(), G, edge);
  }
  cout << weight << " " << maxdist << "\n";
}

int main(){
  int t;
  cin >> t;
  while(t--){
    solve();
  }
}