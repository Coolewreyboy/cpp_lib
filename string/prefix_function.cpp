std::vector<int> prefix_function(auto begin, auto end)
{
    std::vector<int> p(end - begin);
    int n = end - begin;
    for(int i = 1; i < n; i++) {
        int k = p[i - 1];
        while(k > 0 && *(begin + k) != *(begin + i))
            k = p[k - 1];
        p[i] = k + (*(begin + i) == *(begin + k));
    }
    return p;
}
