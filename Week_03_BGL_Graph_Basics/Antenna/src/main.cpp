#include <iostream>
#include <vector>
#include <CGAL/Exact_predicates_exact_constructions_kernel_with_sqrt.h>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Min_circle_2.h>
#include <CGAL/Min_circle_2_traits_2.h>


typedef CGAL::Exact_predicates_exact_constructions_kernel_with_sqrt SQRT_K;
typedef CGAL::Exact_predicates_inexact_constructions_kernel IK;

typedef IK::Point_2 P;
typedef IK::Circle_2 C;
typedef SQRT_K::Point_2 SQRT_P;
typedef SQRT_K::Circle_2 SQRT_C;
typedef CGAL::Min_circle_2_traits_2<IK> Traits;
typedef CGAL::Min_circle_2<Traits> Min_circle;

using namespace std;

int64_t round_up(SQRT_K::FT &x){
  double a = ceil(CGAL::to_double(x));
  while(a<x){ a+= 1;}
  while(a-1 >= x){ a-=1; }
  return static_cast<int64_t>(a);
}


bool solve(){
  int n; cin >> n;
  if(n==0){return false;}
  vector<P> points;
  points.reserve(n);
  for(int i=0; i<n; i++){
    int64_t a, b; cin >> a >> b;
    points.emplace_back(a, b);
  }
  
  if(n==0){
    cout << "0" << "\n";
    return true;
  }
  
  const Min_circle mc(points.begin(), points.end(), true);
  
  vector<SQRT_P> sqrt_points;
  for(auto iter = mc.support_points_begin(); iter != mc.support_points_end(); ++iter){
    sqrt_points.emplace_back(iter->x(), iter->y());
  }
  
  SQRT_C circle;
  
if(sqrt_points.size() == 1){
    circle = SQRT_C(sqrt_points[0], 0);
}
else if(sqrt_points.size() == 2){
    circle = SQRT_C(sqrt_points[0], sqrt_points[1]);
}
else { 
    circle = SQRT_C(sqrt_points[0], sqrt_points[1], sqrt_points[2]);
}
  
  SQRT_K::FT r = CGAL::sqrt(circle.squared_radius());
  
  cout << round_up(r) << "\n";

  return true;
}

int main(){
  ios_base::sync_with_stdio(false);
  while(solve()){}
  return 0;
}