#include <limits>
#include <vector>
#include <iostream>
#include <algorithm>
#include <map>

using namespace std;

void solve(){
  int n, k, w; cin >> n >> k >> w;
  vector<int> cost(n);
  vector<vector<int>> wway(w);
  for(int i=0; i<n; i++){
    int c; cin >> c;
    cost[i] = c;
  }
  
  for(int i=0; i<w; i++){
    int l; cin >> l;
    for(int j=0; j<l; j++){
      int wcur; cin >> wcur;
      wway[i].push_back(wcur);
    }
  }
  
  int spikeCost = cost[0];
  vector<vector<int>> cumSum(w);
  vector<vector<int>> cumSumSpike(w);
  for(int i=0; i<w; i++){
    int curSize = (int)wway[i].size();
    cumSum[i] = vector<int>(curSize);
    cumSumSpike[i] = vector<int>(curSize+1);
    if(curSize>=1){
    cumSum[i][0] = 0;
    cumSumSpike[i][0] = 0;
    //cout << "cumSumSpike " << i << ": ";
    //cout << cumSumSpike[i][0] << " ";
    for(int j=1; j<=curSize; j++){
      if(j<curSize){
      cumSum[i][j] = cumSum[i][j-1] + cost[wway[i][j]];
      }
      cumSumSpike[i][j] = cumSumSpike[i][j-1] + cost[wway[i][j-1]];
      //cout << cumSumSpike[i][j] << " ";
    }
    //cout << "\n";
  }
  }
  
    cout << "*********************************\n";
    vector<pair<int, int>> minMen(k, {numeric_limits<int>::max(), -1});
    int maxIslandSimple = 0;
    for(int i=0; i<w; i++){
      int curSum = 0;
      int windowStart = 0;
      int windowEnd = 0;
      int curSize = (int)wway[i].size();
      cout << "Inspecting wway " << i << "\n";
      while(windowEnd <= curSize + 1){
        cout << "windowStart: " << windowStart << ", windowEnd: " << windowEnd << ", curSum: " << curSum << "\n";
        int windowSize = windowEnd - windowStart;
        curSum = cumSumSpike[i][windowEnd] - cumSumSpike[i][windowStart];
        if(curSum == k){
          maxIslandSimple = max(maxIslandSimple, windowSize);
          cout << "Found sum. Possible Islands conquered:  " << windowSize << "\n";
          windowStart++;
        }
        else if(curSum < k) {
          windowEnd++;
        }
        else {
          windowStart++;
        }
        if(windowStart > windowEnd){
          swap(windowStart, windowEnd);
        }
        if(minMen[curSum].first < windowSize)
          minMen[curSum] = {windowSize, i};
          cout << "We can conquer  " << windowSize << " islands using only " << curSum << " men\n";
        }
      }
  
  cout << "-------------------------------------\n";
  int maxIslands = 0;
  for(int i = 0; i<w; i++){
      int curSum = 0;
      int curSize = (int)wway[i].size();
      cout << "Inspecting wway " << i << "\n";
      for(int j=0; j<curSize; j++){
        curSum = cumSum[i][j] + spikeCost;
        if(curSum >= k){ break; }
        int menNeeded = k - curSum;
        auto maxp = minMen[menNeeded];
        if(maxp.second == i){ continue; }
        cout << "Found sum. Possible Islands conquered:  " << curSum + maxp.first << "\n";
        maxIslands = max(maxIslands, curSum + maxp.first);
      }
  }
  cout << "RES: " << max(maxIslands, maxIslandSimple) << "\n";
  return;
}
  

int main(){
  std::ios_base::sync_with_stdio(false);
  int t;
  cin >> t;
  for(int i=0; i<t; i++){
    solve();
  }
  return 0;
}