#include <iostream>
#include <vector>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>

using namespace std;

typedef CGAL::Exact_predicates_inexact_constructions_kernel IK;

bool solve() {
    int n;
    cin >> n;
    if(n==0){return false;}

    long x, y, a, b;
    cin >> x >> y >> a >> b;

    IK::Point_2 raysource(x, y), raypoint(a, b);
    IK::Ray_2 phileas(raysource, raypoint);

    vector<IK::Segment_2> obstacle;
    obstacle.reserve(n);

    for(int i = 0; i < n; i++){
        long r, s, t, u;
        cin >> r >> s >> t >> u;
        obstacle.emplace_back(IK::Point_2(r, s), IK::Point_2(t, u));
    }
    
    for(int i = 0; i < n; i++){
      if(CGAL::do_intersect(phileas, obstacle[i])){
        cout << "yes" << "\n";
        return true;
      }
    }
    cout << "no" << "\n";
    return true;
}
  
  

int main() {
    ios_base::sync_with_stdio(false);
    while(solve()) {}
    return 0;
}
