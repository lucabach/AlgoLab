#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <queue>
#include <algorithm>
#include <array>
#include <utility>

using namespace std;

array<string, 50000> name;
array<int, 50000> age;
unordered_map<string, int> nameToNum;
vector<vector<int>> children;
vector<vector<pair<int, int>>> query; //maxAge, queryIndex
array<int, 50000> result;
vector<pair<int, int>> age_stack;

int binary_search(int maxAge) {
    if (age_stack.empty()) return -1;

    int low = 0;
    int high = (int)age_stack.size() - 1; // Use inclusive bound
    int ans = -1;

    // Standard 'First occurrence' binary search logic
    while (low <= high) { // Use <= with high = size - 1
        int mid = (low + high) / 2;

        if (age_stack[mid].second <= maxAge) {
            ans = age_stack[mid].first; // This is a candidate
            high = mid - 1;             // Try to find an even older ancestor (lower index)
        } else {
            low = mid + 1;              // Too old, look for younger ones
        }
    }
    return ans;
}

void dfs(const int &idx){
  age_stack.emplace_back(idx, age[idx]);
  
  for(int i=0; i<(int) query[idx].size(); i++){
    pair<int, int> curQuery = query[idx][i];
    int res = binary_search(curQuery.first);
    result[curQuery.second] = res;
  }
  
  for(int c : children[idx]){
    dfs(c);
  }
  age_stack.pop_back();
}


void solve(){
  int n, q; cin >> n >> q;
  
  children.resize(n);
  query.resize(n);
  nameToNum.clear();
  age_stack.clear();
  
  int max_age_idx = 0;
  int max_age = -1;
  for(int i=0; i<n; i++){
    children[i].clear();
    query[i].clear();
    string s; int a; cin >> s >> a;
    name[i] = s;
    age[i] = a;
    nameToNum[s] = i;
    if(a > max_age){
      max_age = a;
      max_age_idx = i;
    }
  }
  
  for(int i=0; i<n-1; i++){
    string s, p; cin >> s >> p;
    children[nameToNum[p]].push_back(nameToNum[s]);
  }
  
  for(int i=0; i<q; i++){
    string s; int maxAge; cin >> s >> maxAge;
    query[nameToNum[s]].emplace_back(maxAge, i);
  }
  
  dfs(max_age_idx);
  
  for(int i=0; i<q; i++){
    cout << name[result[i]] << " ";
  }
  
  cout << "\n";
}


signed main(){
  int t; cin >> t;
  while(t--){
    solve();
  }
  return 0;
}

