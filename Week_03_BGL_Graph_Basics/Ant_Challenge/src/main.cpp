#include <iostream>
#include <vector>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/prim_minimum_spanning_tree.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>

using namespace std;

typedef boost::adjacency_list<
boost::vecS,
boost::vecS,
boost::undirectedS,
boost::no_property, // no vertex property
boost::property<boost::edge_weight_t, int> // edge property (interior)
> graph;
typedef boost::graph_traits<graph>::vertex_descriptor vertex_desc;
typedef boost::graph_traits<graph>::edge_descriptor edge_desc;


int dijkstra_dist(const graph &G, int s, int t) {
int n = boost::num_vertices(G);
std::vector<int> dist_map(n); //exterior property
boost::dijkstra_shortest_paths(G, s,
boost::distance_map(boost::make_iterator_property_map(dist_map.begin(),
boost::get(boost::vertex_index, G))));
return dist_map[t];
}


void solve(){
  int n, e, s, a, b; cin >> n >> e >> s >> a >> b;
  vector<graph> G(s, graph(n));
  for(int i=0; i<e; i++){
    int t1, t2; cin >> t1 >> t2;
    for(int j=0; j<s; j++){
      int w; cin >> w;
      boost::add_edge(t1, t2, w, G[j]);
      //cout << "added edge " <<t1 << " - " << t2 << "\n";
    }
  }
  
  
  vector<vector<vertex_desc>> p(s, vector<vertex_desc>(n));
    for(int i = 0; i < s; i++) {
    int hive; cin >> hive;

    prim_minimum_spanning_tree(
        G[i],
        boost::make_iterator_property_map(
            p[i].begin(),
            get(boost::vertex_index, G[i])
        ),
        boost::root_vertex(hive)
    );
}
  
  
  
  graph BIG_G(n);
  for(int i=0; i<s; i++){
    auto cost = boost::get(boost::edge_weight_t(), G[i]);
    graph curGraph = G[i];
    for(int j=0; j<n; j++){
      auto curEdge = boost::edge(j, p[i][j], curGraph);
      if(curEdge.second){
        int curCost = cost[curEdge.first];
        boost::add_edge(j, p[i][j], curCost, BIG_G);
      }
    }
  }
  cout << dijkstra_dist(BIG_G, a, b) << "\n";  
}


int main(){
  int t;
  cin >> t;
  while(t--){
    solve();
  }
}