
#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
#include <set>
#include <map>
using namespace std;

typedef pair<long, long> PII;
//#define int long

vector<PII> set1;
vector<PII> set2;
vector<long> gulp;
vector<tuple<long, long, int>> dtmLeft;
vector<long> best_without_potion;

struct SortTuple {
bool operator() (const tuple<long, long, int>& p1, const tuple<long, long, int>& p2) const {
  return get<1>(p1)  < get<1>(p2) || 
        (get<1>(p1) == get<1>(p2) && get<0>(p1) > get<0>(p2)) ||
        (get<1>(p1) == get<1>(p2) && get<0>(p1) == get<0>(p2) && get<2>(p1) > get<2>(p2));
}
};



void fillBestWithoutPotion(long D, long T){
  dtmLeft.clear();
  int n = set1.size();
  for(int i=0; i< 1<<n; i++){
    long curDist = 0; long curTime = 0; int curmoves = 0;
    for(int j=0; j<n; j++){
      if(i & 1<<j){
        curmoves++;
        curDist +=  set1[j].first;
        curTime += set1[j].second;
      }
    }
      if(curTime < T){
      best_without_potion[curmoves] = max(curDist, best_without_potion[curmoves]);
      dtmLeft.emplace_back(curDist, curTime, curmoves);
      }
    }
  
  sort(dtmLeft.begin(), dtmLeft.end(), SortTuple());
  /* int curidx = 0;
  while(true){
   if(curidx >= (int)dtmLeft.size() -1){break;}
   if(get<1>(dtmLeft[curidx]) <= get<1>(dtmLeft[curidx+1]) && get<0>(dtmLeft[curidx]) >= get<0>(dtmLeft[curidx+1])){
     dtmLeft.erase(dtmLeft.begin()+curidx+1);
     continue;
    }
    curidx++;
  } */

  n = set2.size();
  for(int i=0; i< 1<<n; i++){
    long curDist = 0; long curTime = 0; int curmoves = 0;
    for(int j=0; j<n; j++){
      if(i & 1<<j){
        curmoves++;
        curDist +=  set2[j].first;
        curTime += set2[j].second;
      }
    }

    if(curTime < T){
      best_without_potion[curmoves] = max(curDist, best_without_potion[curmoves]);
    }
    
    int curidx = 0;
    while(true){
      if(curidx >= (int)dtmLeft.size()){ break;}
        long otherDist = get<0>(dtmLeft[curidx]);
        long otherTime = get<1>(dtmLeft[curidx]);
        long otherMoves = get<2>(dtmLeft[curidx]);
        if(curTime + otherTime < T){
            if(curmoves + otherMoves < (int)best_without_potion.size()){
            best_without_potion[curmoves + otherMoves] = max(best_without_potion[curmoves+otherMoves], curDist+otherDist);
            }
        }
        curidx++;
    }
  }
}


void solve(){
  long n, m, D, T; cin >> n >> m >> D >> T;
    best_without_potion.clear();
    best_without_potion.resize(n+1, 0);
    set1.clear(); set2.clear();
    set1.resize(n/2);
    set2.resize(n - n/2);

    for(int i=0; i<(int)n/2; i++){
      long d, t; cin >> d >> t;
      set1[i] = {d, t};
    }

    for(int i=0; i<(int)(n-n/2); i++){
      long d, t; cin >> d >> t;
      set2[i] = {d, t};
    }

    gulp.clear();
    gulp.resize(m+1);
    gulp[0] = 0;
    for(int i=1; i<=m; i++){
      long g; cin >> g;
      gulp[i] = g;
    }
    
    fillBestWithoutPotion(D, T);


    int start = 0;
    int end = m;
    int bestOption = -1;
    while(start<=end){
      int mid = (end+start)/2;
      bool reachable = false;
      for(int i=n; i>0;i--){
      if(best_without_potion[i] + i*gulp[mid] >= D){
        reachable = true;
        bestOption = mid;
        end = mid-1;
        break;
      }
      }
      if(!reachable){
        start = mid + 1;
      }
    }
    
    if(bestOption == -1){ cout << "Panoramix captured\n";}
    else{
    cout <<  bestOption << "\n";
    }
}

signed main(){
  ios_base::sync_with_stdio(false);
  int t; cin >> t;
  while(t--){
    solve();
  }
  return 0;
}