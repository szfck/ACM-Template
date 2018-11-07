//
//https://open.kattis.com/problems/rubiksrevenge
//
#include<iostream>
#include<unordered_map>
#include<unordered_set>
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
const int N = 2e5 + 10;
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
int id(int row, int col) {
    return row * 4 + col;
}
map<string, int> dep;
set<string> vis;
int res;
string tar = "RRRRGGGGBBBBYYYY";
void update(bool rec, string t, int d, queue<pair<string,int>> &que) {
    if (vis.find(t) == vis.end()) {
        vis.insert(t);
        que.push(mp(t, d));
        if (rec) {
            dep[t] = d;
            if (t == tar) res = min(res, d);
        } else {
            if (dep.find(t) != dep.end()) {
                res = min(res, dep[t] + d);
            }
        }
    }
}
void bfs(string s, bool rec) {
    vis.clear();
    queue<pair<string, int>> que;
    update(rec, s, 0, que);
    while (que.size()) {
        if (res < 20) break;
        auto cur = que.front();
        que.pop();
        string str = cur.fi;
        int dis = cur.se;
        if (dis >= 6) continue;
        rep(i, 0, 4) {
            string t = str;
            rep(j, 0, 4) {
                t[id(i, (j + 1) % 4)] = str[id(i, j)];
            }
            update(rec, t, dis + 1, que);

            t = str;
            rep(j, 0, 4) {
                t[id((j + 3) % 4, i)] = str[id(j, i)];
            }
            update(rec, t, dis + 1, que);

            t = str;
            rep(j, 0, 4) {
                t[id(i, (j + 3) % 4)] = str[id(i, j)];
            }
            update(rec, t, dis + 1, que);

            t = str;
            rep(j, 0, 4) {
                t[id((j + 1) % 4, i)] = str[id(j, i)];
            }
            update(rec, t, dis + 1, que);
        }
    }
}
int solve(string start) {
    res = 20;
    bfs(start, true);
    bfs(tar, false);
    return res;
}
int main() {
    string s = "";
    rep(i, 0, 4) {
        string t;
        cin >> t;
        s += t;
    }
    cout << solve(s) << endl;
    return 0;
}
