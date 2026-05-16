#include <iostream>
#include <vector>
using namespace std;

void solveQuadratic(){
  int n;
  cin >> n;
  vector<vector<int>> m(n, vector<int>(n));
  
  for(int i=0; i<n; i++){
    for(int j=0; j<n; j++){
      cin >> m[i][j];
    }
  }
  
  vector<vector<int>> psum(n, vector<int>(n));
  psum[0][0] = m[0][0];
  for(int i=0; i<n; i++){
    for(int j=0; j<n; j++){
      if(i==0 && j==0){
        continue;
      }
      else if(i==0 && j != 0){
        psum[i][j] = psum[i][j-1] + m[i][j];
      }
      else if(j==0 && i !=0){
        psum[i][j] = psum[i-1][j] + m[i][j];
      }
      else{
        psum[i][j] = psum[i][j-1] + psum[i-1][j] - psum[i-1][j-1] + m[i][j];
      }
    }
  }
  
  
  int evensums = 0;
  int prefixsum = 0;
  for(int startx = 0; startx<n; startx++){
    for(int starty = 0; starty<n; starty++){
      for(int endx = startx; endx<n; endx++){
        for(int endy = starty; endy<n; endy++){
          if(startx == 0 && starty == 0){
            prefixsum = psum[endx][endy];
          }
          else if(startx == 0){
            prefixsum = psum[endx][endy] - psum[endx][starty-1];
          }
          else if(starty == 0){
            prefixsum = psum[endx][endy] - psum[startx-1][endy];
          }
          else{
            prefixsum = psum[endx][endy] - psum[endx][starty-1] - psum[startx-1][endy] + psum[startx-1][starty-1];
          }
          if(prefixsum % 2 == 0){
            evensums++;
          }
        }
      }
    }
  }
  cout << evensums << "\n";
}



void solveCubic(){
  int n;
  cin >> n;
  vector<vector<int>> m(n, vector<int>(n));
  
  for(int i=0; i<n; i++){
    for(int j=0; j<n; j++){
      cin >> m[i][j];
    }
  }
  
  vector<vector<int>> psum(n, vector<int>(n));
  psum[0][0] = m[0][0];
  for(int i=0; i<n; i++){
    for(int j=0; j<n; j++){
      if(i==0 && j==0){
        continue;
      }
      else if(i==0 && j != 0){
        psum[i][j] = psum[i][j-1] + m[i][j];
      }
      else if(j==0 && i !=0){
        psum[i][j] = psum[i-1][j] + m[i][j];
      }
      else{
        psum[i][j] = psum[i][j-1] + psum[i-1][j] - psum[i-1][j-1] + m[i][j];
      }
    }
  }
  
  int evenSums = 0;
  for(int startx=0; startx<n; startx++){
    for(int endx=startx; endx<n; endx++){
      int odd = 0;
      int even = 0;
      for(int endy=0; endy<n; endy++){
        int currentSliceSum;
        if(startx == 0){
          currentSliceSum = psum[endx][endy];
        }
        else{
          currentSliceSum = psum[endx][endy] - psum[startx-1][endy];
        }
        if(currentSliceSum % 2 == 0){
          even++;
        }
        else{
          odd++;
        }
      }
      evenSums += (even * (even-1))/2 + (odd * (odd -1))/2 + even;
    }
  }
  cout << evenSums << "\n";
}


int main(){
  std::ios_base::sync_with_stdio(false);
  int t;
  cin >> t;
  for(int i=0; i<t; i++){
    solveCubic();
  }
  return 0;
}