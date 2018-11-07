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
#include<time.h>
using namespace std;
const int N = 505;
const int INF = 0x3f3f3f3f;
#define P(x) { if (debug) cout << x << endl;}
#define H(x) P(#x << ": " << (x))
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define mp make_pair 
#define pb push_back
#define clr(x, v) memset(x, v, sizeof (x))
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
#define fi first
#define se second
const int MOD = 1e9 + 7;
const bool debug = 0;
int n, f, dd;
struct Edge {
    int from, to, cap, next;
    Edge() { }
    Edge(int from, int to, int cap, int next):
        from(from), to(to), cap(cap), next(next) { }
} edge[N * N * 6];
int head[N], cnt;
int d[N];
void init() {
    cnt = 0;
    clr(head, -1);
}
void addEdge(int u, int v, int c) {
    edge[cnt] = Edge(u, v, c, head[u]);
    head[u] = cnt++;
    edge[cnt] = Edge(v, u, 0, head[v]);
    head[v] = cnt++;
}
int bfs(int s, int t) {
    queue<int> que;
    clr(d, -1);
    d[s] = 0;
    que.push(s);
    while (que.size()) {
        int cur = que.front();
        que.pop();
        for (int k = head[cur]; ~k; k = edge[k].next) {
            int v = edge[k].to;
            if (d[v] == -1 && edge[k].cap > 0) {
                d[v] = d[cur] + 1;
                que.push(v);
            }
        }
    }
    return d[t] != -1;
}
int dfs(int u, int t, int flow) {
    if (u == t) return flow;
    int cur = 0;
    for (int k = head[u]; ~k; k = edge[k].next) {
        int v = edge[k].to;
        if (edge[k].cap > 0 && d[v] == d[u] + 1) {
            int f = dfs(v, t, min(edge[k].cap, flow - cur));
            cur += f;
            edge[k].cap -= f;
            edge[k ^ 1].cap += f;
        }
    }
    if (cur == 0) d[u] = -1;
    return cur;
}
int maxFlow(int s, int t) {
    int ans = 0;
    while (bfs(s, t)) {
        ans += dfs(s, t, INF);
    }
    return ans;
}
int FF(int i) { return i; }
int C1(int i) { return f + i; }
int C2(int i) { return f + n + i; }
int DD(int i) { return f + n + n + i; }
int S() { return f + n + n + dd; }
int T() { return S() + 1; }
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    while (cin >> n >> f >> dd) {
        int s = S(), t = T();
        init();
        rep(i, 0, n) {
            addEdge(C1(i), C2(i), 1);
        }
        rep(i, 0, f) {
            addEdge(s, FF(i), 1);
        }
        rep(i, 0, dd) {
            addEdge(DD(i), t, 1);
        }
        rep(i, 0, n) {
            int f_i, d_i, x;
            cin >> f_i >> d_i;
            rep(j, 0, f_i) {
                cin >> x;
                addEdge(FF(x - 1), C1(i), 1);
            }
            rep(j, 0, d_i) {
                cin >> x;
                addEdge(C2(i), DD(x - 1), 1);
            }
        }
        cout << maxFlow(s, t) << endl;
    }
    
    return 0;
}


