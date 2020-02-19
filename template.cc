#include "bits/stdc++.h"
using namespace std;

/////////////////// TYPES & MACROS ///////////////////////////////
#define mp make_pair
#define eb emplace_back
#define pb push_back
#define all(x) x.begin(),x.end()
#define ff first
#define ss second
#define vv vector
#define exist(s,e) (s.find(e)!=s.end())
#define SZ(x) ((int)(x).size())
#define int int64_t
#define el '\n'
template <class T> bool inline rmn(T &a, T b) { return a > b ? (a = b, true) : false; }
template <class T> bool inline rmx(T &a, T b) { return a < b ? (a = b, true) : false; }
const int32_t MOD = 1e9 + 7, INF = 0x3f3f3f3f; const int64_t INFLL = ((int64_t)INF << 32) | INF;

//////////////////// DEBUG /////////////////////////////////////////
#define D(x) cerr<<#x<<" is:\t"<<x<<'\n';
#define DD(x,y) cerr<<'('<<#x<<','<<#y<<") are:\t"<<x<<' '<<y<<'\n';
#define DDD(x,y,z) cerr<<'('<<#x<<','<<#y<<','<<#z<<") are:\t"<<x<<' '<<y<<' '<<z<<'\n';

/////////////////// VARIABLES & FUNCTIONS//////////////////////////
vv<vv<int>> adj; vv<int> vis, color; 
int dx8[]={0,1,1,1,0,-1,-1,-1}, dy8[]={1,1,0,-1,-1,-1,0,1},dx4[]={0,1,0,-1}, dy4[]={1,0,-1,0};
inline int64_t mexp(int64_t x,int64_t n,int64_t m=MOD){int64_t res=1;x%=m;while(n){if(n&1)res=(res*x)%m;n>>=1;x=(x*x)%m;}return res;}
inline int64_t gcd(int64_t a, int64_t b){if(a<0) a=-a; if(b<0) b=-b; while (a>0 && b>0){if(a>b)a%=b;else b%=a;}return a+b;}



///////////////////// MAIN STARTS //////////////////////////////////
int32_t main(void){
ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
cout << fixed << setprecision(10); cerr<<fixed << setprecision(3);





return 0;
}
