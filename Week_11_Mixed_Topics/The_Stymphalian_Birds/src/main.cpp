
#include <iostream>
#include <vector>
#include <utility>
#include <cmath>
#include <queue>

using namespace std;

vector<bool> killed;
int N;

int kill(const int &idx){
  if(idx >= N || killed[idx]){
    return 0;
  }
  else{
    killed[idx] = true;
    //cout << "killed bird " << idx << "\n";
    return 1 + kill(2*idx+1) + kill(2*idx+2);
  }
}

void solve(){
  int n; cin >> n;
  N = n;
  
  killed.clear();
  killed.resize(n, false);
  priority_queue<pair<int, int>> q;
  for(int i=0; i<n; i++){
    int t; cin >> t;
    q.emplace(-t, i);
  }
  
  int curTime = 0;
  bool dead = false;
  
  while(!q.empty()){
    auto curElem = q.top(); q.pop();
    int killTime = -curElem.first;
    int idx = curElem.second;
    //cout << "curtarget: " << idx << " killTime: " << killTime <<"\n";
    if(killed[idx]){
      continue;
    }
    if(killTime <= curTime){
      dead = true; break;
    }
    int birdskilled = kill(idx);
    curTime += birdskilled;
    //cout << "killed " << birdskilled << " birds. " << "curTime is now " << curTime << "\n";
    if(killTime < curTime){
      dead=true; break;
    }
  }
  
  if(dead){
    cout << "no\n";
  }
  else{
    cout << "yes\n";
  }
}

signed main(){
  int t; cin >> t;
  while(t--){
    solve();
  }
  return 0;
}