#include <iostream>
#include <vector>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/max_cardinality_matching.hpp>

using namespace std;

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS> graph;
typedef boost::graph_traits<graph>::vertex_descriptor vertex_desc;
typedef boost::graph_traits<graph>::edge_iterator edge_it;
typedef boost::graph_traits<graph>::out_edge_iterator out_edge_it;



bool perfect_matching(const graph &G, const int &x) {
  
int n = boost::num_vertices(G);
std::vector<vertex_desc> mate_map(n); // exterior property map
boost::edmonds_maximum_cardinality_matching(G,
boost::make_iterator_property_map(mate_map.begin(),
boost::get(boost::vertex_index, G)));
int matching_size = boost::matching_size(G,
boost::make_iterator_property_map(mate_map.begin(),
boost::get(boost::vertex_index, G)));
//cout << "Matching size: " << matching_size << "\n";
if((n-x)%2 == 1){return false;}
if(matching_size == (n-x)/2){ return true; }
return false;
}


void solve(){
  int w, h;
  cin >> w >> h;
  vector<vector<bool>> tiles(h, vector<bool>(w));
  int count_x = 0;
  
  for(int i=0; i<h; i++){
    for(int j=0; j<w; j++){
      char c; cin >> c;
      if(c == '.'){
        tiles[i][j] = true;
      }
      else{
        tiles[i][j] = false;
        count_x ++;
      }
    }
  }
  
  graph G(w*h);

for (int i = 0; i < h; i++) {
    for (int j = 0; j < w; j++) {

        if (!tiles[i][j]) continue;

        int u = j + w * i;          // current vertex

        // Up: (i-1, j)
        if (i > 0 && tiles[i-1][j]) {
            int v = j + w * (i-1);
            boost::add_edge(u, v, G);
        }

        // Down: (i+1, j)
        if (i + 1 < h && tiles[i+1][j]) {
            int v = j + w * (i+1);
            boost::add_edge(u, v, G);
        }

        // Left: (i, j-1)
        if (j > 0 && tiles[i][j-1]) {
            int v = (j-1) + w * i;
            boost::add_edge(u, v, G);
        }

        // Right: (i, j+1)
        if (j + 1 < w && tiles[i][j+1]) {
            int v = (j+1) + w * i;
            boost::add_edge(u, v, G);
        }

    }
}

out_edge_it oe_beg, oe_end;

for (int u = 0; u < w*h; u++) {
    //cout << "Neighbors of " << u << ": ";
    for (boost::tie(oe_beg, oe_end) = boost::out_edges(u, G);
         oe_beg != oe_end; ++oe_beg)
    {
        //cout << boost::target(*oe_beg, G) << " ";
    }
    //cout << "\n";
}


  
  if(perfect_matching(G, count_x)){
    cout << "yes" << "\n";
  }
  else{
    cout << "no" << "\n";
  }
  return;
}

signed main(){
  int t; cin >> t;
  while(t--){
    solve();
  }
}