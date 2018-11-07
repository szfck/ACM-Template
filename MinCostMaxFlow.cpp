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
#define HH(x) P(#x << ": " << (x))
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define mp make_pair 
#define pb push_back
#define clr(x, v) memset(x, v, sizeof (x))
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
#define fi first
#define se second
const int MOD = 1e9 + 7;
const bool debug = 1;
int n, m, k;
struct Edge {
    int from, to, cap, cost;
    Edge(){ }
    Edge(int from, int to, int cap, int cost) : 
        from(from), to(to), cap(cap), cost(cost) { }
};
struct MCMF {
    int n;
    vector<Edge> edges;
    vector<int> G[N];
    int inq[N];
    int d[N];
    int p[N]; // previous edge
    int a[N];

    MCMF(int n) {
        this->n = n;
        for (int i = 0; i < n; i++) {
            G[i].clear();
        }
        edges.clear();
    }

    void addEdge(int from, int to, int cap, int cost) {
        edges.push_back(Edge(from, to, cap, cost));
        edges.push_back(Edge(to, from, 0, -cost));
        G[from].push_back((int) edges.size() - 2);
        G[to].push_back((int) edges.size() - 1);
    }

    bool BellmanFord(int s, int t, int& flow, int& cost) {
        for (int i = 0; i < n; i++) {
            d[i] = INF;
        }
        clr(inq, 0);
        d[s] = 0, inq[s] = 1, p[s] = 0, a[s] = INF;

        queue<int> que;
        que.push(s);
        while (que.size()) {
            int u = que.front();
            que.pop();
            inq[u] = 0;
            for (int i = 0; i < (int) G[u].size(); i++) {
                Edge& e = edges[G[u][i]];
                if (e.cap > 0 && d[e.to] > d[u] + e.cost) {
                    d[e.to] = d[u] + e.cost;
                    p[e.to] = G[u][i];
                    a[e.to] = min(a[u], e.cap);
                    if (!inq[e.to]) {
                        que.push(e.to);
                        inq[e.to] = 1;
                    }
                }
            }
        }
        if (d[t] == INF) return false;
        flow += a[t];
        cost += d[t] * a[t];
        int u = t;
        while (u != s) {
            edges[p[u]].cap -= a[t];
            edges[p[u] ^ 1].cap += a[t];
            u = edges[p[u]].from;
        }
        return true;
    }
};
int M(int i) { return i; }
int H(int i) { return k + i; }
int S() { return k + k; }
int T() { return S() + 1; }
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    while (cin >> n >> m, n || m) {
        vector<pair<int, int>> man, house;
        rep(i, 0, n) {
            string s;
            cin >> s;
            rep(j, 0, m) {
                if (s[j] == 'm') {
                    man.push_back(mp(i, j));
                } else if (s[j] == 'H') {
                    house.push_back(mp(i, j));
                }
            }
        }
        k = man.size();

        int s = S(), t = T();
        MCMF cf(t + 1);
        rep(i, 0, k) {
            cf.addEdge(s, M(i), 1, 0);
            cf.addEdge(H(i), t, 1, 0);
        }
        rep(i, 0, k) {
            rep(j, 0, k) {
                int dis = abs(man[i].first - house[j].first)
                    + abs(man[i].second - house[j].second);
                cf.addEdge(M(i), H(j), 1, dis);
            }
        }
        int flow = 0, cost = 0;
        while (cf.BellmanFord(s, t, flow, cost));
        cout << cost << endl;
    }
    return 0;
}


