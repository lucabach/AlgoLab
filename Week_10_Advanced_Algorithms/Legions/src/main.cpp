///2
#include <iostream>
#include <vector>
#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpz.h>

#define int long
// choose input type (input coefficients must fit)
typedef int IT;
// choose exact type for solver (CGAL::Gmpz or CGAL::Gmpq)
typedef CGAL::Gmpz ET;
typedef CGAL::Quadratic_program<IT> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;

using namespace std;


void solve(){
  int xs, ys, n; cin >> xs >> ys >> n;
  Program lp (CGAL::SMALLER, false, 0, false, 0); 
  const int X = 0;
  const int Y = 1;
  const int D = 2;
  
  lp.set_l(D, true, 0);
  lp.set_c(D, -1);
  
  for(int i=0; i<n; i++){
    int a, b, c, v; cin >> a >> b >> c >> v;
    int V = sqrt(a*a + b*b)*v;
    if(a*xs + b*ys <= -c){
      lp.set_a(X, i, a);
      lp.set_a(Y, i, b);
      lp.set_a(D, i, V); 
      lp.set_b(i, -c);
    }
    else {
      lp.set_a(X, i, -a);
      lp.set_a(Y, i, -b); 
      lp.set_a(D, i, V);
      lp.set_b(i, c);
    }
  }
  
   Solution sol = CGAL::solve_linear_program(lp, ET());
   cout << (int) -CGAL::to_double(sol.objective_value()) << "\n";
}

signed main(){
  ios_base::sync_with_stdio(false);
  int t; cin >> t;
  while(t--){ solve(); }
  return 0;
}