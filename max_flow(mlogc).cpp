/*
   Cool_ewrey_boy
*/

#include <bits/stdc++.h>

#define F first
#define S second
#define size(v) (int) size(v)
#define all(v) begin(v), end(v)
#if !LOCAL
   #define endl '\n'
#endif

using namespace std;
using ll = long long;
const ll INF = 1e18l + 10;
const int mod = 1e9 + 7, inf = 1e9 + 10;

struct edge {
   ll flow, cap, id;
   edge(int c, int i) {
      flow = 0;
      cap = c;
      id = i;
   }
   edge() {
      flow = cap = id = 0;
   }
   ll get() {
      return cap - flow;
   }
};

int main() {
   cin.tie(0)->sync_with_stdio(0);
   if(auto s = "in.txt"; fopen(s, "r") && freopen(s, "r", stdin));
   int n, m;
   cin >> n >> m;
   vector edg(0, edge());
   vector g(n, vector(0, pair(0, 0)));
   for(int i = 0; i < m; i++) {
      int u, v, c;
      cin >> u >> v >> c;
      u--, v--;
      g[u].push_back(pair(v, size(edg)));
      edg.push_back(edge(c, size(edg)));
      g[v].push_back(pair(u, size(edg)));
      edg.push_back(edge(0, size(edg)));
   }
   ll con = 1e9;
   vector use(n, false);
   function<bool(int)> dfs = [&](int v) {
      if(use[v]) return false;
      use[v] = 1;
      if(v == n - 1) return true;
      for(auto &[u, id]: g[v]) {
         if(edg[id].get() >= con && dfs(u)) {
            edg[id].flow += con;
            edg[id ^ 1].flow -= con;
            return true;
         }
      }
      return false;
   };
   ll ans = 0;
   while(con) {
      if(dfs(0)) {
         ans += con;
      }
      else con /= 2;
      use.assign(n, false);
   }
   cout << ans;
   return 0;
}

