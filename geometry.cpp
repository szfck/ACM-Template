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
int n, m;
// geo
const double pi = acos(-1.0);
const double eps = 1e-8;
inline double sqr(double x) {
    return x * x;
}
int cmp(double x) {
    if (fabs(x) < eps) return 0;
    if (x > 0) return 1;
    return -1;
}
struct point {
    double x, y;
    point() {}
    point(double a, double b) : x(a), y(b) {}
    void read() {
        cin >> x >> y;
    }
    friend point operator + (const point& a, const point& b) {
        return point(a.x + b.x, a.y + b.y);
    }
    friend point operator - (const point& a, const point& b) {
        return point(a.x - b.x, a.y - b.y);
    }
    friend bool operator == (const point&a ,const point& b) {
        return cmp(a.x - b.x) == 0 && cmp(a.y - b.y) == 0;
    }
    friend point operator * (const point& a, const double& b) {
        return point(a.x * b, a.y * b);
    }
    friend point operator * (const double& a, const point& b) {
        return point(a * b.x, a * b.y);
    }
    friend point operator / (const point& a, const double& b) {
        return point(a.x / b, a.y / b);
    }
    double len() {
        return sqrt(sqr(x) + sqr(y));
    }
    point norm() {
        return point(x / len(), y / len());
    }
};

double dist(const point& a, const point& b) {
    return (a - b).len();
}
double dot(const point& a, const point& b) {
    return a.x * b.x + a.y * b.y;
}
// counter clockwise
point rotate_point(const point& p, double A) {
    double tx = p.x, ty = p.y;
    return point(tx * cos(A) - ty * sin(A), tx * sin(A) + ty * cos(A));
}
struct Line {
    double a, b, c;
    Line(double a, double b, double c) : a(a), b(b), c(c) {} 
};

double p2l(const point& p, const Line& l) {
    return (l.a * p.x + l.b * p.y + l.c) / (sqrt(l.a * l.a + l.b * l.b));
}
Line getLine(point p, double xv, double yv) {
    return Line(yv, -xv, p.y * xv - p.x * yv);
}

