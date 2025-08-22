std::vector<int> z_function(auto begin, auto end)
{
    int n = end - begin;
    std::vector<int> z(n);
    for(int i = 1, j = 1; i < n; i++) {
        z[i] = min(z[i - j], max(0, j + z[j] - i));
        while(i + z[i] < n && *(begin + z[i]) == *(begin + i + z[i]))
            z[i]++;
        if(i + z[i] > j + z[j])
            j = i;
    }
    return z;
}
