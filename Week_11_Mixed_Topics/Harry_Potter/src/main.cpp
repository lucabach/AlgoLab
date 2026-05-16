///1
#include <iostream>
#include <vector>
#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpz.h>
#include <tuple>

typedef CGAL::Gmpz IT;
typedef CGAL::Gmpz ET;
typedef CGAL::Quadratic_program<IT> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;

using namespace std;

struct Connection {
  int i;
  int j;
  int d;
  int e1;
  int e2;
};

double floor_to_double(const CGAL::Quotient<ET> &x){
  double x1 = floor(CGAL::to_double(x));
  while((ET) x1 > x){ x1 -= 1;}
  while((ET) x1 + 1 <= x){ x1 += 1;}
  return x1;
}

long feasible(int k, const vector<Connection> &exchanges, int a, int b, int c){
  Program lp(CGAL::SMALLER, true, 0, false, 0);
  
  const int S = 0;
  const int SUM_ROW = k;
  lp.set_c(S, 1);
  lp.set_b(SUM_ROW, c);
  
  int S_ROW = k+1;
  int next_var = 1;
  
  vector<IT> facs(k, 1);
  for(Connection c : exchanges){
    if(c.i >= k || c.j >= k){
      continue;
    }
    facs[c.j] *= c.e2;
  }
  
  for(Connection c : exchanges){
    if(c.i >= k || c.j >= k){
      continue;
    }
    int xij = next_var++;
    //flow constraint
    lp.set_a(xij, c.i, facs[c.i]);
    lp.set_a(xij, c.j, -facs[c.j]*c.e1/c.e2);
    //sum of suspicions
    lp.set_a(xij, SUM_ROW, c.d);
    //max suspicion of a single exchange
    lp.set_a(xij, S_ROW, c.d); lp.set_a(S, S_ROW, -1); lp.set_b(S_ROW, 0); S_ROW++;
  }
  
  lp.set_b(0, -b*facs[0]);
  lp.set_b(1, a);
  
  for(int i=2; i<k; i++){
    lp.set_b(i, 0);
  }
  
  Solution s = CGAL::solve_linear_program(lp, ET());
  
  if (s.is_infeasible()) {
    return -1;
  }
  return (long) -floor_to_double(-s.objective_value());
}
    
void solve(){
  int n, m, a, b, c; cin >> n >> m >> a >> b >> c;
  
  vector<Connection> exchanges;
  for(int i=0; i<m; i++){
    int x, y, d, e1, e2; cin >> x >> y >> d >> e1 >> e2;
    x--; y--;
    if(x==0 || y==1){
      continue;
    }
    exchanges.push_back({x, y, d, e1, e2});
  }
  
  long sn = feasible(n, exchanges, a, b, c);
  
  if(sn<0){ cout << "Busted!\n"; return;}
  
  int start = 2; int end = n;
  int min_people = n;
  int best_s = sn;
  while(start<=end){
    int mid = (start+end)/2;
    int maxSS = feasible(mid, exchanges, a, b, c);
    if(maxSS >= 0){
      if(mid < min_people){
        min_people = mid;
        best_s = maxSS;
      }
      end = mid -1;
    }
    else{
      start = mid+1;
    }
  }
  
  cout << min_people << " " << best_s << "\n";
}


signed main(){
  int T; cin >> T;
  while(T--){
    solve();
  }
  return 0;
}