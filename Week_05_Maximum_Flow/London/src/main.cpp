#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <utility>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>

using namespace std;

//#define int long long

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
  //cout << "----------------------\n";
  int h, w; cin >> h >> w;
  vector<char> alphabet = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
  
  array<int, 26> demand = {};
  array<array<int, 1000>, 1000> part1 = {};
  array<array<int, 1000>, 1000> part2 = {};
  unordered_map<char, int> alphabetmap;
  
  for(int i=1; i <= (int)alphabet.size(); i++){
    alphabetmap[alphabet[i-1]] = i;
  }
  
  string message; cin >> message;
  for(int i=0; i<(int)message.size(); i++){
    demand[alphabetmap[message[i]]-1]++;
  }
  

  for(int i=0; i<h; i++){
    for(int j=0; j<w; j++){
      char curCar; cin >> curCar;
      part1[i][j] = alphabetmap[curCar] - 1;
      //cout << "part1ij = " << alphabetmap[curCar] << "\n";
    }
  }
  
  for(int i=0; i<h; i++){
    for(int j=w-1; j>=0; j--){
      char curCar; cin >> curCar;
      part2[i][j] = alphabetmap[curCar] - 1;
      //cout << "part2ij = " << alphabetmap[curCar] << "\n";
    }
  }
  
  graph G(26*26 + 26);
  edge_adder adder(G);
  vertex_desc v_source = boost::add_vertex(G);
  vertex_desc v_sink = boost::add_vertex(G);
  
  auto capacity = boost::get(boost::edge_capacity, G);
  for(int i=0; i<h; i++){
    for(int j=0; j<w; j++){
      int cur1 = part1[i][j];
      int cur2 = part2[i][j];
      auto sourceEdge = boost::edge(v_source, cur1*26 + cur2, G);
      if(sourceEdge.second){
        capacity[sourceEdge.first]++;
      } else{ adder.add_edge(v_source, cur1*26 + cur2, 1);}
      auto midEdge1 = boost::edge(cur1*26 + cur2, 26*26 + cur1, G);
      if(midEdge1.second){
        capacity[midEdge1.first]++;
      } else{ adder.add_edge(cur1*26 + cur2, 26*26 + cur1, 1);}
      auto midEdge2 = boost::edge(cur1*26 + cur2, 26*26 + cur2, G);
      if(midEdge2.second){
        capacity[midEdge2.first]++;
      } else{ adder.add_edge(cur1*26 + cur2, 26*26 +cur2, 1);}
      //cout << "Added edge source - " << cur1*cur2 << "\n";
      //cout << "Added edge " << cur1*cur2 << " - " << 26*26+cur1 <<  "\n";
      //cout << "Added edge " << cur1*cur2 << " - " << 26*26+cur2 <<  "\n";
    }
  }
  
  for(int i=0; i<26; i++){
    adder.add_edge(26*26 + i, v_sink, demand[i]);
    //cout << "Added edge " << 26*26+i << " to sink with cap " << demand[i-1] << "\n";
  }
  
  long flow = boost::push_relabel_max_flow(G, v_source, v_sink);
  if(flow == (long)message.size()){
    cout << "Yes\n";
  }
  else{
    cout << "No\n";
  }
}


signed main(){
  std::ios_base::sync_with_stdio(false);
  int t; cin >> t;
  while(t--){
    solve();
  }
  return 0;
}