#include "bits/stdc++.h"
using namespace std;

/////////////////// TYPES & MACROS ///////////////////////////////
#define all(x) x.begin(), x.end()
#define ff first
#define ss second
#define vv vector
#define exist(s, e) (s.find(e) != s.end())
#define SZ(x) ((int)(x).size())
#define int int64_t
#define el '\n'
template <class T>
auto inline rmn(T &a, T b) -> bool { return a > b ? (a = b, true) : false; }
template <class T>
auto inline rmx(T &a, T b) -> bool { return a < b ? (a = b, true) : false; }
const int32_t MOD = 1e9 + 7, INF = 0x3f3f3f3f;
const int64_t INFLL = ((int64_t)INF << 32) | INF;

//////////////////// DEBUG /////////////////////////////////////////
#ifdef LOCAL
#define D(x) cerr << #x << " is:\t" << x << '\n';
#define DD(x, y) cerr << '(' << #x << ',' << #y << ") are:\t" << x << ' ' << y << '\n';
#define DDD(x, y, z) cerr << '(' << #x << ',' << #y << ',' << #z << ") are:\t" << x << ' ' << y << ' ' << z << '\n';
#else
#define D(x) ;
#define DD(x, y) ;
#define DDD(x, y, z) ;
#endif

/////////////////// VARIABLES & FUNCTIONS//////////////////////////
vv<vv<int>> adj;
vv<int> vis, color;

///////////////////// MAIN STARTS //////////////////////////////////
int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
    cout << fixed << setprecision(13);
    cerr << fixed << setprecision(3);

    return 0;
}
