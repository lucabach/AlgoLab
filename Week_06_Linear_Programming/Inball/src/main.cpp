///
#include <iostream>
#include <vector>
#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpz.h>

typedef int IT;
typedef CGAL::Gmpz ET;
typedef CGAL::Quadratic_program<IT> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;

using namespace std;

int round_down(const CGAL::Quotient<ET> &x){
  int x1 = floor(CGAL::to_double(x));
  while((ET) x1 > x){ x1-=1;}
  while((ET) x1 + 1 <= x){ x1+=1;}
  return x1;
}

void solve(int n, int d){
  // create an LP with Ax <= b, lower bound 0 and no upper bounds
 Program lp (CGAL::SMALLER, false, 0, false, 0);

 const int R = d;
 lp.set_l(R, true, 0);
 lp.set_c(R, -1);
 
 for(int i=0; i<n; i++){
   int norm = 0;
   for(int j=0; j<d; j++){
     int ai; cin >> ai;
     lp.set_a(j, i, ai);
     norm += (ai * ai);
   }
   
   norm = sqrt(norm);
   lp.set_a(R, i, norm);
   
   int bi; cin >> bi;
   lp.set_b(i, bi);
 }
  
  Solution sol = CGAL::solve_linear_program(lp, ET());
  
  if(sol.is_infeasible()){ cout << "none\n"; return;}
  if(sol.is_unbounded()){ cout << "inf\n"; return;}
  cout << (int)(-CGAL::to_double(sol.objective_value())) << "\n";
}

signed main(){
  ios_base::sync_with_stdio(false);
  int n;
  while(true){
    cin >> n;
    if(n == 0){ break;}
    int d; cin >> d;
    solve(n, d);
  }
  return 0;
}