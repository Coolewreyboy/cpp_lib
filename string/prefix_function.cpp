std::vector<int> prefix_function(auto begin, auto end)
{
    int n = end - begin;
    std::vector<int> p(n);
    for(int i = 1; i < n; i++) {
        int k = p[i - 1];
        while(k > 0 && *(begin + k) != *(begin + i))
            k = p[k - 1];
        p[i] = k + (*(begin + i) == *(begin + k));
    }
    return p;
}
