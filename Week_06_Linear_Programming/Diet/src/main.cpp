#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpz.h>
#include <iostream>

// choose input type (input coefficients must fit)
typedef int IT;
// choose exact type for solver (CGAL::Gmpz or CGAL::Gmpq)
typedef CGAL::Gmpz ET;
// program and solution types
typedef CGAL::Quadratic_program<IT> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;

using namespace std;


int round_down(const CGAL::Quotient<ET> &x){
  double x1 = floor(CGAL::to_double(x));
  while(x1 > x){
    x1--;
  }
  while(x1 + 1 <= x){
    x1++;
  }
  return (int)x1;
}

void solve(const int &n, const int &m){
  Program lp (CGAL::SMALLER, true, 0, false, 0);
  
  for(int i=0; i<n; i++){
    int curmin, curmax; cin >> curmin >> curmax;
    lp.set_b(2*i, curmax);
    lp.set_b(2*i + 1, -curmin);
  }
  
  for(int i=0; i<m; i++){
    int price; cin >> price;
    lp.set_c(i, price);
    for(int j=0; j<n; j++){
      int nutrientquantity; cin >> nutrientquantity;
      lp.set_a(i, 2*j, nutrientquantity);
      lp.set_a(i, 2*j + 1, -nutrientquantity);
    }
  }
  
  Solution s = CGAL::solve_linear_program(lp, ET());
  if(s.is_infeasible()){
    cout << "No such diet.\n";
  }
  else{
    cout << round_down(s.objective_value()) << "\n";
  }
}

signed main(){
  while(true){
    int n, m; cin >> n >> m;
    if(n==0 && m==0){
      break;
    }
    solve(n, m);
  }
  return 0;
}