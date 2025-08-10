#include <bits/stdc++.h>

#define all(v) begin(v), end(v)

using namespace std;

vector<int> prefix_function(auto begin, auto end)
{
	vector<int> p(end - begin);
	for(auto ptr = begin + 1; ptr < end; ptr++) {
		int k = p[ptr - begin - 1];
		while(k > 0 && *(begin + k) != *ptr)
			k = p[k - 1];
		p[ptr - begin] = k + (*ptr == *(begin + k));
	}
	return p;
}

int main()
{
	cin.tie(0)->sync_with_stdio(0);
	string s;
	cin >> s;
	for(auto i : prefix_function(all(s)))
		cout << i << ' ';
	return 0;
}
