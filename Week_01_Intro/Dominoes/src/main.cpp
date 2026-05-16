#include <stack>
#include <queue>
#include <iostream>
#include <vector>
using namespace std;

void solve(){
  int n;
  cin >> n;
  vector<int> dominoes(n);
  for(int i=0; i<n; i++){ cin >> dominoes[i]; }
    queue<int> s;
    s.push(0);
    int count = 0;
    vector<bool> toppled(n);
    toppled[0] = true;
    int current;
    int currentHeight;
    while(!s.empty()){
      current = s.front();
      currentHeight = dominoes[current];
      //cout << "currently inspecting domino " << current << " with height " << currentHeight << "\n";
      s.pop();
      for(int i=1; i<=currentHeight && current+i<n; i++){
        if(!toppled[current + i]){
        s.push(current + i);
        toppled[current + i] = true;
        count++;
        //cout << "toppled domino " << current +i << ", count: " << count << "\n";
        }
      }
    }
    cout << count << "\n";
    //cout << "-------------------------------------" << "\n";
}

void solveLinear(){
  int n;
  cin >> n;
  vector<int> h(n);
  for(int i=0; i<n; i++){ cin >> h[i]; }
  int max_reach = h[0]-1;
  for(int i=0; i<n; i++){
    if(i<=max_reach){
      max_reach = max(max_reach, i+h[i]-1);
    }
  }
  cout << min(max_reach+1, n) << "\n";
}
  
  

int main(){
  std::ios_base::sync_with_stdio(false);
  int t;
  cin >> t;
  for(int i=0; i<t; i++){
    solveLinear();
  }
  return 0;
}