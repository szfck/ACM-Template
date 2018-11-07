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
const int N = 205;
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
struct Edge {
    int from, to, cap, nxt;
};
struct Dinic {
    int head[N], cnt;
    Edge edge[N * 15];
    int d[N];
    Dinic() {
        cnt = 0;
        clr(head, -1);
    }
    void addEdge(int u, int v, int c) {
        edge[cnt] = {u, v, c, head[u]};
        head[u] = cnt++;
        edge[cnt] = {v, u, 0, head[v]};
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
            for (int k = head[cur]; ~k; k = edge[k].nxt) {
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
        for (int k = head[u]; ~k; k = edge[k].nxt) {
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
};

int main() {
    while (cin >> n >> m) {
        for (int i = 0; i < m; i++) {
            int u, v, w;
            cin >> u >> v >> w;
            dinic.addEdge(u, v, w);
        }
        int q;
        cin >> q;
        while (q--) {
            Dinic tmp = dinic;
            int s, t;
            cin >> s >> t;
            cout << tmp.maxFlow(s, t) << endl;
        }
    }
    return 0;
}
