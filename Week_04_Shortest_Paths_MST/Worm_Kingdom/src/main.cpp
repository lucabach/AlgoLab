///3
#include <iostream>
#include <vector>
#include <limits>
#include <utility>
#include <limits>
#include<queue>

#define int long

using namespace std;


vector<vector<vector<int>>> children;
vector<vector<int>> size;
vector<vector<int>> sumTree;

int bfs(const int &k, const int &x){
  
  if(children[k][x].empty()){
    sumTree[k][x] = size[k][x];
    //cout << "node " << x << ": " << sumTree[k][x] << "\n";
    return size[k][x];
  }
  
  int accumulatedSize = size[k][x];
  for(int child : children[k][x]){
      accumulatedSize += bfs(k, child);
  }
  sumTree[k][x] = accumulatedSize;
  //cout << "node " << x << ": " << sumTree[k][x] << "\n";
  return accumulatedSize;
}

int bfs2(const int &k, const int &x, const int & total, int min_diff){
  
  int local_min_diff = numeric_limits<int>::max();
  for(int child : children[k][x]){
      int inter_diff = total - sumTree[k][child];
      local_min_diff = min(local_min_diff, abs(sumTree[k][child]-inter_diff));
  }
  
  min_diff = min(min_diff, local_min_diff);
  for(int child : children[k][x]){
      min_diff = min(min_diff, bfs2(k, child, total, min_diff));
  }
  
  return min_diff;
}

vector<bool> compute_dp0(const vector<int>& burrow_sum) {
    int k = burrow_sum.size();

    int S = 0;
    for (int b : burrow_sum) S += b;

    vector<bool> dp0(S + 1, false);
    dp0[0] = true;

    for (int i = 0; i < k; i++) {
        int Bi = burrow_sum[i];
        for (int x = S; x >= Bi; x--) {
            dp0[x] = dp0[x] || dp0[x - Bi];
        }
    }

    return dp0;
}

void solve(){
  int k, p; cin >> k >> p;
  children.clear();
  size.clear();
  sumTree.clear();
  children.resize(k);
  size.resize(k);
  sumTree.resize(k);
  vector<int> sumBurrow(k);
  vector<bool> isLeaf;
  
  int S = 0;
  for(int i=0; i<k; i++){
    int ni; cin >> ni;
    if(i==0){
      isLeaf.resize(ni, true);
    }
    children[i] = vector<vector<int>>(ni);
    for(int j=0; j<ni-1; j++){
      int u, v; cin >> u >> v;
      children[i][u].push_back(v);
      isLeaf[u] = false;
    }
    size[i] = vector<int>(ni);
    sumTree[i] = vector<int>(ni);
    int curSum = 0;
    for(int j=0; j<ni; j++){
      int s; cin >> s;
      size[i][j] = s;
      curSum+=s;
    }
    sumBurrow[i] = curSum;
    S+=curSum;
  }
    
  if(k==1){
    int totalSum = sumBurrow[0];
    vector<bool> visited((int)children[0].size(), false);
    int borrowSum = bfs(0, 0);
    int min_diff = bfs2(0, 0, borrowSum, numeric_limits<int>::max());
    cout << min_diff << "\n";
    return;
  }
  
  for(int i=0; i<k; i++){
    int borrowSum = bfs(i, 0);
  }
  
  vector<bool> dp0 = compute_dp0(sumBurrow);

  
  // dp1[x] = true  <=>  there exists ONE subtree of size x
  vector<bool> dp1(S + 1, false);

  for (int i = 0; i < k; i++) {
    int ni = sumTree[i].size();
    // skip node 0 (root), because cutting above root isolates nothing
    for (int v = 1; v < ni; v++) {
      int T = sumTree[i][v];
      dp1[T] = true;
    }
  }

  int best_diff = numeric_limits<int>::max();

  // combine dp0 and dp1
  for (int x = 1; x < S; x++) {
    if (dp0[x] || dp1[x]) {
      best_diff = min(best_diff, labs(S - 2 * x));
    }
  }

  cout << best_diff + p * (k - 1) << "\n";
}


signed main(){
  ios_base::sync_with_stdio(false);
  int t; cin >> t;
  while(t--){
    solve();
  }
  return 0;
}