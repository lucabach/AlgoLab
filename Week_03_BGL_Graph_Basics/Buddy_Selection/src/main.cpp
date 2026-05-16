#include <boost/graph/max_cardinality_matching.hpp>
#include <iostream>
#include <vector>
#include <boost/graph/adjacency_list.hpp>
#include <unordered_map>
#include <string>
#include <algorithm>

typedef boost::adjacency_list<boost::vecS,
boost::vecS,
boost::undirectedS> graph;
typedef boost::graph_traits<graph>::vertex_descriptor vertex_desc;

using namespace std;


int maximum_matching(const graph &G) {
int n = boost::num_vertices(G);
std::vector<vertex_desc> mate_map(n); // exterior property map
//const vertex_desc NULL_VERTEX = boost::graph_traits<graph>::null_vertex();
boost::edmonds_maximum_cardinality_matching(G,
boost::make_iterator_property_map(mate_map.begin(),
boost::get(boost::vertex_index, G)));
int matching_size = boost::matching_size(G,
boost::make_iterator_property_map(mate_map.begin(),
boost::get(boost::vertex_index, G)));
return matching_size;
}



void solve(){
  int n, c, f; cin >> n >> c >> f;
  unordered_map<string, int> charToNum;
  
  graph G(n);
  vector<vector<int>> characteristics(n, vector<int>(c));
  int charcount = 1;
  for(int i=0; i<n; i++){
    for(int j=0; j<c; j++){
      string s; cin >> s;
      int x = charToNum[s];
      if(x == 0){
        x = charcount++;
        charToNum[s] = x;
      }
      characteristics[i][j] = x;
    }
  }
  
  for(int i=0; i<n; i++){
    sort(characteristics[i].begin(), characteristics[i].end());
  }
  
  for(int i=0; i<n; i++){
    for(int j=i; j<n; j++){
      int idxi=0; int idxj=0; int common = 0;
      while(idxi<c && idxj<c){
        if(characteristics[i][idxi] == characteristics[j][idxj]){
          common++;
          if(common > f){
            boost::add_edge(i, j, G);
            break;
          }
          idxi++;
          continue;
        }
        else if(characteristics[i][idxi] < characteristics[j][idxj]){
          idxi++;
        }
        else{
          idxj++;
        }
      }
    }
  }
  
 int mm = maximum_matching(G);
 if(mm == n/2){
   cout << "not optimal\n";
 }
 else{
   cout << "optimal\n";
 }
}
 
int main(){
  int t;
  cin >> t;
  while(t--){
    solve();
  }
}