#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpz.h>
#include <CGAL/Gmpq.h>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Triangulation_face_base_2.h>
#include <CGAL/squared_distance_2.h>
#include <limits>


typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Triangulation_vertex_base_2<K> Vb;
typedef CGAL::Triangulation_face_base_2<K> Fb;
typedef CGAL::Triangulation_data_structure_2<Vb,Fb> Tds;
typedef CGAL::Delaunay_triangulation_2<K,Tds> Triangulation;
typedef CGAL::Gmpq IT;
typedef CGAL::Gmpq ET;
typedef CGAL::Quadratic_program<IT> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;
typedef K::Point_2 P;

using namespace std;
#define int long

Triangulation t;


void solve(){
  int a, s, b, totalenergy; cin >> a >> s >> b >> totalenergy;
  Program lp (CGAL::SMALLER, true, 0, false, 0); 
  
  vector<P> asteroids(a);
  vector<int> density(a);
  for(int i=0; i<a; i++){
    int x, y, d; cin >> x >> y >> d;
    asteroids[i] = P(x, y);
    density[i] = d;
  }
  
  vector<P> shots(s);
  for(int i=0; i<s; i++){
    int x, y; cin >> x >> y;
    shots[i] = P(x, y);
  }
  
  vector<P> hunters(b);
  for(int i=0; i<b; i++){
    int x, y; cin >> x >> y;
    hunters[i] = P(x, y);
  }

  t.clear(); t.insert(hunters.begin(), hunters.end());
  vector<int> maxradius(s, numeric_limits<int>::max());
  if(b>0){
  for(int i=0; i<s; i++){
    P curShot = shots[i];
    auto nearestHunter = t.nearest_vertex(curShot);
    maxradius[i] = CGAL::squared_distance(curShot, nearestHunter->point());
  }
  }
  
  
  const IT one = 1;
  for(int i=0; i<a; i++){
    P curAsteroid = asteroids[i];
    for(int j=0; j<s; j++){
      P curShot = shots[j];
      int curD = CGAL::squared_distance(curAsteroid, curShot);
      if(curD < maxradius[j]){
        IT denominator = curD==0? one : IT(curD);
        lp.set_a(j, i, -(one/denominator));
      }
    }
  }
  

  for(int i=0; i<a; i++){
    lp.set_b(i, -density[i]);
  }
  
  const int SUM_ROW = a;
  for(int i=0; i<s; i++){
    lp.set_a(i, SUM_ROW, 1);
  }
  lp.set_b(SUM_ROW, totalenergy);
  Solution sol = CGAL::solve_linear_program(lp, ET());
  if(sol.is_infeasible()){
    cout << "n\n";
  }
  else{
    cout << "y\n";
  } 
}

signed main(){
  int T; cin >> T;
  while(T--){
    solve();
  }
  return 0;
}
