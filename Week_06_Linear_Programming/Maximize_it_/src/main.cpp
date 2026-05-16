#include <iostream>
#include <vector>
#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpq.h>
#include <cmath>

typedef int IT;
typedef CGAL::Gmpq ET;

typedef CGAL::Quadratic_program<IT> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;

using namespace std;

long round_down(const CGAL::Quotient<ET> &x){
    // round down to nearest integer <= x
    long val = CGAL::to_double(x);
    while (ET(val) > x) val--;
    return val;
}

long round_up(const CGAL::Quotient<ET> &x){
    // round up to nearest integer >= x
    long val = CGAL::to_double(x);
    while (ET(val) < x) val++;
    return val;
}


void solve(const int &p){
  IT a, b; cin >> a >> b;
  
  const int X = 0;
  const int Y = 1;
  const int Z = 2;
  
  if(p==1){
  Program lp1(CGAL::SMALLER, true, 0, false, 0);
  lp1.set_a(X, 0, 1); lp1.set_a(Y, 0, 1); lp1.set_b(0, 4);
  lp1.set_a(X, 1, 4); lp1.set_a(Y, 1, 2); lp1.set_b(1, a*b);
  lp1.set_a(X, 2, -1); lp1.set_a(Y, 2, 1); lp1.set_b(2, 1);
  
  lp1.set_c(X, a);
  lp1.set_c(Y, -b);
  
  Solution s1 = CGAL::solve_linear_program(lp1, ET());
  
  if(s1.is_infeasible()){
    cout << "no" << "\n";
  }
  else if(s1.is_unbounded()){
    cout << "unbounded" << "\n";
  }
  else{
    long sol1 = -round_up(s1.objective_value());
    cout << sol1 << "\n";
  }
  return;
  }
  
  Program lp2(CGAL::SMALLER, false, 0, true, 0);
  lp2.set_a(X, 0, -1); lp2.set_a(Y, 0, -1); lp2.set_b(0, 4);
  lp2.set_a(X, 1, -4); lp2.set_a(Y, 1, -2); lp2.set_a(Z, 1, -1); lp2.set_b(1, a*b);
  lp2.set_a(X, 2, 1); lp2.set_a(Y, 2, -1); lp2.set_b(2, 1);
  
  lp2.set_c(X, a);
  lp2.set_c(Y, b);
  lp2.set_c(Z, 1);
  Solution s2 = CGAL::solve_linear_program(lp2, ET());
  
  if(s2.is_infeasible()){
    cout << "no" << "\n";
  }
  else if(s2.is_unbounded()){
    cout << "unbounded" << "\n";
  }
  else{
    long sol2 = round_up(s2.objective_value());
    cout << sol2 << "\n";
  }
  return;
}

signed main(){
  while(true){
  int p; cin >> p;
  if(!p){ break; }
  solve(p);
  }
  return 0;
}