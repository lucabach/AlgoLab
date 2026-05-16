#include <boost/graph/kruskal_min_spanning_tree.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <vector>
#include <iostream>
#include <boost/graph/prim_minimum_spanning_tree.hpp>
#include <limits>
#include <stack>

#define int long

using namespace std;

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS,
boost::no_property,
boost::property<boost::edge_weight_t, int>
> weighted_graph;

typedef boost::graph_traits<weighted_graph>::edge_descriptor edge_desc;
typedef boost::graph_traits<weighted_graph>::vertex_descriptor vertex_desc;


vector<edge_desc> kruskal(const weighted_graph &G) {
std::vector<edge_desc> mst; // vector to store MST edges (not a property map!)
boost::kruskal_minimum_spanning_tree(G, std::back_inserter(mst));
return mst;
}


void solve(){
  int n, source; cin >> n >> source;
  weighted_graph G(n);
  
  std::vector<std::vector<int>> neighbors(n);
  vector<vector<bool>> used(n, vector<bool>(n));
  vector<vector<int>> costs(n, vector<int>(n));
  vector<vector<int>> longest_edge(n, vector<int>(n));

    
  for(int i=0; i<n-1; i++){
    for(int j=i+1; j<n; j++){
      int c; cin >> c;
      boost::add_edge(i, j, c, G);
      costs[i][j] = costs[j][i] = c;
    }
  }
  
  vector<edge_desc> mst = kruskal(G);
  auto c_map = boost::get(boost::edge_weight_t(), G);

  int opt_cost = 0;
  for(edge_desc e: mst){
    int u = boost::source(e, G);
    int v = boost::target(e, G);
    neighbors[u].push_back(v);
    neighbors[v].push_back(u);
    used[u][v] = used[v][u] = true;
    opt_cost += c_map[e];
  }
  
  
  for(int i=0; i<n; i++){
    vector<bool>visited(n);
    stack<tuple<int, int, int>> s;
    s.emplace(i, -1, 0); //curNode, neighbor_iter, longest edge
    
    while(!s.empty()){
      auto &[curNode, neighboridx, curMax] = s.top();
      neighboridx++;
      if(neighboridx == (int)neighbors[curNode].size()){
        s.pop();
        continue;
      }
      
      int curNeighbor = neighbors[curNode][neighboridx];
      if(visited[curNeighbor]){
        continue;
      }
      
      curMax = max(curMax, costs[curNode][curNeighbor]);
      longest_edge[i][curNeighbor] = longest_edge[curNeighbor][i] = curMax;
      visited[curNeighbor] = true;
      s.emplace(curNeighbor, -1, curMax);
    }
  }
  
  int min_diff = numeric_limits<int>::max();
  
  for(int i=0; i<n; i++){
    for(int j=i+1; j<n; j++){
      if(!used[i][j]){
        int curCost = costs[i][j];
        min_diff = min(min_diff, curCost - longest_edge[i][j]);
      }
    }
  }
  
  cout << opt_cost + min_diff << "\n";
}


signed main(){
  ios_base::sync_with_stdio(false);
  int t; cin >> t;
  while(t--){solve();}
  return 0;
}