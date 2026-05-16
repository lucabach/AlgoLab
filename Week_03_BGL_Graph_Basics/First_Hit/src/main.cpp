#include <iostream>
#include <limits>
#include <CGAL/Exact_predicates_exact_constructions_kernel.h>


using namespace std;

typedef CGAL::Exact_predicates_exact_constructions_kernel EK;

double floor_to_double(const EK::FT &x){
  double a = floor(CGAL::to_double(x));
  while(a>x){a-=1;}
  while(a+1 <= x){a+=1;}
  return a;
}

bool solve(){
  int n; cin >> n;
  if(n == 0){
    return false;
  }
  long a, b, c, d;
  cin >> a >> b >> c >> d;
  EK::Point_2 start(a, b);
  EK::Ray_2 phileas(start, EK::Point_2(c, d));

  EK::FT minD(numeric_limits<double>::max());
  EK::Point_2 minP;
  bool found_closest = false;
  
  vector<EK::Segment_2> segs;
  for (int i=0; i<n; i++){
        long r, s, t, u;
        std::cin >> r >> s >> t >> u;
        const EK::Segment_2 seg(EK::Point_2(r, s), EK::Point_2(t, u));
        segs.push_back(seg);
  } 
  random_shuffle(segs.begin(), segs.end());
  
  for(EK::Segment_2 obs : segs){
    
    if (minD <= EK::FT(1)) break;
    if(minD < CGAL::squared_distance(start, obs)) continue;

    if(CGAL::do_intersect(phileas, obs)){
    auto inter = CGAL::intersection(phileas, obs);
    found_closest = true;
    EK::Point_2 interP;
    EK::FT interD;

    
    // Case 1: intersection is a SEGMENT
    if (const EK::Segment_2* s = boost::get<EK::Segment_2>(&*inter)) {
        EK::FT ds = CGAL::squared_distance(start, s->source());
        EK::FT dt = CGAL::squared_distance(start, s->target());
        if(ds < dt){
          interP = s->source();
          interD = ds;
        }
        else{
          interP = s->target();
          interD = dt;
        }
    }

    // Case 2: intersection is a POINT
    else if (const EK::Point_2* p = boost::get<EK::Point_2>(&*inter)) {
        interP = *p;
        interD = CGAL::squared_distance(start, *p);
    }
    
    if(interD < minD){
      minD = interD;
      minP = interP;
    }
  }
  }
  
  if(!found_closest){
    cout << "no" << "\n";
    return true;
  }
  
  cout << floor_to_double(minP.x()) << " " 
       << floor_to_double(minP.y()) << "\n";
  return true;
  }
  
int main() {
    ios_base::sync_with_stdio(false);
    std::cout << std::fixed << std::setprecision(0);
    while(solve()){}
    return 0;
}
