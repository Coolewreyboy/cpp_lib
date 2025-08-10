std::vector<int> prefix_function(auto begin, auto end)
{
    std::vector<int> p(end - begin);
    for(auto ptr = begin + 1; ptr < end; ptr++) {
        int k = p[ptr - begin - 1];
        while(k > 0 && *(begin + k) != *ptr)
            k = p[k - 1];
        p[ptr - begin] = k + (*ptr == *(begin + k));
    }
    return p;
}
