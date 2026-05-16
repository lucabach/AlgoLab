#include <iostream>
#include <vector>
using namespace std;

int choose2(int x){
  return (x*(x-1))/2;
}

void solve(vector<int> bits, int n){
  int eps = 1;
  int sum = 0;
  for(int i=0; i<n; i++){
    sum += bits[i];
    if(sum % 2 == 0){
      eps++;
    }
  }
  int sol = choose2(eps) + choose2(n + 1 - eps);
  cout << sol;
  cout << endl;
}

int main(){
  int t;
  cin >> t;
  while(t>0){
    t--;
    int n;
    cin >> n;
    vector<int> bits(n);
    for(int i=0; i<n; i++){
      cin >> bits[i] ;
    }
    solve(bits, n);
  }
  return 0;
}