#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void solve() {
  int n, m; 
  cin >> n >> m;

  vector<int> strength(n);
  for (int i = 0; i < n; i++) cin >> strength[i];

  vector<int> weight(m);
  for (int i = 0; i < m; i++) cin >> weight[i];


  sort(weight.begin(), weight.end(), greater<>());
  sort(strength.begin(), strength.end(), greater<>());

  if(weight[0]>strength[0]){
    cout << "impossible" << "\n";
    return;
  }
  
  int low = (m-1)/n;
  int high = m;
  while(low<=high){
    int mid = (low+high)/2;
    int friends = (m-1)/mid + 1;
    bool can_carry = true;
    for(int i=0; i<friends; i++){
      if(strength[i]<weight[i*mid]){
        can_carry = false;
        break;
      }
    }
    if(can_carry){
      high = mid-1;
    }
    else{
      low = mid+1;
    }
  }
  cout << (low*3) -1 << "\n";
  return;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int t; 
  cin >> t;
  while (t--) solve();
  return 0;
}
