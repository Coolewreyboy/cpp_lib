#include <bits/stdc++.h>

#define all(v) begin(v), end(v)

using namespace std;

std::vector<int> z_function(auto begin, auto end)
{
    std::vector<int> z(end - begin);
    int n = end - begin;
    for(int i = 1, j = 1; i < n; i++) {
        if(j + z[j] > i)
		z[i] = min(z[i - j], j + z[j] - i);
        while(i + z[i] < n && *(begin + z[i]) == *(begin + i + z[i]))
            z[i]++;
        if(i + z[i] > j + z[j])
            j = i;
    }	
    return z;
}

int main()
{
	cin.tie(0)->sync_with_stdio(0);
	string s;
	cin >> s;
	for(auto i : z_function(all(s)))
		cout << i << ' ';
	return 0;
}
