#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <utility>

using namespace std;

void solve(){
  int n; cin >> n;
  vector<int> length(n);
  vector<vector<int>> wordPosition(n);
  for(int i=0; i<n; i++){
    int l; cin >> l;
    length[i] = l;
    wordPosition[i] = vector<int>(l);
  }
  
  for(int i=0; i<n; i++){
    for(int j=0; j<length[i]; j++){
      int x; cin >> x;
      wordPosition[i][j] = x;
    }
  }
  
  priority_queue<pair<int, int>> curMin;
  int curMax = -1;
  
  //cout << "**********************************\n";
  for(int i=0; i<n; i++){
    curMin.emplace(-wordPosition[i][0], i);
    //cout << "added (" << wordPosition[i][0] << ", " << i << ")" << " to curMin \n";
    curMax = max(curMax, wordPosition[i][0]);
  }
  //cout << "curMax: " << curMax << "\n";
  int minLength = numeric_limits<int>::max();
  pair<int, int> mini;
  int minNum, minIdx;
  vector<int> popped;
  int newLength;
  int emptyMin = numeric_limits<int>::max();
  
  //cout << ".......................................\n";
  while(!curMin.empty()){
    mini = curMin.top();
    minNum = min(-mini.first, emptyMin);
    minIdx = mini.second;
    newLength = curMax - minNum + 1;
    minLength = min(minLength, newLength);
    //cout << "minLength: " << minLength << ", curMax: " << curMax << ", minNum: " << minNum << "\n";
    curMin.pop();
    //cout << "Popped (" << mini. first << ", " << mini.second << ")\n";
    wordPosition[minIdx].erase(wordPosition[minIdx].begin());
    if(wordPosition[minIdx].empty()){
      emptyMin = min(emptyMin, -mini.first);
      //cout << "NEW empty min = " << emptyMin << "\n";
      continue;
    }
    else{
    curMin.emplace(-wordPosition[minIdx][0], mini.second);
    //cout << "Pushed (" << wordPosition[minIdx][0] << ", " << mini.second << ")\n";
    }
    curMax = max(curMax, wordPosition[minIdx][0]);
  }
  
  cout << minLength << "\n";
}

signed main(){
  ios_base::sync_with_stdio(false);
  int t; cin >> t;
  while(t--){
    solve();
  }
  return 0;
}