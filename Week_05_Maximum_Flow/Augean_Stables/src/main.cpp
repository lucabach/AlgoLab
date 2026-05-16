#include <iostream>
#include <vector>
#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpz.h>

#define int long

typedef int IT;
typedef double ET;
typedef CGAL::Quadratic_program<IT> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;

using namespace std;


bool is_this_feasible(const vector<vector<int>> &A, const vector<int> &B, int a, int p){
  int n = (int) B.size();
  int a2 = a*a;
  int p2 = p*p;
  int ap = a*p;
  Program lp (CGAL::SMALLER, true, 0, false, 0); 
  
  const int ONE = 0; const int h1 = 1; const int h2 = 2; const int h3 = 3;
  lp.set_l(ONE, true, 1); lp.set_u(ONE, true, 1);
  lp.set_l(h1, true, 0); lp.set_u(h1, true, 1);
  lp.set_l(h2, true, 0); lp.set_u(h2, true, 1);
  lp.set_l(h3, true, 0); lp.set_u(h3, true, 1);
  
  for(int i=0; i<n; i++){
    lp.set_a(ONE, i, A[i][0]); lp.set_a(h1, i, A[i][1]-a2); lp.set_a(h2, i, A[i][2] - p2); lp.set_a(h3, i, A[i][3]-ap);
    lp.set_b(i, B[i]);
  }
  
  Solution s = CGAL::solve_linear_program(lp, ET());
  if(s.is_infeasible()){ return false; } else { return true; }
}


void solve(){
  int n; cin >> n;
  
  vector<vector<int>> A(n, vector<int>(4));
  vector<int> B(n);
  for(int i=0; i<n; i++){
    int f, c, k, l, m; cin >> f >> c >> k >> l >> m;
    A[i] = {f, -k, -l, -m};
    B[i] = c;
  }
  
  vector<int> psumA(25, 0);
  for(int i=1; i<=24; i++){
    int x; cin >> x;
    psumA[i] = psumA[i-1] + x;
  }
  
  vector<int> psumP(25, 0);
  for(int i=1; i<=24; i++){
    int x; cin >> x;
    psumP[i] = psumP[i-1] + x;
  }
  
  if(!is_this_feasible(A, B, psumA[24], psumP[24])){
    cout << "Impossible!\n";
    return;
  }
  
  int start = 0; int end = 48;
  int min_hours = 48;
  while(start <= end){
    bool feasible = false;
    int mid = (start+end)/2;
    for(int countA=0; countA<=mid; countA++){
      int countP = mid - countA;
      if(countA > 24 || countP > 24){ continue; }
      feasible = is_this_feasible(A, B, psumA[countA], psumP[countP]);
      if(feasible){ break; }
    }
    if(feasible){
      min_hours = min(min_hours, mid);
      end = mid - 1;
    }
    else {
      start = mid + 1;
    }
  }
  
  cout << min_hours << "\n";
}
 
 signed main(){
   int t; cin >> t;
   while(t--){
     solve();
   }
   return 0;
 }