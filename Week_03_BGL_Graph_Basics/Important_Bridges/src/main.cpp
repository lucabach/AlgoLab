#include <boost/graph/biconnected_components.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <bits/stdc++.h>
#include <set>

using namespace std;


struct edge_component_t
{
    enum
    {
        num = 555
    };
    typedef boost::edge_property_tag kind;
} edge_component;


typedef boost::adjacency_list<boost::vecS,
boost::vecS,
boost::undirectedS,
boost::no_property,
boost::property< edge_component_t, std::size_t > > graph;
typedef boost::graph_traits<graph>::edge_descriptor edge_desc;
typedef boost::graph_traits<graph>::vertex_descriptor vertex_desc;
typedef pair<int, int> PII;

struct Lexico {
bool operator() (const PII& p1, const PII& p2) const {
return p1.first < p2.first || (p1.first == p2.first && p1.second < p2.second);
}
};


pair<boost::property_map<graph, edge_component_t >::type, int> biconnected_comp(graph &G) {
boost::property_map<graph, edge_component_t >::type component = boost::get(edge_component, G);
int num_comps = (int) biconnected_components(G, component);
return {component, num_comps};
}

void solve(){
  int n, m; cin >> n >> m;
  
  graph G(n);
  for(int i=0; i<m; i++){
    int e1, e2; cin >> e1 >> e2;
    boost::add_edge(e1, e2, G);
  }
  
  auto elem = biconnected_comp(G);
  auto compmap = elem.first;
  int num_comp = elem.second;
  
  vector<int> compcount(num_comp, 0);
  
  boost::graph_traits< graph >::edge_iterator ei, ei_end;
  for (boost::tie(ei, ei_end) = edges(G); ei != ei_end; ++ei){
          compcount[compmap[*ei]]++;
  }
  
  set<int> critical_components;
  for(int i=0; i<num_comp; i++){
    if(compcount[i] == 1){
      critical_components.insert(i);
    }
  }
  
  vector<pair<int, int>> criticalBridges;
  for(boost::tie(ei, ei_end) = edges(G); ei != ei_end; ++ei){
        int u = boost::source(*ei, G);
        int v = boost::target(*ei, G);
        int comp = compmap[*ei];
        if(critical_components.find(comp) != critical_components.end()){
          criticalBridges.emplace_back(u, v);
        }
  }
  
  for(int i=0; i<(int) criticalBridges.size(); i++){
    if(criticalBridges[i].second < criticalBridges[i].first){
      int temp = criticalBridges[i].second;
      criticalBridges[i].second = criticalBridges[i].first;
      criticalBridges[i].first = temp;
    }
  }
  sort(criticalBridges.begin(), criticalBridges.end(), Lexico());
  int cSize = (int)criticalBridges.size();
  cout << cSize << "\n";
  for(int i=0; i<cSize; i++){
    cout << criticalBridges[i].first << " " << criticalBridges[i].second << "\n";
  }
}



int main(){
  int t;
  cin >> t;
  while(t--){
    solve();
  }
}