//Cool_ewrey_boy

#include <bits/stdc++.h>

#define size(v) (int) v.size()
#define all(v) begin(v), end(v)
#define ff(T, name, args...) function<T(args)> name = [&](args)->T
#if !LOCAL
   #define endl '\n'
#endif

using namespace std;
using ll = decltype(1LL);
const ll INF = 1e18l + 100;
const int mod = 1e9 + 7, inf = 1e9 + 100;

enum operation { EMPTY = 0, AND = 1, OR = 2, INV = 3 };

struct segment_tree_bits {
	vector<int> t;
	vector<operation> dt;
	int sz;
	segment_tree_bits(int n)
	{
		for(sz = 1; sz < n; sz <<= 1);
		t.resize(2 * sz - 2);
		dt.resize(2 * sz -2, EMPTY);
	};
	operation merge_operation(operation old, operation cur)
	{
		if(old == EMPTY)
			return cur;
		if(cur == EMPTY)
			return old;
		if(old == INV && cur == INV)
			return EMPTY;
		if(cur == AND || cur == OR)
			return cur;
		if(old == AND)
			return OR;
		if(old == OR)
			return AND;

	}
	void update(int v, int len, operation op)
	{
		if(op == EMPTY)
			return;
		if(op == OR)
			t[v] = len;
		if(op == AND)
			t[v] = 0;
		if(op == INV)
			t[v] = len - t[v];
	}
	void propagate(int v, int len)
	{
		dt[2 * v + 1] = merge_operation(dt[2 * v + 1], dt[v]);
		dt[2 * v + 2] = merge_operation(dt[2 * v + 2], dt[v]);
		update(2 * v + 1, len / 2, dt[v]);
		update(2 * v + 2, len / 2, dt[v]);
		dt[v] = EMPTY;
	}
	int get(int v, int lv, int rv, int l, int r)
	{
		if(r <= lv || rv <= l)
		       return 0;	
		if(l <= lv && rv <= r)
			return t[v];
		int mv = (lv + rv) / 2;
		propagate(v, rv - lv);
		return get(2 * v + 1, lv, mv, l, r) + get(2 * v + 2, mv, rv, l, r);
	}
	int get(int l, int r)
	{ return get(0, 0, sz, l, r); }
	void update(int v, int lv, int rv, int l, int r, operation op)
	{
		if(r <= lv || rv <= l)
			return;
		if(l <= lv && rv <= r) {
			update(v, rv - lv, op);
			dt[v] = merge_operation(dt[v], op);
			return;
		}
		int mv = (rv + lv) / 2;
		propagate(v, rv - lv);
		update(2 * v + 1, lv, mv, l, r, op);
		update(2 * v + 2, mv, rv, l, r, op);
		t[v] = t[2 * v + 1] + t[2 * v + 2];
	}
	void update_range(int l, int r, operation op)
	{ update(0, 0, sz, l, r, op); }
	int find_first_zero(int v, int len)
	{
		if(len == 1)
			return v - sz + 1;
		propagate(v, len);
		if(t[2 * v + 1] == len / 2)
			return find_first_zero(2 * v + 2, len / 2);
		return find_first_zero(2 * v + 1, len / 2);
	}
	int find_zero()
	{ return find_first_zero(0, sz); }

};

void solve(int __case)
{
   int n;
   cin >> n;
   vector<long long> a;
   vector<tuple<int, long long, long long>> q(n);
   for(auto &[t, l, r] : q) {
      cin >> t >> l >> r;
      a.push_back(l);
      a.push_back(r);
      a.push_back(l + 1);
      a.push_back(r + 1);
   }
   a.push_back(1);
   sort(all(a));
   a.resize(unique(all(a)) - begin(a));
   int m = size(a);
   segment_tree_bits segt(m);
   for(auto [t, l, r] : q) {
	l = lower_bound(all(a), l) - begin(a);
	r = lower_bound(all(a), r) - begin(a) + 1;
	operation op;
	if(t == 1)
		op = OR;
	if(t == 2)
		op = AND;
	if(t == 3)
		op = INV;
	segt.update_range(l, r, op);
	cout << a[segt.find_zero()] << endl;
   }
}

int main() {
   cin.tie(0)->sync_with_stdio(0);
   if(auto s = "in.txt"; fopen(s, "r") && freopen(s, "r", stdin)){};
   int t = 1;
   //cin >> t;
   //t = 1;
   for(int T = 1; T <= t; T++)
      solve(T);
   return 0;
}
