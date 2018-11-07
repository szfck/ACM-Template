#include<iostream>
#include<stack>
#include<iomanip>
#include<algorithm>
#include<string>
#include<string.h>
#include<cmath>
#include<set>
#include<vector>
#include<queue>
#include<map>
using namespace std;
const int N = 1e6 + 10;
using ll = long long;
const int INF = 0x3f3f3f3f;
using pii = pair<int, int>;
using vi = vector<int>;
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define mp make_pair 
#define pb push_back
#define clr(x, v) memset(x, v, sizeof (x))
#define all(x) x.begin(), x.end()
#define fi first
#define se second
const int MOD = 1e9 + 7;
const double eps = 1e-9;
int sgn(double x) {
    return x < -eps ? -1 : x < eps ? 0 : 1;
}
struct Point {
    double x, y;
    Point() { }
    Point(double _x, double _y) { x = _x; y = _y; }
};
double cross(Point a, Point b, Point c) {
    return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}
double dist(Point a, Point b) {
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}
int n, m;
Point p[N], convex[N];
bool cmp(Point a, Point b) {
    int ret = sgn(cross(p[0], a, b));
    if (ret == 0) return dist(p[0], a) < dist(p[0], b);
    return ret > 0;
}
int graham() {
    int mi = 0;
    rep(i, 1, n) {
        if (sgn(p[i].y - p[mi].y) < 0 || (sgn(p[i].y - p[mi].y) == 0 && sgn(p[i].x - p[mi].x) < 0)) {
            mi = i;
        }
    }
    swap(p[0], p[mi]);
    sort(p + 1, p + n, cmp);

    int top = 0;
    convex[top++] = p[0];
    convex[top++] = p[1];
    rep(i, 2, n + 1) {
        while (top >= 2 && sgn(cross(convex[top - 2], p[i % n], convex[top - 1])) >= 0) {
            top--;
        }
        convex[top++] = p[i % n];
    }
    return top;
}
int main() {
    while (cin >> n) {
    }
    return 0;
}
