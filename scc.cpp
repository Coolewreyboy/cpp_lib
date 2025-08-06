#include <bits/stdc++.h>

using namespace std;

int main()
{
	cin.tie(0)->sync_with_stdio(0);
	int n, m;
	cin >> n >> m;
	vector<vector<int>> g(n);
	for(int i = 0; i < m; i++) {
		int u, v;
		cin >> u >> v;
		u--, v--;
		g[u].push_back(v);
	}
	int t = 0;
	vector<int> tin(n, -1), min_tin(n, -1), stk, c(n, -1);
	int cnt_c = 0;
	function<void(int)> dfs = [&](int v)
	{
		if(tin[v] != -1)
			return;
		tin[v] = t++;
		min_tin[v] = tin[v];
		stk.push_back(v);
		for(int u : g[v]) {
			dfs(u);
			if(c[u] == -1)
				min_tin[v] = min(min_tin[v], min_tin[u]);
		}
		if(min_tin[v] == tin[v]) {
			int x = -1;
			while(x != v) {
				x = stk.back();
				stk.pop_back();
				c[x] = cnt_c;
			}
			cnt_c++;
		}
	};
	for(int i = 0; i < n; i++)
		dfs(i);
	vector<vector<int>> g2(cnt_c);
	for(int i = 0; i < n; i++)
		for(int j : g[i])
			g2[c[i]].push_back(c[j]);
	vector<bool> mark(cnt_c);
	function<void(int)> dfs2 = [&](int v)
	{
		if(mark[v])
			return;
		mark[v] = 1;
		for(int u : g2[v])
			dfs2(u);
		stk.push_back(v);
	};
	for(int i = 0; i < cnt_c; i++)
		dfs2(i);
	reverse(stk.begin(), stk.end());
	vector<int> cc(cnt_c);
	for(int i = 0; i < cnt_c; i++)
		cc[stk[i]] = i;
	cout << cnt_c << endl;
	for(int i : c)
		cout << cc[i] + 1 << ' ';
	cout << endl;
	return 0;
}
